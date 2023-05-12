#ifndef PLAIN_PLALYRTILE_HPP
#define PLAIN_PLALYRTILE_HPP

#include "PLAOBJLayer.hpp"
#include "Primitive/PLAPRMTile.hpp"
#include "Object/Timeline/PLATimelineHolder.hpp"
#include "Object/Timeline/PLATMLMotion.hpp"

#include "IPLATileLayerDataSource.hpp"

class PLALYRTile : public PLAOBJLayer
{
  const PLAOBJImage *_image = nullptr;
  GRAVec2<PLASize> _tileSize = GRAVec2<PLASize>(0);
  GRAVec2<PLASize> _chipSize = GRAVec2<PLASize>(0);
  const IPLATileLayerDataSource *_dataSource = nullptr;
  std::vector<std::vector<PLATimelineHolder *>> _timelineHolders =
    std::vector<std::vector<PLATimelineHolder *>>(0);

public:
  PLALYRTile(const PLAVec2f &aOffset, const std::string &aImageName,
             const GRAVec2<PLASize> &aTileSize,
             const GRAVec2<PLASize> &aChipSize,
             const IPLATileLayerDataSource *aDataSource);

  static PLALYRTile *Create(const PLAVec2f &aOffset,
                            const std::string &aImageName,
                            const GRAVec2<PLASize> &aTileSize,
                            const GRAVec2<PLASize> &aChipSize,
                            const IPLATileLayerDataSource *aDataSource);

  PLALYRTile() = delete;

  virtual ~PLALYRTile();

  void AddMotionThread(const PLAVec2s &aAddress, PLATMLMotion *aThread);

  const PLAOBJImage *GetImage() const { return _image; };
  const PLAVec2s &GetTileSize() const { return _tileSize; };
  const PLAVec2s &GetChipSize() const { return _chipSize; };
  const PLATileChip &GetChip(const PLAVec2s &aAddress) const
  { return _dataSource->GetTileChip(aAddress); }
  const PLATMLMotion *GetMotionThread(const PLAVec2s &aAddress) const;

  PLASize GetNumberOfChips() const { return _tileSize.x * _tileSize.y; };

  PLAVec2s GetDataAddress() const { return _dataSource->GetDataAddress(); };

  virtual PLAVec3f GetSize() const;
  virtual void GetSize(PLAVec3f *aSize) const;

  virtual void SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  PLARect GetRect() const;
};

#endif //PLAIN_PLALYRTILE_HPP
