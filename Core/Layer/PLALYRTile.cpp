#include "PLALYRTile.hpp"

PLALYRTile *PLALYRTile::Create(const PLAVec2 &aOffset,
                               const std::string &aImageName,
                               const GRAVec2<PLASize> &aMapSize,
                               const GRAVec2<PLASize> &aChipSize,
                               PLASize aAddress) {
  PLAImage *image = PLAImage::CreateRaw(aImageName);
  PLALYRTile *layer =
    new PLALYRTile(aOffset, image, aMapSize, aChipSize, aAddress);
  PLAObject::Bind(layer);
  return layer;
}

PLAVec3 PLALYRTile::GetSize() const {
  return PLAVec3(_chipSize.x * _mapSize.x, _chipSize.y * _mapSize.y, 0);
}

void PLALYRTile::GetSize(PLAVec3 *aSize) const {
  aSize->x = _chipSize.x * _mapSize.x;
  aSize->y = _chipSize.y * _mapSize.y;
  aSize->z = 0;
}

/*
void PLALYRTile::RefreshChips(const std::vector<std::vector<PLATileChip>> &aChips) {
  if (aChips.size() != _mapSize.y) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Invalid Y-axis size. aChips.y: %d, _mapSize.y %d",
                    aChips.size(), _chips.size());
  }
  if (aChips.size() != _mapSize.x) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Invalid X-axis size. aChips.x: %d, _mapSize.x %d",
                    aChips.size(), _mapSize.x);
  }
  _chips = aChips;
}
 */

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