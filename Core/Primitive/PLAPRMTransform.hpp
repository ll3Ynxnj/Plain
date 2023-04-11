#ifndef PLAIN_PLATRANSFORM_HPP
#define PLAIN_PLATRANSFORM_HPP

#include "PLAPRMVector.hpp"
#include "Grain/Primitive/GRAPRMTransform.hpp"

using PLATransform = GRAPRMTransform<PLAFloat>;
static const PLATransform kPLATransformNone =
  PLATransform(kPLAVec3fNone, kPLAVec3fNone, kPLAVec3fNone);
static const PLATransform kPLATransformNorm =
  PLATransform(kPLAVec3fNone, kPLAVec3fNone, kPLAVec3fNorm);

#endif //PLAIN_PLATRANSFORM_HPP
