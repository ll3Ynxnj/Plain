#ifndef PLAIN_PLACIRCLE_HPP
#define PLAIN_PLACIRCLE_HPP

#include "Grain/Primitive/GRAPRMCircle.hpp"

using PLACircle = GRAPRMCircle<PLAFloat>;
static const PLACircle kPLACircleNone = PLACircle(kPLAVec2None, 0);
static const PLACircle kPLACircleNorm = PLACircle(kPLAVec2None, 1);

#endif //PLAIN_PLACIRCLE_HPP
