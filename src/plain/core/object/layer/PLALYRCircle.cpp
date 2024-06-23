#include "plain/core/object/layer/PLALYRCircle.hpp"
#include "plain/core/library/PLALIBCollision.hpp"

PLALYRCircle *PLALYRCircle::Create(const PLACircle &aCircle)
{
  PLALYRCircle *layer =
    new PLALYRCircle(PLAVec3f(aCircle.origin.x - aCircle.radius,
                             aCircle.origin.y - aCircle.radius, 0),
                     aCircle.radius, kPLAColorWhite, kPLAColorNone,
                     kPLAStrUndefined, kPLARectNone);
  layer->Bind();
  return layer;
}

PLALYRCircle *PLALYRCircle::Create(const PLACircle &aCircle,
                                   const PLAColor &aFillColor,
                                   const PLAColor &aStrokeColor,
                                   const std::string &aImage,
                                   const PLARect &aClip)
{
  PLALYRCircle *layer =
    new PLALYRCircle(PLAVec3f(aCircle.origin.x - aCircle.radius,
                             aCircle.origin.y - aCircle.radius, 0),
                     aCircle.radius, aFillColor, aStrokeColor, aImage, aClip);
  layer->Bind();
  return layer;
}

PLAVec3f PLALYRCircle::GetSize() const
{
  return { _radius * 2, _radius * 2, 0 };
}

void PLALYRCircle::GetSize(PLAVec3f *aSize) const
{
  aSize->x = _radius * 2;
  aSize->y = _radius * 2;
  aSize->z = 0;
}

void PLALYRCircle::SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot)
{
  _radius = aSize.x > aSize.y ? aSize.x : aSize.y;
  this->SetOffset(PLAVec3f((aPivot.x - 0.5) * _radius * 2,
                          (aPivot.y - 0.5) * _radius * 2,
                          0));
}

void PLALYRCircle::SetImageClip(PLAOBJImageClip *aImageClip)
{
  _imageClip = aImageClip;
}

void PLALYRCircle::SetVideoClip(PLAOBJVideoClip *aVideoClip)
{
  _videoClip = aVideoClip;
}

bool PLALYRCircle::IsCollideWithPoint(const PLAPoint &aPoint) const
{
  return
    PLACollision::IsCollideWithPointAndCircle(aPoint, this->GetCircle());
}

bool PLALYRCircle::IsCollideWithLine(const PLALine &aLine) const
{
  return
    PLACollision::IsCollideWithLineAndCircle(aLine, this->GetCircle());
}

bool PLALYRCircle::IsCollideWithRect(const PLARect &aRect) const
{
  return
    PLACollision::IsCollideWithRectAndCircle(aRect, this->GetCircle());
}

bool PLALYRCircle::IsCollideWithCircle(const PLACircle &aCircle) const
{
  return
    PLACollision::IsCollideWithCircleAndCircle(this->GetCircle(), aCircle);
}

PLACircle PLALYRCircle::GetCircle() const
{
  return
    {
      { this->GetOffset().x + _radius, this->GetOffset().y + _radius },
      _radius
    };
}

void PLALYRCircle::SetFillColor(const PLAColor &aColor) const
{
  PLA_ERROR_ISSUE(PLAErrorType::Expect, "Undefined Method.");
}

void PLALYRCircle::SetStrokeColor(const PLAColor &aColor) const
{
  PLA_ERROR_ISSUE(PLAErrorType::Expect, "Undefined Method.");
}
