#ifndef ANHR_PLARECT_HPP
#define ANHR_PLARECT_HPP

#include "PLAVector.hpp"
#include "Grain/Type/GRARect.hpp"

using PLARect = GRARect<PLAFloat>;
static const PLARect kPLARectNone = PLARect(kPLAVec2None, kPLAVec2None);
static const PLARect kPLARectNorm = PLARect(kPLAVec2None, kPLAVec2Norm);

#endif //ANHR_PLARECT_HPP