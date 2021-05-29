#include "PLALYRRect.hpp"

PLALYRRect *PLALYRRect::Create(const PLARect &aRect,
                               const PLAColor &aFillColor,
                               const PLAColor &aStrokeColor,
                               const std::string &aImage,
                               const PLARect &aClip)
{
  PLALYRRect *layer = new PLALYRRect(PLAVec3(aRect.pos.x,
                                             aRect.pos.y, 0),
                                     aRect.size,
                                     aFillColor,
                                     aStrokeColor,
                                     aImage, aClip);
  PLAObject::Bind(layer);
  return layer;
}

PLAVec3 PLALYRRect::GetSize() const
{
  return { abs(_vector.x), abs(_vector.y), 0 };
}

void PLALYRRect::GetSize(PLAVec3 *aSize) const
{
  aSize->x = abs(_vector.x);
  aSize->y = abs(_vector.y);
  aSize->z = 0;
}

void PLALYRRect::SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot)
{
  this->SetOffset(PLAVec3(aSize.x * aPivot.x, aSize.y * aPivot.y, 0));
  _vector.x = aSize.x;
  _vector.y = aSize.y;
}

bool PLALYRRect::IsCollideWithPoint(const PLAPoint &aPoint) const
{
  return
    PLACollision::IsCollideWithPointAndRect(aPoint, this->GetRect());
}

bool PLALYRRect::IsCollideWithLine(const PLALine &aLine) const
{
  return
    PLACollision::IsCollideWithLineAndRect(aLine, this->GetRect());
}

bool PLALYRRect::IsCollideWithRect(const PLARect &aRect) const
{
  return
    PLACollision::IsCollideWithRectAndRect(this->GetRect(), aRect);
}

bool PLALYRRect::IsCollideWithCircle(const PLACircle &aCircle) const
{
  return
    PLACollision::IsCollideWithRectAndCircle(this->GetRect(), aCircle);
}

PLARect PLALYRRect::GetRect() const
{
  return
    { { this->GetOffset().x, this->GetOffset().y }, { _vector.x, _vector.y } };
}
