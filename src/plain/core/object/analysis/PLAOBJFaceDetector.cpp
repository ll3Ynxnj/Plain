#include "plain/opencv/PLAOpenCVCascadeFaceDetector.hpp"
#include "plain/opencv/PLAOpenCVYuNetFaceDetector.hpp"
#include "plain/core/object/analysis/PLAOBJFaceDetector.hpp"
#include "plain/core/object/PLAOBJError.hpp"

PLAOBJFaceDetector *PLAOBJFaceDetector::Create(PLAFaceDetectorType aType)
{
  switch (aType)
  {
    case PLAFaceDetectorType::OpenCVCascade:
      return PLAOpenCVCascadeFaceDetector::Create();
    case PLAFaceDetectorType::YuNet:
      return PLAOpenCVYuNetFaceDetector::Create();
    case PLAFaceDetectorType::MediaPipe:
    case PLAFaceDetectorType::TFLite:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Face detector type not yet implemented.");
      return nullptr;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Unexpected face detector type detected.");
      return nullptr;
  }
}

PLAOBJFaceDetector::PLAOBJFaceDetector() :
  PLAObject(PLAObjectType::FaceDetector, "== PLAOBJFaceDetector ==")
{
}

PLAOBJFaceDetector::~PLAOBJFaceDetector()
{
}

PLAFaceDetectionResult PLAOBJFaceDetector::GetResult() const
{
  std::lock_guard<std::mutex> lock(_resultMutex);
  return _result;
}

void PLAOBJFaceDetector::SetMode(PLAFaceDetectionMode aMode)
{
  _mode = aMode;
}

void PLAOBJFaceDetector::SetDetectionInterval(PLAInt aInterval)
{
  _detectionInterval = (aInterval > 0) ? aInterval : 1;
}

bool PLAOBJFaceDetector::ShouldDetect()
{
  ++_frameCounter;

  switch (_mode)
  {
    case PLAFaceDetectionMode::EveryFrame:
      return true;
    case PLAFaceDetectionMode::Interval:
      return (_frameCounter % _detectionInterval) == 0;
    case PLAFaceDetectionMode::OnDemand:
      return false;
    case PLAFaceDetectionMode::None:
      return false;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "Unknown detection mode.");
      return false;
  }
}

void PLAOBJFaceDetector::UpdateResult(const PLAFaceDetectionResult &aResult)
{
  std::lock_guard<std::mutex> lock(_resultMutex);
  _result = aResult;
}
