#ifndef PLAIN_PLATRANSFORM_HPP
#define PLAIN_PLATRANSFORM_HPP

#include "PLAPRMVector.hpp"
#include "Grain/Primitive/GRAPRMTransform.hpp"

using PLATransform = GRAPRMTransform<PLAFloat>;
static const PLATransform kPLATransformNone =
  PLATransform(kPLAVec3None, kPLAVec3None, kPLAVec3None);
static const PLATransform kPLATransformNorm =
  PLATransform(kPLAVec3None, kPLAVec3None, kPLAVec3Norm);

#endif //PLAIN_PLATRANSFORM_HPP
