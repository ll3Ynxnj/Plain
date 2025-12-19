#include "plain/opencv/PLAOpenCVCascadeSmileDetector.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include <opencv2/imgproc.hpp>

PLAOpenCVCascadeSmileDetector *PLAOpenCVCascadeSmileDetector::Create(const PLAString &aName)
{
  return new PLAOpenCVCascadeSmileDetector(aName);
}

PLAOpenCVCascadeSmileDetector::PLAOpenCVCascadeSmileDetector(const PLAString &aName)
  : PLAOBJSmileDetector(aName)
{
}

PLAOpenCVCascadeSmileDetector::~PLAOpenCVCascadeSmileDetector()
{
}

bool PLAOpenCVCascadeSmileDetector::Initialize()
{
  if (_isInitialized)
  {
    return true;
  }

  // Try to load smile cascade from common paths
  std::vector<std::string> cascadePaths = {
    _cascadePath,
    "resources/haarcascade_smile.xml",
    "/usr/share/opencv4/haarcascades/haarcascade_smile.xml",
    "/usr/local/share/opencv4/haarcascades/haarcascade_smile.xml",
    "/usr/share/opencv/haarcascades/haarcascade_smile.xml",
  };

  bool loaded = false;
  for (const auto &path : cascadePaths)
  {
    if (path.empty())
    {
      continue;
    }

    if (_smileCascade.load(path))
    {
      loaded = true;
      GRA_PRINT("Smile cascade loaded from: %s\n", path.c_str());
      break;
    }
  }

  if (!loaded)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to load smile cascade. "
                    "Please ensure haarcascade_smile.xml is available.");
    return false;
  }

  _isInitialized = true;
  GRA_PRINT("Cascade smile detector initialized\n");
  return true;
}

bool PLAOpenCVCascadeSmileDetector::Detect(const cv::Mat &aFaceImage, PLAFace &aFace)
{
  if (!_isInitialized || aFaceImage.empty())
  {
    return false;
  }

  // Convert to grayscale if needed
  cv::Mat grayFace;
  if (aFaceImage.channels() == 1)
  {
    grayFace = aFaceImage;
  }
  else if (aFaceImage.channels() == 3)
  {
    cv::cvtColor(aFaceImage, grayFace, cv::COLOR_BGR2GRAY);
  }
  else if (aFaceImage.channels() == 4)
  {
    cv::cvtColor(aFaceImage, grayFace, cv::COLOR_BGRA2GRAY);
  }
  else
  {
    return false;
  }

  // Equalize histogram for better detection
  cv::equalizeHist(grayFace, grayFace);

  // Calculate minimum smile size based on face size
  int minSize = grayFace.cols / _minSizeRatio;

  // Detect smiles in the lower half of the face (mouth region)
  int mouthRegionY = grayFace.rows / 2;
  cv::Mat mouthRegion = grayFace(cv::Rect(0, mouthRegionY,
                                           grayFace.cols,
                                           grayFace.rows - mouthRegionY));

  std::vector<cv::Rect> smiles;
  _smileCascade.detectMultiScale(
    mouthRegion,
    smiles,
    _scaleFactor,
    _minNeighbors,
    0,
    cv::Size(minSize, minSize)
  );

  // Update face with smile detection result
  aFace.isSmiling = !smiles.empty();
  aFace.smileConfidence = smiles.empty() ? 0.0f :
    std::min(1.0f, static_cast<PLAFloat>(smiles.size()) / 3.0f);

  return true;
}

void PLAOpenCVCascadeSmileDetector::SetCascadePath(const PLAString &aPath)
{
  _cascadePath = aPath;
}

void PLAOpenCVCascadeSmileDetector::SetScaleFactor(PLAFloat aFactor)
{
  _scaleFactor = (aFactor > 1.0f) ? aFactor : 1.1f;
}

void PLAOpenCVCascadeSmileDetector::SetMinNeighbors(PLAInt aNeighbors)
{
  _minNeighbors = (aNeighbors > 0) ? aNeighbors : 20;
}
