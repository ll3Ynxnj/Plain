// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/core/object/analysis/PLAOBJFrameAnalyzer.hpp"
#include "plain/core/agent/analysis/PLAAGTFrameAnalyzer.hpp"
#include "plain/core/object/analysis/PLAOBJFaceDetector.hpp"
#include "plain/core/object/analysis/PLAOBJFaceTracker.hpp"
#include "plain/core/object/analysis/PLAOBJSmileDetector.hpp"
#include "plain/core/PLAFaceDetectionScale.hpp"
#include "plain/core/PLAFaceDetectionMode.hpp"
#include "plain/core/object/PLAOBJError.hpp"

PLAOBJFrameAnalyzer *PLAOBJFrameAnalyzer::Create(
  const PLAString &aName,
  PLAFaceDetectorType aFaceDetectorType,
  PLASmileDetectorType aSmileDetectorType,
  PLAComputeMode aComputeMode)
{
  PLAOBJFrameAnalyzer *analyzer = new PLAOBJFrameAnalyzer(
    aName, aFaceDetectorType, aSmileDetectorType, aComputeMode);
  analyzer->Bind();
  return analyzer;
}

PLAOBJFrameAnalyzer *PLAOBJFrameAnalyzer::Object(const PLAString &aName)
{
  auto object = PLAObject::Object(PLAObjectType::FrameAnalyzer, aName);
  return static_cast<PLAOBJFrameAnalyzer *>(object);
}

PLAOBJFrameAnalyzer *PLAOBJFrameAnalyzer::Object(PLAId aId)
{
  auto object = PLAObject::Object(PLAObjectType::FrameAnalyzer, aId);
  return static_cast<PLAOBJFrameAnalyzer *>(object);
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

PLAOBJFrameAnalyzer::PLAOBJFrameAnalyzer(
  const PLAString &aName,
  PLAFaceDetectorType aFaceDetectorType,
  PLASmileDetectorType aSmileDetectorType,
  PLAComputeMode aComputeMode) :
  PLAObject(PLAObjectType::FrameAnalyzer, aName),
  GRAOBJBinder<PLAOBJFrameAnalyzer>::Item(aName, Manager::Instance())
{
  // Create face detector
  PLAString faceDetectorName = aName + "_FaceDetector";
  _faceDetector = PLAOBJFaceDetector::Create(aFaceDetectorType, faceDetectorName);
  if (_faceDetector)
  {
    _faceDetector->SetComputeMode(aComputeMode);
    _faceDetector->SetScale(PLAFaceDetectionScale::Half);
    _faceDetector->Initialize(1920, 1080);
    _faceDetector->SetMode(PLAFaceDetectionMode::Interval);
    _faceDetector->SetDetectionInterval(1);
  }

  // Create face tracker
  PLAString faceTrackerName = aName + "_FaceTracker";
  _faceTracker = PLAOBJFaceTracker::Create(faceTrackerName);

  // Create smile detector
  PLAString smileDetectorName = aName + "_SmileDetector";
  _smileDetector = PLAOBJSmileDetector::Create(aSmileDetectorType, smileDetectorName);
  if (_smileDetector)
  {
    _smileDetector->SetComputeMode(aComputeMode);
    _smileDetector->Initialize();
  }
}

PLAOBJFrameAnalyzer::~PLAOBJFrameAnalyzer()
{
  // Detectors are managed by their respective Managers via Bind/Unbind
  // They will be cleaned up when the application terminates
}

PLAAGTFrameAnalyzer PLAOBJFrameAnalyzer::AssignAgent()
{
  return PLAAGTFrameAnalyzer(this);
}

void PLAOBJFrameAnalyzer::EnableFaceDetection(bool aEnable)
{
  _faceDetectionEnabled = aEnable;
  if (aEnable)
  {
    // Enable all features when face detection is enabled
    _faceTrackingEnabled = true;
    _smileDetectionEnabled = true;
  }
}

void PLAOBJFrameAnalyzer::AttachToSource(PLAOBJFrameSource *aSource)
{
  if (!aSource)
  {
    return;
  }

  aSource->SetFunction(
    PLAFunctionCode::FrameSource::OnFrameUpdate,
    [this](const cv::Mat &frame) {
      this->Analyze(frame);
    });
}

void PLAOBJFrameAnalyzer::Analyze(const cv::Mat &aFrame)
{
  if (aFrame.empty())
  {
    return;
  }

  // Skip if already analyzing (no double execution)
  if (_isAnalyzing)
  {
    return;
  }

  // Start async analysis
  _isAnalyzing = true;
  std::thread([this, frame = aFrame.clone()]() {
    AnalyzeInternal(frame);
    _isAnalyzing = false;
  }).detach();
}

void PLAOBJFrameAnalyzer::AnalyzeInternal(const cv::Mat &aFrame)
{
  // Check if face detection is enabled
  if (!_faceDetectionEnabled || !_faceDetector || !_faceDetector->IsInitialized())
  {
    return;
  }

  // Run face detection
  _faceDetector->Detect(aFrame);
  PLAFaceDetectionResult result = _faceDetector->GetResult();

  // Run tracking to assign persistent IDs
  if (_faceTrackingEnabled && _faceTracker)
  {
    _faceTracker->Update(result);
  }

  // Run smile detection on each detected face
  if (_smileDetectionEnabled && _smileDetector && _smileDetector->IsInitialized())
  {
    for (PLAFace &face : result.faces)
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
        _smileDetector->Detect(faceImage, face);
      }
    }
  }

  // Update result (thread-safe)
  {
    std::lock_guard<std::mutex> lock(_resultMutex);
    _lastResult = result;
  }

  // Notify callback
  _functor.RunFunction(PLAFunctionCode::FrameAnalyzer::OnComplete, result);
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
