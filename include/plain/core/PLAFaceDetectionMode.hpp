#ifndef PLAIN_ENGINE_PLAFACEDETECTIONMODE_HPP
#define PLAIN_ENGINE_PLAFACEDETECTIONMODE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"

enum class PLAFaceDetectionMode : PLAInt
{
  EveryFrame,
  Interval,
  OnDemand,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLAFACEDETECTIONMODE_HPP
