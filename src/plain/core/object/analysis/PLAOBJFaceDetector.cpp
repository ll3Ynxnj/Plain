#include "plain/opencv/PLAOpenCVCascadeFaceDetector.hpp"
#include "plain/opencv/PLAOpenCVYuNetFaceDetector.hpp"
#include "plain/core/object/analysis/PLAOBJFaceDetector.hpp"
#include "plain/core/object/PLAOBJError.hpp"

PLAOBJFaceDetector *PLAOBJFaceDetector::Create(PLAFaceDetectorType aType,
                                                const PLAString &aName)
{
  PLAOBJFaceDetector *detector = nullptr;

  switch (aType)
  {
    case PLAFaceDetectorType::OpenCVCascade:
      detector = PLAOpenCVCascadeFaceDetector::Create(aName);
      break;
    case PLAFaceDetectorType::YuNet:
      detector = PLAOpenCVYuNetFaceDetector::Create(aName);
      break;
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

  if (detector) {
    detector->Bind();
  }
  return detector;
}

PLAOBJFaceDetector *PLAOBJFaceDetector::Detector(const PLAString &aName)
{
  GRAOBJBinder<PLAOBJFaceDetector>::Error error(GRAOBJBinder<PLAOBJFaceDetector>::Error::None);
  return static_cast<PLAOBJFaceDetector *>(Manager::Instance()->RefItemWithName(aName, &error));
}

void PLAOBJFaceDetector::Bind()
{
  this->PLAObject::Bind();

  GRAOBJBinder<PLAOBJFaceDetector>::Error error(GRAOBJBinder<PLAOBJFaceDetector>::Error::None);
  PLAOBJFaceDetector::Manager::Instance()->Bind(this, &error);
  if (error != GRAOBJBinder<PLAOBJFaceDetector>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJFaceDetector binding. ERROR : %02d", error); }
}

void PLAOBJFaceDetector::Unbind()
{
  GRAOBJBinder<PLAOBJFaceDetector>::Error error(GRAOBJBinder<PLAOBJFaceDetector>::Error::None);
  PLAOBJFaceDetector::Manager::Instance()->Unbind(this, &error);
  if (error != GRAOBJBinder<PLAOBJFaceDetector>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJFaceDetector unbinding. ERROR : %02d", error); }

  this->PLAObject::Unbind();
}

PLAOBJFaceDetector::PLAOBJFaceDetector(const PLAString &aName) :
  PLAObject(PLAObjectType::FaceDetector, aName),
  GRAOBJBinder<PLAOBJFaceDetector>::Item(aName, Manager::Instance())
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

// GRAOBJBinder::Item //////////////////////////////////////////////////////////

const char *PLAOBJFaceDetector::GetBinderItemTypeName() const
{
  static const char *kName = "PLAOBJFaceDetector";
  return kName;
}

// PLAOBJFaceDetector::Manager /////////////////////////////////////////////////

PLAOBJFaceDetector::Manager PLAOBJFaceDetector::Manager::_instance =
  PLAOBJFaceDetector::Manager();

PLAOBJFaceDetector::Manager::Manager() : GRAOBJBinder<PLAOBJFaceDetector>()
{
}

PLAOBJFaceDetector::Manager::~Manager()
{
}

void PLAOBJFaceDetector::Manager::Init()
{
  GRAOBJBinder<PLAOBJFaceDetector>::Init();
}
