#include "plain/core/object/analysis/PLAOBJSmileDetector.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include "plain/opencv/PLAOpenCVCascadeSmileDetector.hpp"
#include "plain/opencv/PLAOpenCVCNNSmileDetector.hpp"

PLAOBJSmileDetector *PLAOBJSmileDetector::Create(PLASmileDetectorType aType,
                                                  const PLAString &aName)
{
  PLAOBJSmileDetector *detector = nullptr;

  switch (aType)
  {
    case PLASmileDetectorType::OpenCVCascade:
      detector = PLAOpenCVCascadeSmileDetector::Create(aName);
      break;
    case PLASmileDetectorType::CNN:
      detector = PLAOpenCVCNNSmileDetector::Create(aName);
      break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Unknown smile detector type: %d", static_cast<int>(aType));
      return nullptr;
  }

  if (detector) {
    detector->Bind();
  }
  return detector;
}

PLAOBJSmileDetector *PLAOBJSmileDetector::Detector(const PLAString &aName)
{
  GRAOBJBinder<PLAOBJSmileDetector>::Error error(GRAOBJBinder<PLAOBJSmileDetector>::Error::None);
  return static_cast<PLAOBJSmileDetector *>(Manager::Instance()->RefItemWithName(aName, &error));
}

void PLAOBJSmileDetector::Bind()
{
  this->PLAObject::Bind();

  GRAOBJBinder<PLAOBJSmileDetector>::Error error(GRAOBJBinder<PLAOBJSmileDetector>::Error::None);
  PLAOBJSmileDetector::Manager::Instance()->Bind(this, &error);
  if (error != GRAOBJBinder<PLAOBJSmileDetector>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJSmileDetector binding. ERROR : %02d", error); }
}

void PLAOBJSmileDetector::Unbind()
{
  GRAOBJBinder<PLAOBJSmileDetector>::Error error(GRAOBJBinder<PLAOBJSmileDetector>::Error::None);
  PLAOBJSmileDetector::Manager::Instance()->Unbind(this, &error);
  if (error != GRAOBJBinder<PLAOBJSmileDetector>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJSmileDetector unbinding. ERROR : %02d", error); }

  this->PLAObject::Unbind();
}

PLAOBJSmileDetector::PLAOBJSmileDetector(const PLAString &aName)
  : PLAObject(PLAObjectType::SmileDetector, aName),
    GRAOBJBinder<PLAOBJSmileDetector>::Item(aName, Manager::Instance())
{
}

PLAOBJSmileDetector::~PLAOBJSmileDetector()
{
}

void PLAOBJSmileDetector::SetThreshold(PLAFloat aThreshold)
{
  _threshold = (aThreshold > 0.0f && aThreshold <= 1.0f) ? aThreshold : 0.5f;
}

// GRAOBJBinder::Item //////////////////////////////////////////////////////////

const char *PLAOBJSmileDetector::GetBinderItemTypeName() const
{
  static const char *kName = "PLAOBJSmileDetector";
  return kName;
}

// PLAOBJSmileDetector::Manager ////////////////////////////////////////////////

PLAOBJSmileDetector::Manager PLAOBJSmileDetector::Manager::_instance =
  PLAOBJSmileDetector::Manager();

PLAOBJSmileDetector::Manager::Manager() : GRAOBJBinder<PLAOBJSmileDetector>()
{
}

PLAOBJSmileDetector::Manager::~Manager()
{
}

void PLAOBJSmileDetector::Manager::Init()
{
  GRAOBJBinder<PLAOBJSmileDetector>::Init();
}
