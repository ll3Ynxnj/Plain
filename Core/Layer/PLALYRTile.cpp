#include "PLALYRTile.hpp"
#include "PLACollision.hpp"

PLALYRTile *PLALYRTile::Create(const PLAVec2 &aOffset,
                               const std::string &aImageName,
                               const GRAVec2<PLASize> &aTileSize,
                               const GRAVec2<PLASize> &aChipSize,
                               const IPLALYRTileDataSource *aDataSource)
{
  PLAImage *image = PLAImage::CreateRaw(aImageName);

  std::vector<std::vector<PLANode::Holder *>> motionHolders(0);
  for (PLASize y = 0; y < aTileSize.y; y++) {
    std::vector<PLANode::Holder *> holders(0);
    for (PLASize x = 0; x < aTileSize.x; x++) {
      holders.push_back(new PLANode::Holder());//PLAMotion::Create()));
    }
    motionHolders.push_back(holders);
  }
  PLALYRTile *layer =
    new PLALYRTile(aOffset, image, aTileSize, aChipSize, aDataSource, motionHolders);
  layer->Bind();
  return layer;
}

PLALYRTile::PLALYRTile(const PLAVec2 &aOffset, const PLAImage *aImage,
                       const GRAVec2<PLASize> &aTileSize,
                       const GRAVec2<PLASize> &aChipSize,
                       const IPLALYRTileDataSource *aDataSource,
                       const std::vector<std::vector<PLANode::Holder *>> &aNodeHolders) :
PLALayer(PLALayerType::Tile, PLAVec3(aOffset.x, aOffset.y, 0)),
  _image(aImage), _tileSize(aTileSize),
  _chipSize(aChipSize), _dataSource(aDataSource),
  _nodeHolders(aNodeHolders)
{
  /*
  for (PLASize y = 0; y < aTileSize.y; y++) {
    std::vector<PLAMotionHolder *> holders(0);
    for (PLASize x = 0; x < aTileSize.x; x++) {
      holders.push_back(new PLAMotionHolder());
    }
    _motionHolders.push_back(holders);
  }
   */
};

PLALYRTile::~PLALYRTile()
{
  /*
  for (PLASize y = 0; y < _tileSize.y; y++) {
    for (PLASize x = 0; x < _tileSize.x; x++) {
      GRA_DELETE(_motionHolders[y][x]);
    }
  }
  */
};

/*
void PLALYRTile::UpdateMotionProperties()
{
  for (PLASize y = 0; y < _tileSize.y; y++) {
    for (PLASize x = 0; x < _tileSize.x; x++) {
      _motionHolders[y][x]->UpdateMotionProperties();
    }
  }
}
 */

void PLALYRTile::AddMotion(const PLAVec2s &aAddress, PLAMotion *aMotion)
{
  _nodeHolders[aAddress.y][aAddress.x]->AddNode(aMotion);
};

void PLALYRTile::AddMotions(const PLAVec2s &aAddress,
                            const std::vector<PLAMotion *> &aMotions)
{
  for (PLAMotion *motion: aMotions)
  {
    _nodeHolders[aAddress.y][aAddress.x]->AddNode(motion);
  }
};

/*
void PLALYRTile::SetMotion(const PLAVec2s &aAddress, PLAMotion *aMotion)
{
  _motionHolders[aAddress.y][aAddress.x].SetMotion(aMotion);
};
 */

const PLAMotion *PLALYRTile::GetMotion(const PLAVec2s &aAddress) const
{
  return static_cast<const PLAMotion *>
  (_nodeHolders[aAddress.y][aAddress.x]->GetNode());
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
