#ifndef PLAIN_ENGINE_PLAFACEDETECTORTYPE_HPP
#define PLAIN_ENGINE_PLAFACEDETECTORTYPE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"

enum class PLAFaceDetectorType : PLAInt
{
  OpenCVCascade,
  YuNet,
  MediaPipe,
  TFLite,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLAFACEDETECTORTYPE_HPP
