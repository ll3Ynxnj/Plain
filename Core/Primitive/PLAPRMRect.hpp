#ifndef PLAIN_PLARECT_HPP
#define PLAIN_PLARECT_HPP

#include "PLAPRMVector.hpp"
#include "Grain/Primitive/GRAPRMRect.hpp"

using PLARect = GRAPRMRect<PLAFloat>;
static const PLARect kPLARectNone = PLARect(kPLAVec2None, kPLAVec2None);
static const PLARect kPLARectNorm = PLARect(kPLAVec2None, kPLAVec2Norm);

#endif //PLAIN_PLARECT_HPP
