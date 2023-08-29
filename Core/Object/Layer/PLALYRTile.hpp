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
  //std::vector<std::vector<PLATimelineHolder *>> _timelineHolders =
  //  std::vector<std::vector<PLATimelineHolder *>>(0);

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

  //void AddMotionThread(const PLATileDataAddress &aAddress, PLATMLMotion *aThread);

  const PLAOBJImage *GetImage() const { return _image; };
  const PLAVec2s &GetTileSize() const { return _tileSize; };
  const PLAVec2s &GetChipSize() const { return _chipSize; };
  const PLATileChip GetChip(const PLATileDataAddress &aAddress) const
  { return _dataSource->GetTileChip(aAddress); }
  const PLATMLMotion *GetMotion(const PLATileDataAddress &aAddress) const;

  PLASize GetNumberOfChips() const { return _tileSize.x * _tileSize.y; };

  PLATileDataAddress GetDataAddress() const { return _dataSource->GetDataAddress(); };

  PLARect GetRect() const;

  void SetDataSource(const IPLATileLayerDataSource *aDataSource)
  { _dataSource = aDataSource; }

  /// PLAOBJLayer //////////////////////////////////////////////////////////////

  virtual PLAVec3f GetSize() const override;
  virtual void GetSize(PLAVec3f *aSize) const override;
  virtual void SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot) override;

  virtual void SetImageClip(PLAOBJImageClip *aImageClip) override { return; } // Stab

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const override;
  virtual bool IsCollideWithLine(const PLALine &aLine) const override;
  virtual bool IsCollideWithRect(const PLARect &aRect) const override;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const override;
};

#endif //PLAIN_PLALYRTILE_HPP
