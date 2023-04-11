#ifndef PLAIN_PLATILE_HPP
#define PLAIN_PLATILE_HPP

#include "PLAPRMVector.hpp"
#include "PLAPRMColor.hpp"
#include "Primitive/PLAPRMType.hpp"
#include "Grain/Primitive/GRAPRMTile.hpp"

using PLATile = GRAPRMTile<PLAFloat>;
static const PLATile kPLATileNone = PLATile(kPLAVec2sNone, kPLAVec2fNone);
static const PLATile kPLATileNorm = PLATile(kPLAVec2sNone, kPLAVec2fNorm);

using PLATileChipCode = PLAUInt;
static const PLATileChipCode kPLATileChipCodeNone = kPLAUIntUndefined;

struct PLATileChip {
  PLATileChipCode code = kPLATileChipCodeNone;
  PLAColor color = kPLAColorWhite;
  PLAVec2f offset = kPLAVec2fNone;

  PLATileChip() {};
  PLATileChip(PLATileChipCode aCode,
              const PLAColor &aColor, const PLAVec2f &aOffset):
              code(aCode), color(aColor), offset(aOffset) {};
  ~PLATileChip() {};
};
static const PLATileChip kPLATileChipNone = PLATileChip();

#endif //PLAIN_PLATILE_HPP
