#include "plain/opencv/PLAOpenCVCascadeFaceDetector.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include <opencv2/imgproc.hpp>

PLAOpenCVCascadeFaceDetector *PLAOpenCVCascadeFaceDetector::Create()
{
  PLAOpenCVCascadeFaceDetector *detector = new PLAOpenCVCascadeFaceDetector();
  detector->Bind();
  return detector;
}

PLAOpenCVCascadeFaceDetector::PLAOpenCVCascadeFaceDetector()
  : PLAOBJFaceDetector()
{
}

PLAOpenCVCascadeFaceDetector::~PLAOpenCVCascadeFaceDetector()
{
}

bool PLAOpenCVCascadeFaceDetector::Initialize(PLAInt aFrameWidth, PLAInt aFrameHeight)
{
  if (_isInitialized)
  {
    return true;
  }

  // Try to load cascade from OpenCV data directory
  // Common paths for haarcascade_frontalface_default.xml
  std::vector<std::string> cascadePaths = {
    "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml",
    "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml",
    "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml",
    "haarcascade_frontalface_default.xml",
    "resources/haarcascade_frontalface_default.xml"
  };

  bool loaded = false;
  for (const auto &path : cascadePaths)
  {
    if (_faceCascade.load(path))
    {
      loaded = true;
      GRA_PRINT("Face cascade loaded from: %s\n", path.c_str());
      break;
    }
  }

  if (!loaded)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to load face cascade classifier. "
                    "Please ensure haarcascade_frontalface_default.xml is available.");
    return false;
  }

  _isInitialized = true;
  GRA_PRINT("Face detector initialized: %dx%d\n", aFrameWidth, aFrameHeight);
  return true;
}

bool PLAOpenCVCascadeFaceDetector::Detect(const cv::Mat &aFrame)
{
  if (!_isInitialized || aFrame.empty())
  {
    return false;
  }

  if (!ShouldDetect())
  {
    return false;
  }

  // Convert to grayscale for cascade classifier
  cv::Mat gray;
  if (aFrame.channels() == 3)
  {
    cv::cvtColor(aFrame, gray, cv::COLOR_BGR2GRAY);
  }
  else if (aFrame.channels() == 4)
  {
    cv::cvtColor(aFrame, gray, cv::COLOR_BGRA2GRAY);
  }
  else if (aFrame.channels() == 1)
  {
    gray = aFrame;
  }
  else
  {
    return false;
  }

  // Equalize histogram for better detection
  cv::equalizeHist(gray, gray);

  // Detect faces
  std::vector<cv::Rect> faces;
  _faceCascade.detectMultiScale(
    gray,
    faces,
    _scaleFactor,
    _minNeighbors,
    0,
    cv::Size(_minSize.x, _minSize.y)
  );

  // Build result
  PLAFaceDetectionResult result;
  result.isValid = true;
  result.frameNumber = _frameCounter;

  for (const auto &rect : faces)
  {
    PLAFace face = ConvertRect(rect);
    result.faces.push_back(face);
  }

  UpdateResult(result);
  return true;
}

PLAFace PLAOpenCVCascadeFaceDetector::ConvertRect(const cv::Rect &aRect)
{
  PLAFace face;
  face.boundingRect = PLARect(
    PLAVec2f(static_cast<PLAFloat>(aRect.x), static_cast<PLAFloat>(aRect.y)),
    PLAVec2f(static_cast<PLAFloat>(aRect.width), static_cast<PLAFloat>(aRect.height))
  );
  face.confidence = 1.0f; // CascadeClassifier does not provide confidence
  return face;
}

void PLAOpenCVCascadeFaceDetector::SetScaleFactor(PLAFloat aFactor)
{
  _scaleFactor = (aFactor > 1.0f) ? aFactor : 1.1f;
}

void PLAOpenCVCascadeFaceDetector::SetMinNeighbors(PLAInt aMinNeighbors)
{
  _minNeighbors = (aMinNeighbors > 0) ? aMinNeighbors : 3;
}

void PLAOpenCVCascadeFaceDetector::SetMinSize(const PLAVec2i &aSize)
{
  _minSize = aSize;
}
