#ifndef ANHR_PLALINE_HPP
#define ANHR_PLALINE_HPP

#include "Grain/Type/GRALine.hpp"

using PLALine = GRALine<PLAFloat>;
static const PLALine kPLALineNone = PLALine(kPLAVec2None, kPLAVec2None);
static const PLALine kPLALineNorm = PLALine(kPLAVec2None, kPLAVec2Norm);

#endif //ANHR_PLALINE_HPP
