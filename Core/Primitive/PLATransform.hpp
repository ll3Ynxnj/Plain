#ifndef PLAIN_PLATRANSFORM_HPP
#define PLAIN_PLATRANSFORM_HPP

#include "PLAVector.hpp"
#include "Grain/Primitive/GRATransform.hpp"

using PLATransform = GRATransform<PLAFloat>;
static const PLATransform kPLATransformNone =
  PLATransform(kPLAVec3None, kPLAVec3None, kPLAVec3None);
static const PLATransform kPLATransformNorm =
  PLATransform(kPLAVec3None, kPLAVec3None, kPLAVec3Norm);

#endif //PLAIN_PLATRANSFORM_HPP
