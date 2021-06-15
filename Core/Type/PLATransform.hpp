#ifndef ANHR_PLATRANSFORM_HPP
#define ANHR_PLATRANSFORM_HPP

#include "PLAVector.hpp"
#include "Grain/Type/GRATransform.hpp"

using PLATransform = GRATransform<PLAFloat>;
static const PLATransform kPLATransformNone =
  PLATransform(kPLAVec3None, kPLAVec3None, kPLAVec3None);
static const PLATransform kPLATransformNorm =
  PLATransform(kPLAVec3None, kPLAVec3None, kPLAVec3Norm);

#endif //ANHR_PLATRANSFORM_HPP
