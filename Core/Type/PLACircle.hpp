#ifndef ANHR_PLACIRCLE_HPP
#define ANHR_PLACIRCLE_HPP

#include "Grain/Type/GRACircle.hpp"

using PLACircle = GRACircle<PLAFloat>;
static const PLACircle kPLACircleNone = PLACircle(kPLAVec2None, 0);
static const PLACircle kPLACircleNorm = PLACircle(kPLAVec2None, 1);

#endif //ANHR_PLACIRCLE_HPP
