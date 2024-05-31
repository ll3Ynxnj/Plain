#ifndef PLAIN_PLALINE_HPP
#define PLAIN_PLALINE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"
#include "plain/core/primitive/PLAPRMVector.hpp"
#include "grain/primitive/GRAPRMLine.hpp"

using PLALine = GRAPRMLine<PLAFloat>;
static const PLALine kPLALineNone = PLALine(kPLAVec2fNone, kPLAVec2fNone);
static const PLALine kPLALineNorm = PLALine(kPLAVec2fNone, kPLAVec2fNorm);

#endif //PLAIN_PLALINE_HPP
