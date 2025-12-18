#ifndef PLAIN_ENGINE_PLAOPENCVCASCADEFACEDETECTOR_HPP
#define PLAIN_ENGINE_PLAOPENCVCASCADEFACEDETECTOR_HPP

#include "plain/core/object/analysis/PLAOBJFaceDetector.hpp"
#include <opencv2/objdetect.hpp>

class PLAOpenCVCascadeFaceDetector : public PLAOBJFaceDetector
{
  cv::CascadeClassifier _faceCascade;
  PLAFloat _scaleFactor = 1.1f;
  PLAInt _minNeighbors = 3;
  PLAVec2i _minSize = PLAVec2i(30, 30);

public:
  static PLAOpenCVCascadeFaceDetector *Create();

  PLAOpenCVCascadeFaceDetector();
  ~PLAOpenCVCascadeFaceDetector();

  bool Initialize(PLAInt aFrameWidth, PLAInt aFrameHeight) override;
  bool Detect(const cv::Mat &aFrame) override;

  void SetScaleFactor(PLAFloat aFactor);
  PLAFloat GetScaleFactor() const { return _scaleFactor; }

  void SetMinNeighbors(PLAInt aMinNeighbors);
  PLAInt GetMinNeighbors() const { return _minNeighbors; }

  void SetMinSize(const PLAVec2i &aSize);
  const PLAVec2i &GetMinSize() const { return _minSize; }

private:
  PLAFace ConvertRect(const cv::Rect &aRect);
};

#endif // PLAIN_ENGINE_PLAOPENCVCASCADEFACEDETECTOR_HPP
