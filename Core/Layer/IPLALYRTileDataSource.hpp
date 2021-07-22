#ifndef ANHR_IPLALYRTILEDATASOURCE_HPP
#define ANHR_IPLALYRTILEDATASOURCE_HPP

#include "Type/PLAType.hpp"
#include "Type/PLAVector.hpp"

class IPLALYRTileDataSource
{
public:
  virtual PLAVec2s GetDataSize() const = 0;
  virtual PLAVec2s GetDataAddress() const = 0;
  virtual PLAVec2s GetChunkSize() const = 0;
  virtual PLAVec2s GetChunkAddress() const = 0;
  virtual PLATileChip GetTileChip(PLASize aY, PLASize aX) const = 0;
};

#endif //ANHR_IPLALYRTILEDATASOURCE_HPP
