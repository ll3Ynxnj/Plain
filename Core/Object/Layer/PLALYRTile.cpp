#include "PLALYRTile.hpp"
#include "Core/Library/PLALIBCollision.hpp"

PLALYRTile *PLALYRTile::Create(const PLAVec2f &aOffset,
                               const std::string &aImageName,
                               const GRAVec2<PLASize> &aTileSize,
                               const GRAVec2<PLASize> &aChipSize,
                               const IPLATileLayerDataSource *aDataSource)
{
  /*
  std::vector<std::vector<PLATimelineHolder *>> motionHolders(0);
  for (PLASize y = 0; y < aTileSize.y; y++) {
    std::vector<PLATimelineHolder *> holders(0);
    for (PLASize x = 0; x < aTileSize.x; x++) {
      holders.push_back(new PLATimelineHolder());//PLATMLMotionNode::Create()));
    }
    motionHolders.push_back(holders);
  }
   */
  PLALYRTile *layer =
    new PLALYRTile(aOffset, aImageName, aTileSize, aChipSize, aDataSource);//, motionHolders);
  layer->Bind();
  return layer;
}

PLALYRTile::PLALYRTile(const PLAVec2f &aOffset, const std::string &aImageName,
                       const GRAVec2<PLASize> &aTileSize,
                       const GRAVec2<PLASize> &aChipSize,
                       const IPLATileLayerDataSource *aDataSource) ://,
                       //const std::vector<std::vector<PLATimelineHolder *>> &aNodeHolders) :
  PLAOBJLayer(PLAOBJLayerType::Tile, PLAVec3f(aOffset.x, aOffset.y, 0)),
  _tileSize(aTileSize),
  _chipSize(aChipSize), _dataSource(aDataSource)//,
  //_nodeHolders(aNodeHolders)
{
  _image = PLAOBJImage::CreateRaw(aImageName);
  //std::vector<std::vector<PLATimelineHolder *>> motionHolders(0);
  for (PLASize y = 0; y < aTileSize.y; y++) {
    std::vector<PLATimelineHolder *> holders(0);
    for (PLASize x = 0; x < aTileSize.x; x++) {
      holders.push_back(new PLATimelineHolder());//PLATMLMotionNode::Create()));
    }
    _timelineHolders.push_back(holders);
  }
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

void PLALYRTile::AddMotionThread(const PLAVec2s &aAddress,
                                 PLATMLMotion *aThread)
{
  _timelineHolders[aAddress.y][aAddress.x]->PLATimelineHolder::AddThread(aThread);
};

/*
void PLALYRTile::AddMotions(const PLAVec2s &aAddress,
                            const std::vector<PLATMLMotionNode *> &aMotions)
{
  for (PLATMLMotionNode *motion: aMotions)
  {
    _nodeHolders[aAddress.y][aAddress.x]->AddSubNode(motion);
  }
};
 */

/*
void PLALYRTile::SetMotion(const PLAVec2s &aAddress, PLATMLMotionNode *aMotion)
{
  _motionHolders[aAddress.y][aAddress.x].SetMotion(aMotion);
};
 */

const PLATMLMotion *PLALYRTile::GetMotionThread(const PLAVec2s &aAddress) const
{
  return static_cast<const PLATMLMotion *>
  (_timelineHolders[aAddress.y][aAddress.x]->GetNodeThread());
  /*
  if (_motionHolders.contains(aAddress.y))
  {
    const std::map<PLASize, PLAMotionHolder> mtnY = _motionHolders.at(aAddress.y);
    if (mtnY.contains(aAddress.x)) { return mtnY.at(aAddress.x).GetMotion(); }
    else { return PLATMLMotionNode::kNone; }
  }
  else
  {
    return PLATMLMotionNode::kNone;
  }
   */
};

PLAVec3f PLALYRTile::GetSize() const
{
  return PLAVec3f(_chipSize.x * _tileSize.x, _chipSize.y * _tileSize.y, 0);
}

void PLALYRTile::GetSize(PLAVec3f *aSize) const
{
  aSize->x = _chipSize.x * _tileSize.x;
  aSize->y = _chipSize.y * _tileSize.y;
  aSize->z = 0;
}

void PLALYRTile::SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot)
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
  PLAVec3f offset = this->GetOffset();
  PLAVec3f size = this->GetSize();
  return { { offset.x, offset.y }, { size.x, size.y } };
}
