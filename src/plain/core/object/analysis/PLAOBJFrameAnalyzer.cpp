// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/core/object/analysis/PLAOBJFrameAnalyzer.hpp"
#include "plain/core/object/analysis/PLAOBJFaceDetector.hpp"
#include "plain/core/object/analysis/PLAOBJFaceTracker.hpp"
#include "plain/core/object/analysis/PLAOBJSmileDetector.hpp"
#include "plain/core/object/PLAOBJError.hpp"

PLAOBJFrameAnalyzer *PLAOBJFrameAnalyzer::Create(const PLAString &aName)
{
  PLAOBJFrameAnalyzer *analyzer = new PLAOBJFrameAnalyzer(aName);
  analyzer->Bind();
  return analyzer;
}

PLAOBJFrameAnalyzer *PLAOBJFrameAnalyzer::Analyzer(const PLAString &aName)
{
  GRAOBJBinder<PLAOBJFrameAnalyzer>::Error error(GRAOBJBinder<PLAOBJFrameAnalyzer>::Error::None);
  return static_cast<PLAOBJFrameAnalyzer *>(Manager::Instance()->RefItemWithName(aName, &error));
}

void PLAOBJFrameAnalyzer::Bind()
{
  this->PLAObject::Bind();

  GRAOBJBinder<PLAOBJFrameAnalyzer>::Error error(GRAOBJBinder<PLAOBJFrameAnalyzer>::Error::None);
  PLAOBJFrameAnalyzer::Manager::Instance()->Bind(this, &error);
  if (error != GRAOBJBinder<PLAOBJFrameAnalyzer>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJFrameAnalyzer binding. ERROR : %02d", error); }
}

void PLAOBJFrameAnalyzer::Unbind()
{
  GRAOBJBinder<PLAOBJFrameAnalyzer>::Error error(GRAOBJBinder<PLAOBJFrameAnalyzer>::Error::None);
  PLAOBJFrameAnalyzer::Manager::Instance()->Unbind(this, &error);
  if (error != GRAOBJBinder<PLAOBJFrameAnalyzer>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJFrameAnalyzer unbinding. ERROR : %02d", error); }

  this->PLAObject::Unbind();
}

PLAOBJFrameAnalyzer::PLAOBJFrameAnalyzer(const PLAString &aName) :
  PLAObject(PLAObjectType::FrameAnalyzer, aName),
  GRAOBJBinder<PLAOBJFrameAnalyzer>::Item(aName, Manager::Instance())
{
}

PLAOBJFrameAnalyzer::~PLAOBJFrameAnalyzer()
{
}

void PLAOBJFrameAnalyzer::Analyze(const cv::Mat &aFrame)
{
  if (aFrame.empty())
  {
    return;
  }

  // Get face detector by name
  PLAOBJFaceDetector *faceDetector = _faceDetectorName.empty() ? nullptr
    : PLAOBJFaceDetector::Detector(_faceDetectorName);

  if (!faceDetector || !faceDetector->IsInitialized())
  {
    return;
  }

  // Run face detection
  faceDetector->Detect(aFrame);
  _lastResult = faceDetector->GetResult();

  // Run tracking to assign persistent IDs
  PLAOBJFaceTracker *faceTracker = _faceTrackerName.empty() ? nullptr
    : PLAOBJFaceTracker::Tracker(_faceTrackerName);
  if (faceTracker)
  {
    faceTracker->Update(_lastResult);
  }

  // Run smile detection on each detected face
  PLAOBJSmileDetector *smileDetector = _smileDetectorName.empty() ? nullptr
    : PLAOBJSmileDetector::Detector(_smileDetectorName);
  if (smileDetector && smileDetector->IsInitialized())
  {
    for (PLAFace &face : _lastResult.faces)
    {
      cv::Rect faceRect(
        static_cast<int>(face.boundingRect.pos.x),
        static_cast<int>(face.boundingRect.pos.y),
        static_cast<int>(face.boundingRect.size.x),
        static_cast<int>(face.boundingRect.size.y)
      );

      // Ensure rect is within frame bounds
      faceRect.x = std::max(0, faceRect.x);
      faceRect.y = std::max(0, faceRect.y);
      faceRect.width = std::min(faceRect.width, aFrame.cols - faceRect.x);
      faceRect.height = std::min(faceRect.height, aFrame.rows - faceRect.y);

      if (faceRect.width > 0 && faceRect.height > 0)
      {
        cv::Mat faceImage = aFrame(faceRect);
        smileDetector->Detect(faceImage, face);
      }
    }
  }
}

// GRAOBJBinder::Item //////////////////////////////////////////////////////////

const char *PLAOBJFrameAnalyzer::GetBinderItemTypeName() const
{
  static const char *kName = "PLAOBJFrameAnalyzer";
  return kName;
}

// PLAOBJFrameAnalyzer::Manager ////////////////////////////////////////////////

PLAOBJFrameAnalyzer::Manager PLAOBJFrameAnalyzer::Manager::_instance =
  PLAOBJFrameAnalyzer::Manager();

PLAOBJFrameAnalyzer::Manager::Manager() : GRAOBJBinder<PLAOBJFrameAnalyzer>()
{
}

PLAOBJFrameAnalyzer::Manager::~Manager()
{
}

void PLAOBJFrameAnalyzer::Manager::Init()
{
  GRAOBJBinder<PLAOBJFrameAnalyzer>::Init();
}
