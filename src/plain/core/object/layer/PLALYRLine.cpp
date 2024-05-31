#include "plain/core/object/layer/PLALYRLine.hpp"
#include "plain/core/library/PLALIBCollision.hpp"

PLAVec3f PLALYRLine::GetSize() const
{
  return { abs(_vector.x), abs(_vector.y), 0 };
}

void PLALYRLine::GetSize(PLAVec3f *aSize) const
{
  aSize->x = abs(_vector.x);
  aSize->y = abs(_vector.y);
  aSize->z = 0;
}

void PLALYRLine::SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot)
{
  _vector.x = aSize.x;
  _vector.y = aSize.y;
  PLAVec3f offset = PLAVec3f( aSize.x * aPivot.x, aSize.y * aPivot.y, 0 );
  this->SetOffset(offset);
}

bool PLALYRLine::IsCollideWithPoint(const PLAPoint &aPoint) const
{
  return
    PLACollision::IsCollideWithPointAndLine(aPoint, this->GetLine());
}

bool PLALYRLine::IsCollideWithLine(const PLALine &aLine) const
{
  return
    PLACollision::IsCollideWithLineAndLine(this->GetLine(), aLine);
}

bool PLALYRLine::IsCollideWithRect(const PLARect &aRect) const
{
  return
    PLACollision::IsCollideWithLineAndRect(this->GetLine(), aRect);
}

bool PLALYRLine::IsCollideWithCircle(const PLACircle &aCircle) const
{
  return
    PLACollision::IsCollideWithLineAndCircle(this->GetLine(), aCircle);
}

PLALine PLALYRLine::GetLine() const
{
  return { {this->GetOffset().x, this->GetOffset().y}, {_vector.x, _vector.y} };
}
