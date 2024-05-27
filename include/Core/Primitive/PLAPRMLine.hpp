#ifndef PLAIN_PLALINE_HPP
#define PLAIN_PLALINE_HPP

#include "Core/Primitive/PLAPRMType.hpp"
#include "Core/Primitive/PLAPRMVector.hpp"
#include "Primitive/GRAPRMLine.hpp"

using PLALine = GRAPRMLine<PLAFloat>;
static const PLALine kPLALineNone = PLALine(kPLAVec2fNone, kPLAVec2fNone);
static const PLALine kPLALineNorm = PLALine(kPLAVec2fNone, kPLAVec2fNorm);

#endif //PLAIN_PLALINE_HPP
