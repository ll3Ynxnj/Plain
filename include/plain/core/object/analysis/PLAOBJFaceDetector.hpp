#ifndef PLAIN_ENGINE_PLAOBJFACEDETECTOR_HPP
#define PLAIN_ENGINE_PLAOBJFACEDETECTOR_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/analysis/PLAFace.hpp"
#include "plain/core/PLAFaceDetectorType.hpp"
#include "plain/core/PLAFaceDetectionMode.hpp"
#include <opencv2/opencv.hpp>
#include <mutex>

class PLAOBJFaceDetector : public PLAObject
{
protected:
  PLAFaceDetectionMode _mode = PLAFaceDetectionMode::None;
  PLAInt _detectionInterval = 1;
  PLAInt _frameCounter = 0;

  PLAFaceDetectionResult _result;
  mutable std::mutex _resultMutex;

  bool _isInitialized = false;

  PLAOBJFaceDetector();

public:
  static PLAOBJFaceDetector *Create(PLAFaceDetectorType aType);

  virtual ~PLAOBJFaceDetector();

  virtual bool Initialize(PLAInt aFrameWidth, PLAInt aFrameHeight) = 0;
  virtual bool Detect(const cv::Mat &aFrame) = 0;

  PLAFaceDetectionResult GetResult() const;

  void SetMode(PLAFaceDetectionMode aMode);
  PLAFaceDetectionMode GetMode() const { return _mode; }

  void SetDetectionInterval(PLAInt aInterval);
  PLAInt GetDetectionInterval() const { return _detectionInterval; }

  bool IsInitialized() const { return _isInitialized; }

protected:
  bool ShouldDetect();
  void UpdateResult(const PLAFaceDetectionResult &aResult);
};

#endif // PLAIN_ENGINE_PLAOBJFACEDETECTOR_HPP
