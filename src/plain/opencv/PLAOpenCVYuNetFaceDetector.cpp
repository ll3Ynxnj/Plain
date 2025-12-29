#include "plain/opencv/PLAOpenCVYuNetFaceDetector.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>

namespace {
  std::pair<int, int> GetOpenCVBackendTarget(PLAComputeMode aMode)
  {
    switch (aMode) {
      case PLAComputeMode::CUDA:
        return {cv::dnn::DNN_BACKEND_CUDA, cv::dnn::DNN_TARGET_CUDA};
      case PLAComputeMode::OpenCL:
        return {cv::dnn::DNN_BACKEND_OPENCV, cv::dnn::DNN_TARGET_OPENCL};
      case PLAComputeMode::CPU:
        return {cv::dnn::DNN_BACKEND_OPENCV, cv::dnn::DNN_TARGET_CPU};
      case PLAComputeMode::Default:
      default:
        return {cv::dnn::DNN_BACKEND_DEFAULT, cv::dnn::DNN_TARGET_CPU};
    }
  }

  const char *GetComputeModeName(PLAComputeMode aMode)
  {
    switch (aMode) {
      case PLAComputeMode::CUDA:   return "CUDA";
      case PLAComputeMode::OpenCL: return "OpenCL";
      case PLAComputeMode::CPU:    return "CPU";
      case PLAComputeMode::Default:
      default:                     return "Default";
    }
  }
}

PLAOpenCVYuNetFaceDetector *PLAOpenCVYuNetFaceDetector::Create(const PLAString &aName)
{
  return new PLAOpenCVYuNetFaceDetector(aName);
}

PLAOpenCVYuNetFaceDetector::PLAOpenCVYuNetFaceDetector(const PLAString &aName)
  : PLAOBJFaceDetector(aName)
{
}

PLAOpenCVYuNetFaceDetector::~PLAOpenCVYuNetFaceDetector()
{
}

bool PLAOpenCVYuNetFaceDetector::Initialize(PLAInt aFrameWidth, PLAInt aFrameHeight)
{
  if (_isInitialized)
  {
    return true;
  }

  // Store original frame size
  _frameWidth = aFrameWidth;
  _frameHeight = aFrameHeight;

  // Calculate detection size based on scale
  UpdateDetectionSize();

  // Model path (user-specified or default, compile-time path from CMake)
  std::string modelPath = _modelPath.empty()
    ? PLA_YUNET_MODEL_PATH
    : _modelPath;

  try
  {
    auto [backendId, targetId] = GetOpenCVBackendTarget(_computeMode);
    _detector = cv::FaceDetectorYN::create(
      modelPath,
      "",
      cv::Size(_detectionWidth, _detectionHeight),
      _scoreThreshold,
      _nmsThreshold,
      _topK,
      backendId,
      targetId
    );
  }
  catch (const cv::Exception &e)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to load YuNet model from: %s (%s)",
                    modelPath.c_str(), e.what());
    return false;
  }

  if (!_detector)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to load YuNet model from: %s",
                    modelPath.c_str());
    return false;
  }

  GRA_PRINT("YuNet model loaded from: %s\n", modelPath.c_str());

  _isInitialized = true;
  GRA_PRINT("YuNet face detector initialized: %dx%d (detection: %dx%d, scale: %d, compute: %s)\n",
            aFrameWidth, aFrameHeight, _detectionWidth, _detectionHeight,
            static_cast<int>(_scale), GetComputeModeName(_computeMode));
  return true;
}

void PLAOpenCVYuNetFaceDetector::UpdateDetectionSize()
{
  PLAInt divisor = 1;
  switch (_scale)
  {
    case PLAFaceDetectionScale::Full:
      divisor = 1;
      break;
    case PLAFaceDetectionScale::Half:
      divisor = 2;
      break;
    case PLAFaceDetectionScale::Quarter:
      divisor = 4;
      break;
    case PLAFaceDetectionScale::Eighth:
      divisor = 8;
      break;
    default:
      divisor = 1;
      break;
  }

  _detectionWidth = _frameWidth / divisor;
  _detectionHeight = _frameHeight / divisor;
}

