#include "PLALYRLine.hpp"
#include "Core/Library/PLALIBCollision.hpp"

PLAVec3 PLALYRLine::GetSize() const
{
  return { abs(_vector.x), abs(_vector.y), 0 };
}

void PLALYRLine::GetSize(PLAVec3 *aSize) const
{
  aSize->x = abs(_vector.x);
  aSize->y = abs(_vector.y);
  aSize->z = 0;
}

void PLALYRLine::SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot)
{
  _vector.x = aSize.x;
  _vector.y = aSize.y;
  PLAVec3 offset = PLAVec3( aSize.x * aPivot.x, aSize.y * aPivot.y, 0 );
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
