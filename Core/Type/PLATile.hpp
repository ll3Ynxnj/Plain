#ifndef PLAIN_PLATILE_HPP
#define PLAIN_PLATILE_HPP

#include "PLAVector.hpp"
#include "PLAColor.hpp"
#include "Type/PLAType.hpp"
#include "Grain/Type/GRATile.hpp"

using PLATile = GRATile<PLAFloat>;
static const PLATile kPLATileNone = PLATile(kPLAVec2sNone, kPLAVec2None);
static const PLATile kPLATileNorm = PLATile(kPLAVec2sNone, kPLAVec2Norm);

using PLATileChipCode = PLAUInt;
static const PLATileChipCode kPLATileChipCodeNone = kPLAUIntUndefined;

struct PLATileChip {
  PLATileChipCode code = kPLATileChipCodeNone;
  PLAColor color = kPLAColorWhite;
  PLAVec2 offset = kPLAVec2None;

  PLATileChip() {};
  PLATileChip(PLATileChipCode aCode,
              const PLAColor &aColor, const PLAVec2 &aOffset):
              code(aCode), color(aColor), offset(aOffset) {};
  ~PLATileChip() {};
};
static const PLATileChip kPLATileChipNone = PLATileChip();

#endif //PLAIN_PLATILE_HPP
