#include "PLALYRTile.hpp"
#include "PLACollision.hpp"

PLALYRTile *PLALYRTile::Create(const PLAVec2 &aOffset,
                               const std::string &aImageName,
                               const GRAVec2<PLASize> &aMapSize,
                               const GRAVec2<PLASize> &aChipSize,
                               const IPLALYRTileDataSource *aDataSource)
{
  PLAImage *image = PLAImage::CreateRaw(aImageName);
  PLALYRTile *layer =
    new PLALYRTile(aOffset, image, aMapSize, aChipSize, aDataSource);
  PLAObject::Bind(layer);
  return layer;
}

PLALYRTile::PLALYRTile(const PLAVec2 &aOffset, const PLAImage *aImage,
                       const GRAVec2<PLASize> &aTileSize,
                       const GRAVec2<PLASize> &aChipSize,
                       const IPLALYRTileDataSource *aDataSource) :
  PLALayer(PLALayerType::Tile, PLAVec3(aOffset.x, aOffset.y, 0)),
  _image(aImage), _tileSize(aTileSize),
  _chipSize(aChipSize), _dataSource(aDataSource)
{
  for (PLASize y = 0; y < aTileSize.y; y++) {
    std::vector<PLAMotionHolder *> holders(0);
    for (PLASize x = 0; x < aTileSize.x; x++) {
      holders.push_back(new PLAMotionHolder());
    }
    _motionHolders.push_back(holders);
  }
};

PLALYRTile::~PLALYRTile()
{
  for (PLASize y = 0; y < _tileSize.y; y++) {
    for (PLASize x = 0; x < _tileSize.x; x++) {
      GRA_DELETE(_motionHolders[y][x]);
    }
  }
};

void PLALYRTile::UpdateMotion()
{
  for (PLASize y = 0; y < _tileSize.y; y++) {
    std::vector<PLAMotionHolder> holders(0);
    for (PLASize x = 0; x < _tileSize.x; x++) {
      _motionHolders[y][x]->UpdateMotion();
    }
  }
}

void PLALYRTile::AddMotion(const PLAVec2s &aAddress, PLAMotion *aMotion)
{
  _motionHolders[aAddress.y][aAddress.x]->AddMotion(aMotion);
};

void PLALYRTile::AddMotions(const PLAVec2s &aAddress,
                            const std::vector<PLAMotion *> &aMotions)
{
  _motionHolders[aAddress.y][aAddress.x]->AddMotions(aMotions);
};

/*
void PLALYRTile::SetMotion(const PLAVec2s &aAddress, PLAMotion *aMotion)
{
  _motionHolders[aAddress.y][aAddress.x].SetMotion(aMotion);
};
 */

const PLAMotion *PLALYRTile::GetMotion(const PLAVec2s &aAddress) const
{
  return _motionHolders[aAddress.y][aAddress.x]->GetMotion();
  /*
  if (_motionHolders.contains(aAddress.y))
  {
    const std::map<PLASize, PLAMotionHolder> mtnY = _motionHolders.at(aAddress.y);
    if (mtnY.contains(aAddress.x)) { return mtnY.at(aAddress.x).GetMotion(); }
    else { return PLAMotion::kNone; }
  }
  else
  {
    return PLAMotion::kNone;
  }
   */
};

PLAVec3 PLALYRTile::GetSize() const
{
  return PLAVec3(_chipSize.x * _tileSize.x, _chipSize.y * _tileSize.y, 0);
}

void PLALYRTile::GetSize(PLAVec3 *aSize) const
{
  aSize->x = _chipSize.x * _tileSize.x;
  aSize->y = _chipSize.y * _tileSize.y;
  aSize->z = 0;
}

void PLALYRTile::SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot)
{
  return;
}

bool PLALYRTile::IsCollideWithPoint(const PLAPoint &aPoint) const
{
  return PLACollision::IsCollideWithPointAndRect(aPoint, this->GetRect());
}

bool PLALYRTile::IsCollideWithLine(const PLALine &aLine) const
{
  return PLACollision::IsCollideWithLineAndRect(aLine, this->GetRect());
}

bool PLALYRTile::IsCollideWithRect(const PLARect &aRect) const
{
  return PLACollision::IsCollideWithRectAndRect(this->GetRect(), aRect);
}

bool PLALYRTile::IsCollideWithCircle(const PLACircle &aCircle) const
{
  return PLACollision::IsCollideWithRectAndCircle(this->GetRect(), aCircle);
}

PLARect PLALYRTile::GetRect() const
{
  PLAVec3 offset = this->GetOffset();
  PLAVec3 size = this->GetSize();
  return { { offset.x, offset.y }, { size.x, size.y } };
}
