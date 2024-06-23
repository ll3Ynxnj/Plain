#ifndef PLAIN_PLALYRTILE_HPP
#define PLAIN_PLALYRTILE_HPP

#include "plain/core/object/layer/PLAOBJLayer.hpp"
#include "plain/core/primitive/PLAPRMTile.hpp"
#include "plain/core/object/timeline/PLATimelineHolder.hpp"
#include "plain/core/object/timeline/PLATMLMotion.hpp"

#include "plain/core/object/layer/IPLATileLayerDataSource.hpp"

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

  void SetTileSize(const GRAVec2<PLASize> &aTileSize)
  { _tileSize = aTileSize; };
  void SetDataSource(const IPLATileLayerDataSource *aDataSource)
  { _dataSource = aDataSource; }

  /// PLAOBJLayer //////////////////////////////////////////////////////////////

  PLAVec3f GetSize() const override;
  void GetSize(PLAVec3f *aSize) const override;
  void SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot) override;

  void SetImageClip(PLAOBJImageClip *aImageClip) override { return; } // Stab
  void SetVideoClip(PLAOBJVideoClip *aVideoClip) override { return; } // Stab

  bool IsCollideWithPoint(const PLAPoint &aPoint) const override;
  bool IsCollideWithLine(const PLALine &aLine) const override;
  bool IsCollideWithRect(const PLARect &aRect) const override;
  bool IsCollideWithCircle(const PLACircle &aCircle) const override;
};

#endif //PLAIN_PLALYRTILE_HPP
