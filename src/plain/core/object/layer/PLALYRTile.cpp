#include "plain/core/object/layer/PLALYRTile.hpp"
#include "plain/core/library/PLALIBCollision.hpp"

PLALYRTile *PLALYRTile::Create(const PLAVec2f &aOffset,
                               const std::string &aImageName,
                               const GRAVec2<PLASize> &aTileSize,
                               const GRAVec2<PLASize> &aChipSize,
                               const IPLATileLayerDataSource *aDataSource)
{
  PLALYRTile *layer =
    new PLALYRTile(aOffset, aImageName, aTileSize, aChipSize, aDataSource);
  layer->Bind();
  return layer;
}

PLALYRTile::PLALYRTile(const PLAVec2f &aOffset, const std::string &aImageName,
                       const GRAVec2<PLASize> &aTileSize,
                       const GRAVec2<PLASize> &aChipSize,
                       const IPLATileLayerDataSource *aDataSource) :
  PLAOBJLayer(PLALayerType::Tile, PLAVec3f(aOffset.x, aOffset.y, 0)),
  _tileSize(aTileSize),
  _chipSize(aChipSize), _dataSource(aDataSource)
{
  _image = PLAOBJImage::CreateRaw(aImageName);
  //_image = new PLAOBJImage(aImageName, PLAOBJImageSize(1024), PLAImageType::Raw);
  /*
  for (PLASize y = 0; y < aTileSize.y; y++) {
    std::vector<PLATimelineHolder *> holders(0);
    for (PLASize x = 0; x < aTileSize.x; x++) {
      holders.push_back(new PLATimelineHolder());
    }
    _timelineHolders.push_back(holders);
  }
   */
};

PLALYRTile::~PLALYRTile()
{
  /*
  for (PLASize y = 0; y < _tileSize.y; y++) {
     for (PLASize x = 0; x < _tileSize.x; x++) {
       GRA_DELETE(_timelineHolders[y][x]);
     }
  }
  */
  GRA_DELETE(_image);
};

/*
void PLALYRTile::AddMotionThread(const PLATileDataAddress &aAddress,
                                 PLATMLMotion *aThread)
{
  auto dataAddress = _dataSource->GetDataAddress();
  auto holderAddress = aAddress - dataAddress;
  if (holderAddress.x < 0 || _tileSize.x <= holderAddress.x) {
    return;
  }
  if (holderAddress.y < 0 || _tileSize.y <= holderAddress.y) {
    return;
  }
  _timelineHolders[holderAddress.y][holderAddress.x]->PLATimelineHolder::AddTimelineThread(
    aThread);
};
 */

const PLATMLMotion *PLALYRTile::GetMotion(const PLATileDataAddress &aAddress) const
{
  auto motionThread = _dataSource->GetMotion(aAddress);
  return motionThread;
  //auto dataAddress = _dataSource->GetDataAddress();
  //auto holderAddress = aAddress - dataAddress;
  //return static_cast<const PLATMLMotion *>
  //(_timelineHolders[holderAddress.y][holderAddress.x]->GetTimeline());
};

PLARect PLALYRTile::GetRect() const
{
  PLAVec3f offset = this->GetOffset();
  PLAVec3f size = this->GetSize();
  return { { offset.x, offset.y }, { size.x, size.y } };
}

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
