#include "plain/opencv/PLAOpenCVCNNSmileDetector.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include <opencv2/imgproc.hpp>

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

PLAOpenCVCNNSmileDetector *PLAOpenCVCNNSmileDetector::Create(const PLAString &aName)
{
  return new PLAOpenCVCNNSmileDetector(aName);
}

PLAOpenCVCNNSmileDetector::PLAOpenCVCNNSmileDetector(const PLAString &aName)
  : PLAOBJSmileDetector(aName)
{
}

PLAOpenCVCNNSmileDetector::~PLAOpenCVCNNSmileDetector()
{
}

bool PLAOpenCVCNNSmileDetector::Initialize()
{
  if (_isInitialized)
  {
    return true;
  }

  // Model path (user-specified or default, compile-time path from CMake)
  std::string modelPath = _modelPath.empty()
    ? PLA_EMOTION_MODEL_PATH
    : _modelPath;

  try
  {
    _net = cv::dnn::readNetFromONNX(modelPath);
  }
  catch (const cv::Exception &e)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to load CNN emotion model from: %s (%s)",
                    modelPath.c_str(), e.what());
    return false;
  }

  if (_net.empty())
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to load CNN emotion model from: %s",
                    modelPath.c_str());
    return false;
  }

  GRA_PRINT("CNN smile detector model loaded from: %s\n", modelPath.c_str());

  // Set DNN backend and target
  auto [backendId, targetId] = GetOpenCVBackendTarget(_computeMode);
  _net.setPreferableBackend(backendId);
  _net.setPreferableTarget(targetId);

  _isInitialized = true;
  GRA_PRINT("CNN smile detector initialized (compute: %s)\n", GetComputeModeName(_computeMode));
  return true;
}

bool PLAOpenCVCNNSmileDetector::Detect(const cv::Mat &aFaceImage, PLAFace &aFace)
{
  if (!_isInitialized || aFaceImage.empty())
  {
    return false;
  }

  // Convert to grayscale (FER+ expects grayscale)
  cv::Mat grayFace;
  if (aFaceImage.channels() == 3)
  {
    cv::cvtColor(aFaceImage, grayFace, cv::COLOR_BGR2GRAY);
  }
  else if (aFaceImage.channels() == 4)
  {
    cv::cvtColor(aFaceImage, grayFace, cv::COLOR_BGRA2GRAY);
  }
  else
  {
    grayFace = aFaceImage;
  }

  // Resize to model input size
  cv::Mat resizedFace;
  cv::resize(grayFace, resizedFace, cv::Size(_inputWidth, _inputHeight));

  // Convert to float (model expects [0,255] range)
  cv::Mat floatFace;
  resizedFace.convertTo(floatFace, CV_32F);

  // Create blob (1, 1, 64, 64)
  cv::Mat blob = cv::dnn::blobFromImage(floatFace);

  // Run inference (emotion-ferplus uses "Input3" as input layer name)
  _net.setInput(blob, "Input3");
  cv::Mat output = _net.forward();

  // Apply softmax to convert logits to probabilities
  cv::Mat expOutput;
  cv::exp(output, expOutput);
  PLAFloat sumExp = static_cast<PLAFloat>(cv::sum(expOutput)[0]);
  cv::Mat probabilities = expOutput / sumExp;

  // Get happiness probability (index 1)
  PLAFloat happyProb = probabilities.at<float>(0, kHappyIndex);

  // Determine if smiling based on threshold
  aFace.isSmiling = (happyProb >= _threshold);
  aFace.smileConfidence = happyProb;

  return true;
}

void PLAOpenCVCNNSmileDetector::SetModelPath(const PLAString &aPath)
{
  _modelPath = aPath;
}

void PLAOpenCVCNNSmileDetector::SetComputeMode(PLAComputeMode aMode)
{
  if (_isInitialized)
  {
    GRA_PRINT("Warning: Cannot change compute mode after initialization\n");
    return;
  }
  _computeMode = aMode;
}
