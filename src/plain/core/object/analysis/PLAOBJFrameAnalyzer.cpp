// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/core/object/analysis/PLAOBJFrameAnalyzer.hpp"
#include "plain/core/agent/analysis/PLAAGTFrameAnalyzer.hpp"
#include "plain/core/object/analysis/PLAOBJFaceDetector.hpp"
#include "plain/core/object/analysis/PLAOBJFaceTracker.hpp"
#include "plain/core/object/analysis/PLAOBJSmileDetector.hpp"
#include "plain/core/PLAFaceDetectionScale.hpp"
#include "plain/core/PLAFaceDetectionMode.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include <atomic>
#include <chrono>
#include <cstdlib>

// Perf instrumentation (enabled via PLA_PERF=1)
// Prints analyzed/offered fps and per-stage timings every 5 seconds
namespace
{
  bool PerfEnabled()
  {
    static const bool enabled = std::getenv("PLA_PERF") != nullptr;
    return enabled;
  }

  std::atomic<int> perfOffered{0};   // frames offered by source
  std::atomic<int> perfSkipped{0};   // frames skipped (analysis busy)
  std::atomic<int> perfAnalyzed{0};  // frames fully analyzed
  std::atomic<long long> perfDetectUs{0};
  std::atomic<long long> perfSmileUs{0};
  std::atomic<long long> perfDetectMaxUs{0};
  std::atomic<int> perfFaces{0};

  void PerfReport()
  {
    // Called only from the single analysis worker thread
    static auto windowStart = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    float sec = std::chrono::duration<float>(now - windowStart).count();
    if (sec < 5.0f) { return; }

    int analyzed = perfAnalyzed.exchange(0);
    int offered = perfOffered.exchange(0);
    int skipped = perfSkipped.exchange(0);
    long long detectUs = perfDetectUs.exchange(0);
    long long smileUs = perfSmileUs.exchange(0);
    long long detectMaxUs = perfDetectMaxUs.exchange(0);
    int faces = perfFaces.exchange(0);
    windowStart = now;

    float analyzedF = analyzed > 0 ? static_cast<float>(analyzed) : 1;
    GRA_PRINT("[PERF] analyzed %.1ffps (offered %.1f, skipped %.1f) | "
              "faces avg %.2f | detect avg %.1fms max %.1fms | "
              "smile avg %.1fms/frame | total avg %.1fms\n",
              analyzed / sec, offered / sec, skipped / sec,
              faces / analyzedF,
              detectUs / analyzedF / 1000.0f,
              detectMaxUs / 1000.0f,
              smileUs / analyzedF / 1000.0f,
              (detectUs + smileUs) / analyzedF / 1000.0f);
  }
}

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

  if (PerfEnabled()) { perfOffered++; }

  // Skip if already analyzing (no double execution)
  if (_isAnalyzing)
  {
    if (PerfEnabled()) { perfSkipped++; }
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

  auto perfT0 = std::chrono::steady_clock::now();

  // Run face detection
  _faceDetector->Detect(aFrame);
  PLAFaceDetectionResult result = _faceDetector->GetResult();

  // Run tracking to assign persistent IDs
  if (_faceTrackingEnabled && _faceTracker)
  {
    _faceTracker->Update(result);
  }

  auto perfT1 = std::chrono::steady_clock::now();

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

  if (PerfEnabled())
  {
    auto perfT2 = std::chrono::steady_clock::now();
    long long detectUs =
      std::chrono::duration_cast<std::chrono::microseconds>(perfT1 - perfT0).count();
    long long smileUs =
      std::chrono::duration_cast<std::chrono::microseconds>(perfT2 - perfT1).count();
    perfAnalyzed++;
    perfDetectUs += detectUs;
    perfSmileUs += smileUs;
    perfFaces += static_cast<int>(result.faces.size());
    long long prevMax = perfDetectMaxUs.load();
    while (detectUs > prevMax &&
           !perfDetectMaxUs.compare_exchange_weak(prevMax, detectUs)) {}
    PerfReport();
  }

  // Update result (thread-safe)
  {
    std::lock_guard<std::mutex> lock(_resultMutex);
    _lastResult = result;
  }

  // Notify callback
  _functor.RunFunction(PLAFunctionCode::FrameAnalyzer::OnComplete, AssignAgent());
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
