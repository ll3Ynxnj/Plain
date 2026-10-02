#include "plain/core/object/PLAOBJCameraStream.hpp"
#include "plain/core/agent/PLAAGTCameraStream.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include <algorithm>
#include <chrono>

// Timeouts keep a stalled network stream from blocking the capture thread:
// without them a half-open RTSP connection makes read() wait forever and the
// stream freezes silently instead of being reopened.
static const int kOpenTimeoutMSec = 5000;
static const int kReadTimeoutMSec = 5000;
// A few failed reads happen on healthy streams, so only repeats mean a loss
static const int kReadFailureLimit = 3;
static const int kReadRetryIntervalMSec = 100;
// A stream that stalls without failing (timed out reads) is lost as well
static const int kStallTimeoutMSec = 5000;
// Reconnect backoff: retry quickly at first, then back off while the source
// stays unreachable (camera rebooting, network down, cable pulled)
static const int kReconnectDelayMinMSec = 1000;
static const int kReconnectDelayMaxMSec = 30000;
// Waiting is sliced so Close() does not have to sit through a whole delay
static const int kWaitSliceMSec = 50;

PLAOBJCameraStream *PLAOBJCameraStream::Create(const PLAString &aName, int aCameraID)
{
  PLAOBJCameraStream *stream = new PLAOBJCameraStream(aName, aCameraID);
  stream->Bind();

  if (!stream->Open()) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to open camera device %d", aCameraID);
    stream->Unbind();
    delete stream;
    return nullptr;
  }

  return stream;
}

PLAOBJCameraStream *PLAOBJCameraStream::Create(const PLAString &aName,
                                               const PLAString &aCameraURL)
{
  PLAOBJCameraStream *stream = new PLAOBJCameraStream(aName, aCameraURL);
  stream->Bind();

  if (!stream->Open()) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to open camera stream %s", aCameraURL.c_str());
    stream->Unbind();
    delete stream;
    return nullptr;
  }

  return stream;
}

PLAOBJCameraStream *PLAOBJCameraStream::Stream(const PLAString &aName)
{
  return static_cast<PLAOBJCameraStream *>(PLAOBJStream::Manager::Stream(aName));
}

PLAOBJCameraStream::PLAOBJCameraStream(const PLAString &aName, int aCameraID) :
  PLAOBJStream(aName), _cameraID(aCameraID)
{

}

PLAOBJCameraStream::PLAOBJCameraStream(const PLAString &aName,
                                       const PLAString &aCameraURL) :
  PLAOBJStream(aName), _cameraID(-1), _cameraURL(aCameraURL)
{

}

PLAOBJCameraStream::~PLAOBJCameraStream()
{
  this->Close();
}

PLAAGTCameraStream PLAOBJCameraStream::AssignAgent()
{
  return PLAAGTCameraStream(this);
}

bool PLAOBJCameraStream::Open()
{
  if (_capture.isOpened())
  {
    GRA_PRINT("Camera already opened\n");
    return true;
  }

  if (!OpenCapture())
  {
    if (!_cameraURL.empty())
    {
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Failed to open camera stream %s", _cameraURL.c_str());
    }
    else
    {
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "Failed to open camera device %d", _cameraID);
    }
    return false;
  }

  // Capture initial frame to establish stream properties (size, format)
  CaptureFrame();

  if (!this->IsValid())
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Failed to capture initial frame from camera %d", _cameraID);
    _capture.release();
    return false;
  }

  // Start capture thread
  _connected = true;
  _running = true;
  _captureThread = std::thread(&PLAOBJCameraStream::CaptureLoop, this);

  GRA_PRINT("Camera %d opened successfully\n", _cameraID);
  return true;
}

void PLAOBJCameraStream::Close()
{
  // Stop capture thread
  if (_running) {
    _running = false;
    if (_captureThread.joinable()) {
      _captureThread.join();
    }
  }

  if (_capture.isOpened())
  {
    _capture.release();
    GRA_PRINT("Camera %d closed\n", _cameraID);
  }

  _connected = false;
}

