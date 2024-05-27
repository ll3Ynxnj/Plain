#ifndef PLAIN_PLACIRCLE_HPP
#define PLAIN_PLACIRCLE_HPP

#include "Core/Primitive/PLAPRMType.hpp"
#include "Core/Primitive/PLAPRMVector.hpp"
#include "Primitive/GRAPRMCircle.hpp"

using PLACircle = GRAPRMCircle<PLAFloat>;
static const PLACircle kPLACircleNone = PLACircle(kPLAVec2fNone, 0);
static const PLACircle kPLACircleNorm = PLACircle(kPLAVec2fNone, 1);

#endif //PLAIN_PLACIRCLE_HPP
