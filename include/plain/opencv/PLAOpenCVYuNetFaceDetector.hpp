#ifndef PLAIN_ENGINE_PLAOPENCVYUNETFACEDETECTOR_HPP
#define PLAIN_ENGINE_PLAOPENCVYUNETFACEDETECTOR_HPP

#include "plain/core/object/analysis/PLAOBJFaceDetector.hpp"
#include <opencv2/objdetect.hpp>

// YuNet-based face detector using OpenCV DNN
// Requires ONNX model file (face_detection_yunet_2023mar.onnx)
// Higher accuracy than CascadeClassifier, supports landmarks
class PLAOpenCVYuNetFaceDetector : public PLAOBJFaceDetector
{
  cv::Ptr<cv::FaceDetectorYN> _detector;
  PLAString _modelPath;
  PLAFloat _scoreThreshold = 0.5f;
  PLAFloat _nmsThreshold = 0.3f;
  PLAInt _topK = 5000;

  // Original frame size
  PLAInt _frameWidth = 0;
  PLAInt _frameHeight = 0;

  // Detection size (may differ from frame size when scaled)
  PLAInt _detectionWidth = 0;
  PLAInt _detectionHeight = 0;

public:
  static PLAOpenCVYuNetFaceDetector *Create(const PLAString &aName = "YuNetFaceDetector");

  PLAOpenCVYuNetFaceDetector(const PLAString &aName);
  ~PLAOpenCVYuNetFaceDetector();

  bool Initialize(PLAInt aFrameWidth, PLAInt aFrameHeight) override;
  bool Detect(const cv::Mat &aFrame) override;

  void SetModelPath(const PLAString &aPath);
  const PLAString &GetModelPath() const { return _modelPath; }

  void SetScoreThreshold(PLAFloat aThreshold);
  PLAFloat GetScoreThreshold() const { return _scoreThreshold; }

  void SetNMSThreshold(PLAFloat aThreshold);
  PLAFloat GetNMSThreshold() const { return _nmsThreshold; }

  void SetScale(PLAFaceDetectionScale aScale) override;

private:
  void UpdateDetectionSize();
  PLAFace ConvertDetection(const cv::Mat &aDetection, int aIndex,
                           PLAFloat aScaleX, PLAFloat aScaleY);
};

#endif // PLAIN_ENGINE_PLAOPENCVYUNETFACEDETECTOR_HPP
