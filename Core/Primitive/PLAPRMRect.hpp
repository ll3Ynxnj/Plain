#ifndef PLAIN_PLARECT_HPP
#define PLAIN_PLARECT_HPP

#include "PLAPRMVector.hpp"
#include "Grain/Primitive/GRAPRMRect.hpp"

using PLARect = GRAPRMRect<PLAFloat>;
static const PLARect kPLARectNone = PLARect(kPLAVec2fNone, kPLAVec2fNone);
static const PLARect kPLARectNorm = PLARect(kPLAVec2fNone, kPLAVec2fNorm);

#endif //PLAIN_PLARECT_HPP
