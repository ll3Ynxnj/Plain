#ifndef ANHR_PLAPOINT_HPP
#define ANHR_PLAPOINT_HPP

#include "Grain/Type/GRAPoint.hpp"

using PLAPoint = GRAPoint<PLAFloat>;
static const PLAPoint kPLAPointNone = PLAPoint(0);
static const PLAPoint kPLAPointNorm = PLAPoint(1);

#endif //ANHR_PLAPOINT_HPP
