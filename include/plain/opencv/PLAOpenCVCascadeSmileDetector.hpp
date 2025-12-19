#ifndef PLAIN_ENGINE_PLAOPENCVCASCADESMILEDETECTOR_HPP
#define PLAIN_ENGINE_PLAOPENCVCASCADESMILEDETECTOR_HPP

#include "plain/core/object/analysis/PLAOBJSmileDetector.hpp"
#include <opencv2/objdetect.hpp>

// CascadeClassifier-based smile detector
// Uses haarcascade_smile.xml
class PLAOpenCVCascadeSmileDetector : public PLAOBJSmileDetector
{
  cv::CascadeClassifier _smileCascade;
  PLAString _cascadePath;

  // Detection parameters
  PLAFloat _scaleFactor = 1.1f;
  PLAInt _minNeighbors = 100;
  PLAInt _minSizeRatio = 4;  // minSize = face width / ratio

public:
  static PLAOpenCVCascadeSmileDetector *Create();

  PLAOpenCVCascadeSmileDetector();
  ~PLAOpenCVCascadeSmileDetector();

  bool Initialize() override;
  bool Detect(const cv::Mat &aFaceImage, PLAFace &aFace) override;

  void SetCascadePath(const PLAString &aPath);
  const PLAString &GetCascadePath() const { return _cascadePath; }

  void SetScaleFactor(PLAFloat aFactor);
  void SetMinNeighbors(PLAInt aNeighbors);
};

#endif // PLAIN_ENGINE_PLAOPENCVCASCADESMILEDETECTOR_HPP
