#include "plain/opencv/PLAOpenCVCNNSmileDetector.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include <opencv2/imgproc.hpp>

PLAOpenCVCNNSmileDetector *PLAOpenCVCNNSmileDetector::Create()
{
  PLAOpenCVCNNSmileDetector *detector = new PLAOpenCVCNNSmileDetector();
  detector->Bind();
  return detector;
}

PLAOpenCVCNNSmileDetector::PLAOpenCVCNNSmileDetector()
  : PLAOBJSmileDetector()
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

  // Try to load model from common paths
  std::vector<std::string> modelPaths = {
    _modelPath,
    "Plain/resources/emotion-ferplus-8.onnx",
    "resources/emotion-ferplus-8.onnx",
    "/usr/share/opencv4/models/emotion-ferplus-8.onnx",
  };

  bool loaded = false;
  for (const auto &path : modelPaths)
  {
    if (path.empty())
    {
      continue;
    }

    try
    {
      _net = cv::dnn::readNetFromONNX(path);
      if (!_net.empty())
      {
        loaded = true;
        GRA_PRINT("CNN smile detector model loaded from: %s\n", path.c_str());
        break;
      }
    }
    catch (const cv::Exception &e)
    {
      continue;
    }
  }

  if (!loaded)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to load CNN emotion model. "
                    "Please ensure emotion-ferplus-8.onnx is available in resources/");
    return false;
  }

  _isInitialized = true;
  GRA_PRINT("CNN smile detector initialized\n");
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
