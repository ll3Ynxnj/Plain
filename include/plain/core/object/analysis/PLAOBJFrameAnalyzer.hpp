// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAOBJFRAMEANALYZER_HPP
#define PLAIN_ENGINE_PLAOBJFRAMEANALYZER_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/PLAOBJFrameSource.hpp"
#include "plain/core/object/analysis/PLAFace.hpp"
#include "plain/core/PLAFaceDetectorType.hpp"
#include "plain/core/PLASmileDetectorType.hpp"
#include "grain/object/GRAOBJBinder.hpp"
#include <opencv2/opencv.hpp>

class PLAOBJFaceDetector;
class PLAOBJFaceTracker;
class PLAOBJSmileDetector;

class PLAOBJFrameAnalyzer : public PLAObject,
                            private GRAOBJBinder<PLAOBJFrameAnalyzer>::Item
{
  using Binder = GRAOBJBinder<PLAOBJFrameAnalyzer>;

  // Owned detectors
  PLAOBJFaceDetector *_faceDetector = nullptr;
  PLAOBJFaceTracker *_faceTracker = nullptr;
  PLAOBJSmileDetector *_smileDetector = nullptr;

  // Enable flags
  bool _faceDetectionEnabled = false;
  bool _faceTrackingEnabled = false;
  bool _smileDetectionEnabled = false;

  PLAFaceDetectionResult _lastResult;

protected:
  PLAOBJFrameAnalyzer(const PLAString &aName,
                      PLAFaceDetectorType aFaceDetectorType,
                      PLASmileDetectorType aSmileDetectorType);

public:
  using PLAFrameAnalyzerItem = GRAOBJBinder<PLAOBJFrameAnalyzer>::Item;
  using PLAFrameAnalyzerError = GRAOBJBinder<PLAOBJFrameAnalyzer>::Error;

  static PLAOBJFrameAnalyzer *Create(
    const PLAString &aName = "FrameAnalyzer",
    PLAFaceDetectorType aFaceDetectorType = PLAFaceDetectorType::YuNet,
    PLASmileDetectorType aSmileDetectorType = PLASmileDetectorType::CNN);
  static PLAOBJFrameAnalyzer *Analyzer(const PLAString &aName);

  void Bind() override;

protected:
  void Unbind() override;

public:
  virtual ~PLAOBJFrameAnalyzer();

  // Enable/disable face detection (enables all features when true)
  void EnableFaceDetection(bool aEnable);
  bool IsFaceDetectionEnabled() const { return _faceDetectionEnabled; }

  // Enable/disable individual features (for future use)
  void EnableFaceTracking(bool aEnable) { _faceTrackingEnabled = aEnable; }
  bool IsFaceTrackingEnabled() const { return _faceTrackingEnabled; }

  void EnableSmileDetection(bool aEnable) { _smileDetectionEnabled = aEnable; }
  bool IsSmileDetectionEnabled() const { return _smileDetectionEnabled; }

  void AttachToSource(PLAOBJFrameSource *aSource);

  void Analyze(const cv::Mat &aFrame);
  PLAFaceDetectionResult GetResult() const { return _lastResult; }

//-- GRAOBJBinder::Item --/////////////////////////////////////////////////////////
private:
  const char *GetBinderItemTypeName() const override;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRAOBJBinder<PLAOBJFrameAnalyzer>
  {
    static Manager _instance;

    Manager();

  public:
    static Manager *Instance() { return &_instance; };

    ~Manager();

    void Init();
  };
};

#endif // PLAIN_ENGINE_PLAOBJFRAMEANALYZER_HPP
