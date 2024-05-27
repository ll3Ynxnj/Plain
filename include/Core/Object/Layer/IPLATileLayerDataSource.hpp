#ifndef PLAIN_IPLATILELAYERDATASOURCE_HPP
#define PLAIN_IPLATILELAYERDATASOURCE_HPP

#include "Core/Primitive/PLAPRMType.hpp"
#include "Core/Primitive/PLAPRMVector.hpp"
#include "Core/Primitive/PLAPRMTile.hpp"

class PLATMLMotion;
class PLAAGTMotion;

using PLATileDataSize = PLAVec2s;
static const PLATileDataSize kPLATileDataSizeUndefined = kPLAVec2sUndefined;
static const PLATileDataSize kPLATileDataSizeNone      = kPLAVec2sNone;
static const PLATileDataSize kPLATileDataSizeNorm      = kPLAVec2sNorm;

using PLATileDataAddress = PLAVec2i;
static const PLATileDataAddress kPLATileDataAddressUndefined = kPLAVec2iUndefined;
static const PLATileDataAddress kPLATileDataAddressNone      = kPLAVec2iNone;
static const PLATileDataAddress kPLATileDataAddressNorm      = kPLAVec2iNorm;

using PLATileChunkSize = PLAVec2s;
static const PLATileChunkSize kPLATileChunkSizeUndefined = kPLAVec2sUndefined;
static const PLATileChunkSize kPLATileChunkSizeNone      = kPLAVec2sNone;
static const PLATileChunkSize kPLATileChunkSizeNorm      = kPLAVec2sNorm;

using PLATileChunkAddress = PLAVec2i;
static const PLATileChunkAddress kPLATileChunkAddressUndefined = kPLAVec2iUndefined;
static const PLATileChunkAddress kPLATileChunkAddressNone      = kPLAVec2iNone;
static const PLATileChunkAddress kPLATileChunkAddressNorm      = kPLAVec2iNorm;

class IPLATileLayerDataSource
{
public:
  virtual PLATileDataSize GetDataSize() const = 0;
  virtual PLATileDataAddress GetDataAddress() const = 0;
  virtual PLATileChunkSize GetChunkSize() const = 0;
  virtual PLATileChunkAddress GetChunkAddress() const = 0;
  virtual const PLATileChip GetTileChip(const PLATileDataAddress &aAddress) const = 0;

  virtual const PLATMLMotion *GetMotion(const PLATileDataAddress &aAddress) const = 0;
  virtual void AddMotionThread(const PLATileDataAddress &aAddress, PLATMLMotion *aThread) = 0;
  virtual void AddMotionThread(const PLATileDataAddress &aAddress, const PLAAGTMotion &aThread) = 0;
};

#endif //PLAIN_IPLATILELAYERDATASOURCE_HPP
