#include "plain/core/object/PLAOBJCameraStream.hpp"
#include "plain/core/agent/PLAAGTCameraStream.hpp"
#include "plain/core/object/PLAOBJError.hpp"

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

PLAOBJCameraStream *PLAOBJCameraStream::Stream(const PLAString &aName)
{
  return static_cast<PLAOBJCameraStream *>(PLAOBJStream::Manager::Stream(aName));
}

PLAOBJCameraStream::PLAOBJCameraStream(const PLAString &aName, int aCameraID) :
  PLAOBJStream(aName), _cameraID(aCameraID)
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

  // Open camera with V4L2 backend for better performance on Linux
  _capture.open(_cameraID, cv::CAP_V4L2);
  if (!_capture.isOpened())
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Failed to open camera device %d", _cameraID);
    return false;
  }

  // Set camera parameters for optimal performance
  _capture.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
  _capture.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
  _capture.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
  _capture.set(cv::CAP_PROP_FPS, 30);

  // Capture initial frame to establish stream properties (size, format)
  CaptureFrame();

  if (!this->IsValid())
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Failed to capture initial frame from camera %d", _cameraID);
    _capture.release();
    return false;
  }

  // Start capture thread
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
  while (_running) {
    CaptureFrame();
  }
}

void PLAOBJCameraStream::CaptureFrame()
{
  if (!_capture.isOpened())
  {
    return;
  }

  cv::Mat newFrame;
  if (!_capture.read(newFrame) || newFrame.empty())
  {
    return;
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
    return;
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
}
