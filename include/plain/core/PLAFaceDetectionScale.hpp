#ifndef PLAIN_ENGINE_PLAFACEDETECTIONSCALE_HPP
#define PLAIN_ENGINE_PLAFACEDETECTIONSCALE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"

enum class PLAFaceDetectionScale : PLAInt
{
  Full,      // 1/1 - no resize
  Half,      // 1/2
  Quarter,   // 1/4
  Eighth,    // 1/8

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLAFACEDETECTIONSCALE_HPP
