#ifndef PLAIN_PLAPOINT_HPP
#define PLAIN_PLAPOINT_HPP

#include "Grain/Type/GRAPoint.hpp"

using PLAPoint = GRAPoint<PLAFloat>;
static const PLAPoint kPLAPointNone = PLAPoint(0);
static const PLAPoint kPLAPointNorm = PLAPoint(1);
static const PLAPoint kPLAPointUndefined = PLAPoint(kPLAFloatUndefined);

#endif //PLAIN_PLAPOINT_HPP
