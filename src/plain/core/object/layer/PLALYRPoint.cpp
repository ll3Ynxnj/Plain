#include "plain/core/object/layer/PLALYRPoint.hpp"
#include "plain/core/library/PLALIBCollision.hpp"

PLAVec3f PLALYRPoint::GetSize() const
{
  return kPLAVec3fNone;
}

void PLALYRPoint::GetSize(PLAVec3f *aSize) const
{
  aSize->x = 0;
  aSize->y = 0;
  aSize->z = 0;
}

void PLALYRPoint::SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot)
{
  return;
}

bool PLALYRPoint::IsCollideWithPoint(const PLAPoint &aPoint) const
{
  return
    PLACollision::IsCollideWithPointAndPoint(this->GetPoint(), aPoint);
}

bool PLALYRPoint::IsCollideWithLine(const PLALine &aLine) const
{
  return
    PLACollision::IsCollideWithPointAndLine(this->GetPoint(), aLine);
}

bool PLALYRPoint::IsCollideWithRect(const PLARect &aRect) const
{
  return
    PLACollision::IsCollideWithPointAndRect(this->GetPoint(), aRect);
}

bool PLALYRPoint::IsCollideWithCircle(const PLACircle &aCircle) const
{
  return
    PLACollision::IsCollideWithPointAndCircle(this->GetPoint(), aCircle);
}

PLAPoint PLALYRPoint::GetPoint() const
{
  return { this->GetOffset().x, this->GetOffset().y };
}
