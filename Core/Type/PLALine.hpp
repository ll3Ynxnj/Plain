#ifndef PLAIN_PLALINE_HPP
#define PLAIN_PLALINE_HPP

#include "Grain/Type/GRALine.hpp"

using PLALine = GRALine<PLAFloat>;
static const PLALine kPLALineNone = PLALine(kPLAVec2None, kPLAVec2None);
static const PLALine kPLALineNorm = PLALine(kPLAVec2None, kPLAVec2Norm);

#endif //PLAIN_PLALINE_HPP
