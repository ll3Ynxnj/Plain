#include "plain/core/object/PLAOBJCameraStream.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include "plain/core/object/analysis/PLAOBJFaceDetector.hpp"
#include "plain/core/object/analysis/PLAOBJFaceTracker.hpp"
#include "plain/core/object/analysis/PLAOBJSmileDetector.hpp"

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

  cv::Mat frame;
  if (!_capture.read(frame) || frame.empty())
  {
    return;
  }

  // Run face detection on BGR frame (before color conversion)
  if (_faceDetector && _faceDetector->IsInitialized())
  {
    _faceDetector->Detect(frame);

    // Run tracking to assign persistent IDs
    if (_faceTracker)
    {
      _lastResult = _faceDetector->GetResult();
      _faceTracker->Update(_lastResult);
    }
    else
    {
      _lastResult = _faceDetector->GetResult();
    }

    // Run smile detection on each detected face
    if (_smileDetector && _smileDetector->IsInitialized())
    {
      for (PLAFace &face : _lastResult.faces)
      {
        // Crop face region from frame
        cv::Rect faceRect(
          static_cast<int>(face.boundingRect.pos.x),
          static_cast<int>(face.boundingRect.pos.y),
          static_cast<int>(face.boundingRect.size.x),
          static_cast<int>(face.boundingRect.size.y)
        );

        // Ensure rect is within frame bounds
        faceRect.x = std::max(0, faceRect.x);
        faceRect.y = std::max(0, faceRect.y);
        faceRect.width = std::min(faceRect.width, frame.cols - faceRect.x);
        faceRect.height = std::min(faceRect.height, frame.rows - faceRect.y);

        if (faceRect.width > 0 && faceRect.height > 0)
        {
          cv::Mat faceImage = frame(faceRect);
          _smileDetector->Detect(faceImage, face);
        }
      }
    }
  }

  // Convert to RGBA format
  cv::Mat rgbaFrame;
  if (frame.channels() == 3)
  {
    cv::cvtColor(frame, rgbaFrame, cv::COLOR_BGR2RGBA);
  }
  else if (frame.channels() == 4)
  {
    cv::cvtColor(frame, rgbaFrame, cv::COLOR_BGRA2RGBA);
  }
  else
  {
    GRA_PRINT("Unsupported frame format: %d channels\n", frame.channels());
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

void PLAOBJCameraStream::SetFaceDetector(PLAOBJFaceDetector *aDetector)
{
  _faceDetector = aDetector;
}

void PLAOBJCameraStream::SetFaceTracker(PLAOBJFaceTracker *aTracker)
{
  _faceTracker = aTracker;
}

void PLAOBJCameraStream::SetSmileDetector(PLAOBJSmileDetector *aDetector)
{
  _smileDetector = aDetector;
}

PLAFaceDetectionResult PLAOBJCameraStream::GetFaceDetectionResult() const
{
  // Return tracked result if tracker is active
  if (_faceTracker)
  {
    return _lastResult;
  }
  // Otherwise return raw detection result
  if (_faceDetector)
  {
    return _faceDetector->GetResult();
  }
  return kPLAFaceDetectionResultNone;
}