bool PLAOpenCVYuNetFaceDetector::Detect(const cv::Mat &aFrame)
{
  if (!_isInitialized || aFrame.empty() || !_detector)
  {
    return false;
  }

  if (!ShouldDetect())
  {
    return false;
  }

  // YuNet expects BGR input
  cv::Mat bgrFrame;
  if (aFrame.channels() == 4)
  {
    cv::cvtColor(aFrame, bgrFrame, cv::COLOR_BGRA2BGR);
  }
  else if (aFrame.channels() == 3)
  {
    bgrFrame = aFrame;
  }
  else
  {
    cv::cvtColor(aFrame, bgrFrame, cv::COLOR_GRAY2BGR);
  }

  // Detect faces
  cv::Mat faces;
  PLAFloat scaleX = 1.0f;
  PLAFloat scaleY = 1.0f;

  if (_scale == PLAFaceDetectionScale::Full)
  {
    // No resize - detect at original resolution
    _detector->detect(bgrFrame, faces);
  }
  else
  {
    // Resize for detection, then scale coordinates back
    cv::Mat resizedFrame;
    cv::resize(bgrFrame, resizedFrame, cv::Size(_detectionWidth, _detectionHeight));
    _detector->detect(resizedFrame, faces);

    scaleX = static_cast<PLAFloat>(aFrame.cols) / _detectionWidth;
    scaleY = static_cast<PLAFloat>(aFrame.rows) / _detectionHeight;
  }

  // Build result
  PLAFaceDetectionResult result;
  result.isValid = true;
  result.frameNumber = _frameCounter;

  if (!faces.empty())
  {
    for (int i = 0; i < faces.rows; ++i)
    {
      PLAFace face = ConvertDetection(faces, i, scaleX, scaleY);
      result.faces.push_back(face);
    }
  }

  UpdateResult(result);
  return true;
}

PLAFace PLAOpenCVYuNetFaceDetector::ConvertDetection(const cv::Mat &aDetection, int aIndex,
                                                     PLAFloat aScaleX, PLAFloat aScaleY)
{
  // YuNet detection format per row:
  // [x, y, w, h, ...(landmarks)..., score]
  // Index 14 is confidence score

  PLAFace face;

  float x = aDetection.at<float>(aIndex, 0) * aScaleX;
  float y = aDetection.at<float>(aIndex, 1) * aScaleY;
  float w = aDetection.at<float>(aIndex, 2) * aScaleX;
  float h = aDetection.at<float>(aIndex, 3) * aScaleY;

  face.boundingRect = PLARect(
    PLAVec2f(x, y),
    PLAVec2f(w, h)
  );

  face.confidence = aDetection.at<float>(aIndex, 14);

  return face;
}

void PLAOpenCVYuNetFaceDetector::SetModelPath(const PLAString &aPath)
{
  _modelPath = aPath;
}

void PLAOpenCVYuNetFaceDetector::SetScoreThreshold(PLAFloat aThreshold)
{
  _scoreThreshold = (aThreshold > 0.0f && aThreshold <= 1.0f) ? aThreshold : 0.9f;
  if (_detector)
  {
    _detector->setScoreThreshold(_scoreThreshold);
  }
}

void PLAOpenCVYuNetFaceDetector::SetNMSThreshold(PLAFloat aThreshold)
{
  _nmsThreshold = (aThreshold > 0.0f && aThreshold <= 1.0f) ? aThreshold : 0.3f;
  if (_detector)
  {
    _detector->setNMSThreshold(_nmsThreshold);
  }
}

void PLAOpenCVYuNetFaceDetector::SetScale(PLAFaceDetectionScale aScale)
{
  if (_scale == aScale)
  {
    return;
  }

  _scale = aScale;
  UpdateDetectionSize();

  // Recreate detector with new size if already initialized
  if (_isInitialized && _detector)
  {
    _detector->setInputSize(cv::Size(_detectionWidth, _detectionHeight));
    GRA_PRINT("YuNet detection size changed: %dx%d (scale: %d)\n",
              _detectionWidth, _detectionHeight, static_cast<int>(_scale));
  }
}

void PLAOpenCVYuNetFaceDetector::SetComputeMode(PLAComputeMode aMode)
{
  if (_isInitialized)
  {
    GRA_PRINT("Warning: Cannot change compute mode after initialization\n");
    return;
  }
  _computeMode = aMode;
}
