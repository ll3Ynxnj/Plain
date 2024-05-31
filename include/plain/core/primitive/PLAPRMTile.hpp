#ifndef PLAIN_PLATILE_HPP
#define PLAIN_PLATILE_HPP

#include "plain/core/primitive/PLAPRMVector.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"
#include "plain/core/primitive/PLAPRMType.hpp"
#include "grain/primitive/GRAPRMTile.hpp"

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
  PLATileChip(PLATileChipCode aCode): code(aCode) {};
  PLATileChip(PLATileChipCode aCode,
              const PLAColor &aColor, const PLAVec2f &aOffset):
              code(aCode), color(aColor), offset(aOffset) {};
  ~PLATileChip() {};
};
static const PLATileChip kPLATileChipNone = PLATileChip();

#endif //PLAIN_PLATILE_HPP
