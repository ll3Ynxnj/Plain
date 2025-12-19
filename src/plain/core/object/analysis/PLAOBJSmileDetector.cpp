#include "plain/core/object/analysis/PLAOBJSmileDetector.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include "plain/opencv/PLAOpenCVCascadeSmileDetector.hpp"

PLAOBJSmileDetector *PLAOBJSmileDetector::Create(PLASmileDetectorType aType)
{
  switch (aType)
  {
    case PLASmileDetectorType::OpenCVCascade:
      return PLAOpenCVCascadeSmileDetector::Create();
    case PLASmileDetectorType::CNN:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "CNN smile detector not yet implemented");
      return nullptr;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Unknown smile detector type: %d", static_cast<int>(aType));
      return nullptr;
  }
}

PLAOBJSmileDetector::PLAOBJSmileDetector()
  : PLAObject(PLAObjectType::None)
{
}

PLAOBJSmileDetector::~PLAOBJSmileDetector()
{
}

void PLAOBJSmileDetector::SetThreshold(PLAFloat aThreshold)
{
  _threshold = (aThreshold > 0.0f && aThreshold <= 1.0f) ? aThreshold : 0.5f;
}
