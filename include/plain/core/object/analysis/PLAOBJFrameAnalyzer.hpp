// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAOBJFRAMEANALYZER_HPP
#define PLAIN_ENGINE_PLAOBJFRAMEANALYZER_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/PLAOBJFrameSource.hpp"
#include "plain/core/object/analysis/PLAFace.hpp"
#include "grain/object/GRAOBJBinder.hpp"
#include <opencv2/opencv.hpp>

class PLAOBJFrameAnalyzer : public PLAObject,
                            private GRAOBJBinder<PLAOBJFrameAnalyzer>::Item
{
  using Binder = GRAOBJBinder<PLAOBJFrameAnalyzer>;

  PLAString _faceDetectorName;
  PLAString _faceTrackerName;
  PLAString _smileDetectorName;
  PLAFaceDetectionResult _lastResult;

protected:
  PLAOBJFrameAnalyzer(const PLAString &aName);

public:
  using PLAFrameAnalyzerItem = GRAOBJBinder<PLAOBJFrameAnalyzer>::Item;
  using PLAFrameAnalyzerError = GRAOBJBinder<PLAOBJFrameAnalyzer>::Error;

  static PLAOBJFrameAnalyzer *Create(const PLAString &aName = "FrameAnalyzer");
  static PLAOBJFrameAnalyzer *Analyzer(const PLAString &aName);

  void Bind() override;

protected:
  void Unbind() override;

public:
  virtual ~PLAOBJFrameAnalyzer();

  void SetFaceDetectorName(const PLAString &aName) { _faceDetectorName = aName; }
  const PLAString &GetFaceDetectorName() const { return _faceDetectorName; }

  void SetFaceTrackerName(const PLAString &aName) { _faceTrackerName = aName; }
  const PLAString &GetFaceTrackerName() const { return _faceTrackerName; }

  void SetSmileDetectorName(const PLAString &aName) { _smileDetectorName = aName; }
  const PLAString &GetSmileDetectorName() const { return _smileDetectorName; }

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
