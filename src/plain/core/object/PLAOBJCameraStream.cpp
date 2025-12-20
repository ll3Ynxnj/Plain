#include "plain/core/object/PLAOBJCameraStream.hpp"
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
  this->Update();

  if (!this->IsValid())
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Failed to capture initial frame from camera %d", _cameraID);
    _capture.release();
    return false;
  }

  GRA_PRINT("Camera %d opened successfully\n", _cameraID);
  return true;
}

void PLAOBJCameraStream::Close()
{
  if (_capture.isOpened())
  {
    _capture.release();
    GRA_PRINT("Camera %d closed\n", _cameraID);
  }
}

void PLAOBJCameraStream::Update()
{
  if (!_capture.isOpened())
  {
    return;
  }

  if (!_capture.read(_lastFrame) || _lastFrame.empty())
  {
    return;
  }

  // Convert to RGBA format
  cv::Mat rgbaFrame;
  if (_lastFrame.channels() == 3)
  {
    cv::cvtColor(_lastFrame, rgbaFrame, cv::COLOR_BGR2RGBA);
  }
  else if (_lastFrame.channels() == 4)
  {
    cv::cvtColor(_lastFrame, rgbaFrame, cv::COLOR_BGRA2RGBA);
  }
  else
  {
    GRA_PRINT("Unsupported frame format: %d channels\n", _lastFrame.channels());
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

  // Swap buffers to make new data available for reading
  SwapBuffers();
}