bool PLAOBJCameraStream::OpenCapture()
{
  if (!_cameraURL.empty())
  {
    // Open network stream (e.g., RTSP) with FFMPEG backend
    _capture.open(_cameraURL, cv::CAP_FFMPEG,
                  { cv::CAP_PROP_OPEN_TIMEOUT_MSEC, kOpenTimeoutMSec,
                    cv::CAP_PROP_READ_TIMEOUT_MSEC, kReadTimeoutMSec });
    return _capture.isOpened();
  }

  // Open camera with V4L2 backend for better performance on Linux
  _capture.open(_cameraID, cv::CAP_V4L2);
  if (!_capture.isOpened())
  {
    return false;
  }

  // Set camera parameters for optimal performance
  _capture.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
  _capture.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
  _capture.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
  _capture.set(cv::CAP_PROP_FPS, 30);
  return true;
}

void PLAOBJCameraStream::Update()
{
  // Called by Stream::Manager::Update() in main thread
  // Fire event when new frame is available
  if (IsUpdated()) {
    RunFunction(PLAFunctionCode::FrameSource::OnFrameUpdate, _analysisFrames[_analysisFrameIndex]);
    Consume();
  }
}

void PLAOBJCameraStream::CaptureLoop()
{
  int failureCount = 0;
  int reconnectDelayMSec = kReconnectDelayMinMSec;
  auto lastFrameTime = std::chrono::steady_clock::now();

  while (_running) {
    if (CaptureFrame())
    {
      if (!_connected)
      {
        _connected = true;
        GRA_PRINT("Camera stream recovered\n");
      }
      failureCount = 0;
      reconnectDelayMSec = kReconnectDelayMinMSec;
      lastFrameTime = std::chrono::steady_clock::now();
      continue;
    }

    // Two ways to lose a stream: reads that fail right away (connection
    // closed) and reads that time out (connection alive but silent)
    auto stalledMSec = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::steady_clock::now() - lastFrameTime).count();
    if (++failureCount < kReadFailureLimit && stalledMSec < kStallTimeoutMSec)
    {
      WaitForRetry(kReadRetryIntervalMSec);
      continue;
    }

    // The stream is gone. A network stream never recovers on its own, so the
    // capture has to be reopened; the display keeps showing the last frame
    // until it does.
    if (_connected)
    {
      _connected = false;
      GRA_PRINT("Camera stream lost, reconnecting\n");
    }

    _capture.release();
    WaitForRetry(reconnectDelayMSec);
    if (!_running) { break; }

    if (OpenCapture())
    {
      // Reads decide whether the stream is really back
      failureCount = 0;
      lastFrameTime = std::chrono::steady_clock::now();
    }
    else
    {
      reconnectDelayMSec = std::min(reconnectDelayMSec * 2, kReconnectDelayMaxMSec);
    }
  }
}

void PLAOBJCameraStream::WaitForRetry(int aMSec)
{
  for (int elapsed = 0; elapsed < aMSec && _running; elapsed += kWaitSliceMSec)
  {
    int sliceMSec = std::min(kWaitSliceMSec, aMSec - elapsed);
    std::this_thread::sleep_for(std::chrono::milliseconds(sliceMSec));
  }
}

bool PLAOBJCameraStream::CaptureFrame()
{
  if (!_capture.isOpened())
  {
    return false;
  }

  cv::Mat newFrame;
  if (!_capture.read(newFrame) || newFrame.empty())
  {
    return false;
  }

  // Write to back analysis buffer (lock-free double buffering)
  int backIndex = 1 - _analysisFrameIndex;
  _analysisFrames[backIndex] = newFrame.clone();

  // Convert to RGBA format
  cv::Mat rgbaFrame;
  if (newFrame.channels() == 3)
  {
    cv::cvtColor(newFrame, rgbaFrame, cv::COLOR_BGR2RGBA);
  }
  else if (newFrame.channels() == 4)
  {
    cv::cvtColor(newFrame, rgbaFrame, cv::COLOR_BGRA2RGBA);
  }
  else
  {
    GRA_PRINT("Unsupported frame format: %d channels\n", newFrame.channels());
    return false;
  }

  // Update stream data using double buffering
  _size = PLAOBJImageSize(rgbaFrame.cols, rgbaFrame.rows);
  _type = PLAImageType::Raw;

  PLASize dataSize = _size.x * _size.y * 4; // RGBA 4 bytes per pixel

  // Write to back buffer
  std::vector<PLAUInt8> &backBuffer = GetBackBuffer();
  backBuffer.resize(dataSize);
  std::copy(rgbaFrame.data, rgbaFrame.data + dataSize, backBuffer.begin());

  // Swap both buffers atomically
  _analysisFrameIndex = backIndex;
  SwapBuffers();
  return true;
}
