#ifndef ANHR_PLALYRTILE_HPP
#define ANHR_PLALYRTILE_HPP

#include <Layer/PLALayer.hpp>
#include <Type/PLAColor.hpp>

using PLATileChip = PLAUInt;

class PLALYRTileDataSource: public PLAObject {
public:
  static PLALYRTileDataSource *Create();

  PLALYRTileDataSource(): PLAObject(PLAObjectType::LYRTileDataSource) {}

  virtual ~PLALYRTileDataSource() {};

  //-- Functors --//////////////////////////////////////////////////////////////
private:
  std::function<PLAVec2s()> _fGetChunkSize = []() -> PLAVec2s {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Undefined functor \"GetChunkSize\" was called.");
  };
  std::function<PLATileChip(PLASize, PLASize)> _fGetTileChip =
    [](PLASize, PLASize) -> PLATileChip {
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Undefined functor \"GetTileChip\" was called.");
  };

public:
  PLAVec2s GetChunkSize() const { return _fGetChunkSize(); };
  PLATileChip GetTileChip(PLASize aY, PLASize aX) const
  { return _fGetTileChip(aY, aX); };

  void SetFunc_GetChunkSize(const std::function<PLAVec2s()> &aF)
  { _fGetChunkSize = aF; };
  void SetFunc_GetTileChip(const std::function<PLATileChip(PLASize, PLASize)> &aF)
  { _fGetTileChip = aF; };

};

class PLALYRTile: public PLALayer
{
  const PLAImage *_image = nullptr;
  GRAVec2<PLASize> _mapSize = GRAVec2<PLASize>(0);
  GRAVec2<PLASize> _chipSize = GRAVec2<PLASize>(0);
  PLASize _address = 0;
  const PLALYRTileDataSource *_dataSource = nullptr;

protected:
  PLALYRTile(const PLAVec2 &aOffset, const PLAImage *aImage,
             const GRAVec2<PLASize> &aMapSize,
             const GRAVec2<PLASize> &aChipSize, PLASize aAddress,
             const PLALYRTileDataSource *aDataSource) :
    PLALayer(PLALayerType::Tile, PLAVec3(aOffset.x, aOffset.y, 0)),
    _image(aImage), _mapSize(aMapSize),
    _chipSize(aChipSize), _address(aAddress), _dataSource(aDataSource)
  {

  };

public:
  static PLALYRTile *Create(const PLAVec2 &aOffset,
                            const std::string &aImageName,
                            const GRAVec2<PLASize> &aMapSize,
                            const GRAVec2<PLASize> &aChipSize,
                            PLASize aAddress,
                            const PLALYRTileDataSource *aDataSource);

  PLALYRTile() = delete;

  virtual ~PLALYRTile() {};

  PLAUInt GetChip(PLASize aY, PLASize aX) const
  { return _dataSource->GetTileChip(aY, aX); };
  const PLAImage *GetImage() const { return _image; };
  const GRAVec2<PLASize> &GetMapSize() const { return _mapSize; };
  const GRAVec2<PLASize> &GetChipSize() const { return _chipSize; };
  PLASize GetNumberOfChips() const { return _mapSize.x * _mapSize.y; };

  //void RefreshChips(const std::vector<std::vector<PLATileChip>> &aChips);

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;
};

#endif //ANHR_PLALYRTILE_HPP
