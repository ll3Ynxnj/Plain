#ifndef PLAIN_ENGINE_PLAOPENCVCNNSMILEDETECTOR_HPP
#define PLAIN_ENGINE_PLAOPENCVCNNSMILEDETECTOR_HPP

#include "plain/core/object/analysis/PLAOBJSmileDetector.hpp"
#include <opencv2/dnn.hpp>

// CNN-based smile detector using expression recognition model
// Uses ONNX model (e.g., FER+ or emotion-ferplus) to classify facial expressions
// Detects "happy" expression as smile
class PLAOpenCVCNNSmileDetector : public PLAOBJSmileDetector
{
  cv::dnn::Net _net;
  PLAString _modelPath;

  // Input size expected by the model
  PLAInt _inputWidth = 64;
  PLAInt _inputHeight = 64;

  // Expression labels (FER+ format)
  // 0: neutral, 1: happiness, 2: surprise, 3: sadness,
  // 4: anger, 5: disgust, 6: fear, 7: contempt
  static const PLAInt kHappyIndex = 1;

public:
  static PLAOpenCVCNNSmileDetector *Create(const PLAString &aName = "CNNSmileDetector");

  PLAOpenCVCNNSmileDetector(const PLAString &aName);
  ~PLAOpenCVCNNSmileDetector();

  bool Initialize() override;
  bool Detect(const cv::Mat &aFaceImage, PLAFace &aFace) override;

  void SetModelPath(const PLAString &aPath);
  const PLAString &GetModelPath() const { return _modelPath; }
};

#endif // PLAIN_ENGINE_PLAOPENCVCNNSMILEDETECTOR_HPP
