#ifndef ANHR_PLALYRTILE_HPP
#define ANHR_PLALYRTILE_HPP

#include <Layer/PLALayer.hpp>
#include <Type/PLAColor.hpp>

class PLALYRTile : public PLALayer
{
  std::vector<std::vector<PLAUInt>> _chips = std::vector<std::vector<PLAUInt>>();
  const PLAImage *_image = nullptr;
  GRAVec2<PLASize> _mapSize = GRAVec2<PLASize>(0);
  GRAVec2<PLASize> _chipSize = GRAVec2<PLASize>(0);
  PLASize _address = 0;

protected:
  PLALYRTile(const PLAVec2 &aOffset, const PLAImage *aImage,
             const GRAVec2<PLASize> &aMapSize,
             const GRAVec2<PLASize> &aChipSize, PLASize aAddress) :
    PLALayer(PLALayerType::Tile, PLAVec3(aOffset.x, aOffset.y, 0)),
    _chips(aMapSize.x * aMapSize.y), _image(aImage), _mapSize(aMapSize),
    _chipSize(aChipSize), _address(aAddress)
  {};

public:
  static PLALYRTile *Create(const PLAVec2 &aOffset,
                            const std::string &aImageName,
                            const GRAVec2<PLASize> &aMapSize,
                            const GRAVec2<PLASize> &aChipSize,
                            const PLASize aAddress);

  PLALYRTile() = delete;

  virtual ~PLALYRTile() {};

  PLAUInt GetChip(PLASize aX, PLASize aY) const { return _chips[aY][aX]; };
  const PLAImage *GetImage() const { return _image; };
  const GRAVec2<PLASize> &GetMapSize() const { return _mapSize; };
  const GRAVec2<PLASize> &GetChipSize() const { return _chipSize; };
  PLASize GetNumberOfChips() const { return _mapSize.x * _mapSize.y; }

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;
};

#endif //ANHR_PLALYRTILE_HPP
