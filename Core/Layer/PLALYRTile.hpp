#ifndef PLAIN_PLALYRTILE_HPP
#define PLAIN_PLALYRTILE_HPP

#include "PLALayer.hpp"
#include "Type/PLATile.hpp"
#include "Core/Node/PLANodeHolder.hpp"
#include "Core/Node/PLAMotionThread.hpp"

#include "IPLALYRTileDataSource.hpp"

class PLALYRTile : public PLALayer
{
  const PLAImage *_image = nullptr;
  GRAVec2<PLASize> _tileSize = GRAVec2<PLASize>(0);
  GRAVec2<PLASize> _chipSize = GRAVec2<PLASize>(0);
  const IPLALYRTileDataSource *_dataSource = nullptr;
  std::vector<std::vector<PLANodeHolder *>> _nodeHolders =
    std::vector<std::vector<PLANodeHolder *>>(0);

protected:
  PLALYRTile(const PLAVec2 &aOffset, const PLAImage *aImage,
             const GRAVec2<PLASize> &aTileSize,
             const GRAVec2<PLASize> &aChipSize,
             const IPLALYRTileDataSource *aDataSource,
             const std::vector<std::vector<PLANodeHolder *>> &aNodeHolders);

public:
  static PLALYRTile *Create(const PLAVec2 &aOffset,
                            const std::string &aImageName,
                            const GRAVec2<PLASize> &aTileSize,
                            const GRAVec2<PLASize> &aChipSize,
                            const IPLALYRTileDataSource *aDataSource);

  PLALYRTile() = delete;

  virtual ~PLALYRTile();

  //void UpdateMotionProperties() override;

  void AddMotionThread(const PLAVec2s &aAddress, PLAMotionThread *aThread);
  //void AddMotions(const PLAVec2s &aAddress,
  //                const std::vector<PLAMotion *> &aMotions);
  //void SetMotion(const PLAVec2s &aAddress, PLAMotion *aMotion);

  const PLAImage *GetImage() const { return _image; };
  const PLAVec2s &GetTileSize() const { return _tileSize; };
  const PLAVec2s &GetChipSize() const { return _chipSize; };
  const PLATileChip &GetChip(const PLAVec2s &aAddress) const
  { return _dataSource->GetTileChip(aAddress); }
  //const PLAMotion *GetMotion(const PLAVec2s &aAddress) const
  //{ return _motions[aAddress.y][aAddress.x]; }
  const PLAMotionThread *GetMotionThread(const PLAVec2s &aAddress) const;

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
