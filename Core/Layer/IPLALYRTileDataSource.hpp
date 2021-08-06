#ifndef ANHR_IPLALYRTILEDATASOURCE_HPP
#define ANHR_IPLALYRTILEDATASOURCE_HPP

#include "Type/PLAType.hpp"
#include "Type/PLAVector.hpp"
#include "Type/PLATile.hpp"

using PLATileDataSize = PLAVec2s;
static const PLATileDataSize kPLATileDataSizeNone = kPLAVec2sNone;
static const PLATileDataSize kPLATileDataSizeNorm = kPLAVec2sNorm;

using PLATileDataAddress = PLAVec2s;
static const PLATileDataAddress kPLATileDataAddressNone = kPLAVec2sNone;
static const PLATileDataAddress kPLATileDataAddressNorm = kPLAVec2sNorm;

using PLATileChunkSize = PLAVec2s;
static const PLATileChunkSize kPLATileChunkSizeNone = kPLAVec2sNone;
static const PLATileChunkSize kPLATileChunkSizeNorm = kPLAVec2sNorm;

using PLATileChunkAddress = PLAVec2s;
static const PLATileChunkAddress kPLATileChunkAddressNone = kPLAVec2sNone;
static const PLATileChunkAddress kPLATileChunkAddressNorm = kPLAVec2sNorm;

class IPLALYRTileDataSource
{
public:
  virtual PLATileDataSize GetDataSize() const = 0;
  virtual PLATileDataAddress GetDataAddress() const = 0;
  virtual PLATileChunkSize GetChunkSize() const = 0;
  virtual PLATileChunkAddress GetChunkAddress() const = 0;
  virtual const PLATileChip &GetTileChip(const PLAVec2s &aAddress) const = 0;
};

#endif //ANHR_IPLALYRTILEDATASOURCE_HPP
