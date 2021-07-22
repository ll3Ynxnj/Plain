#include "PLALYRTile.hpp"

PLALYRTile *PLALYRTile::Create(const PLAVec2 &aOffset,
                               const std::string &aImageName,
                               const GRAVec2<PLASize> &aMapSize,
                               const GRAVec2<PLASize> &aChipSize,
                               const IPLALYRTileDataSource *aDataSource) {
  PLAImage *image = PLAImage::CreateRaw(aImageName);
  PLALYRTile *layer =
    new PLALYRTile(aOffset, image, aMapSize, aChipSize, aDataSource);
  PLAObject::Bind(layer);
  return layer;
}

PLAVec3 PLALYRTile::GetSize() const {
  return PLAVec3(_chipSize.x * _tileSize.x, _chipSize.y * _tileSize.y, 0);
}

void PLALYRTile::GetSize(PLAVec3 *aSize) const {
  aSize->x = _chipSize.x * _tileSize.x;
  aSize->y = _chipSize.y * _tileSize.y;
  aSize->z = 0;
}

void PLALYRTile::SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot) {
  return;
}

bool PLALYRTile::IsCollideWithPoint(const PLAPoint &aPoint) const {
  return false;
}

bool PLALYRTile::IsCollideWithLine(const PLALine &aLine) const {
  return false;
}

bool PLALYRTile::IsCollideWithRect(const PLARect &aRect) const {
  return false;
}

bool PLALYRTile::IsCollideWithCircle(const PLACircle &aCircle) const {
  return false;
}
