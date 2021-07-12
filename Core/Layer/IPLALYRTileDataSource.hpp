#ifndef ANHR_IPLALYRTILEDATASOURCE_HPP
#define ANHR_IPLALYRTILEDATASOURCE_HPP

class IPLALYRTileDataSource
{
public:
  virtual void Init() = 0;
  virtual PLAVec2s GetChunkSize() const = 0;
  virtual PLATileChip GetTileChip(PLASize aY, PLASize aX) const = 0;
};

#endif //ANHR_IPLALYRTILEDATASOURCE_HPP
