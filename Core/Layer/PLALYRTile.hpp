#ifndef PLAIN_PLALYRTILE_HPP
#define PLAIN_PLALYRTILE_HPP

#include "PLALayer.hpp"
#include "Type/PLATile.hpp"

#include "IPLALYRTileDataSource.hpp"

class PLALYRTile : public PLALayer
{
  const PLAImage *_image = nullptr;
  GRAVec2<PLASize> _tileSize = GRAVec2<PLASize>(0);
  GRAVec2<PLASize> _chipSize = GRAVec2<PLASize>(0);
  const IPLALYRTileDataSource *_dataSource = nullptr;

protected:
  PLALYRTile(const PLAVec2 &aOffset, const PLAImage *aImage,
             const GRAVec2<PLASize> &aTileSize,
             const GRAVec2<PLASize> &aChipSize,
             const IPLALYRTileDataSource *aDataSource) :
    PLALayer(PLALayerType::Tile, PLAVec3(aOffset.x, aOffset.y, 0)),
    _image(aImage), _tileSize(aTileSize),
    _chipSize(aChipSize), _dataSource(aDataSource) {};

public:
  static PLALYRTile *Create(const PLAVec2 &aOffset,
                            const std::string &aImageName,
                            const GRAVec2<PLASize> &aMapSize,
                            const GRAVec2<PLASize> &aChipSize,
                            const IPLALYRTileDataSource *aDataSource);

  PLALYRTile() = delete;

  virtual ~PLALYRTile() {};

  const PLAImage *GetImage() const { return _image; };
  const PLAVec2s &GetTileSize() const { return _tileSize; };
  const PLAVec2s &GetChipSize() const { return _chipSize; };
  const PLATileChip &GetChip(PLAUInt aY, PLAUInt aX) const
  { return _dataSource->GetTileChip(aY, aX); }

  PLASize GetNumberOfChips() const { return _tileSize.x * _tileSize.y; };

  //void RefreshChips(const std::vector<std::vector<PLATileChip>> &aChips);

  const PLAVec2s &GetDataAddress() const
  { return _dataSource->GetDataAddress(); };

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;

  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  PLARect GetRect() const;
};

#endif //PLAIN_PLALYRTILE_HPP
