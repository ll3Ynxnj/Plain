#include "PLALayer.hpp"
#include "PLAError.hpp"

PLALayer *PLALayer::Create(const PLALayer &aLayer)
{
  PLALayer *layer = nullptr;
  switch (aLayer.GetLayerType())
  {
    case PLALayerType::Point :
      layer = new PLALYRPoint(static_cast<const PLALYRPoint &>(aLayer));
      break;
    case PLALayerType::Line :
      layer = new PLALYRLine(static_cast<const PLALYRLine  &>(aLayer));
      break;
    case PLALayerType::Rect :
      layer = new PLALYRRect(static_cast<const PLALYRRect &>(aLayer));
      break;
    case PLALayerType::Circle :
      layer = new PLALYRCircle(static_cast<const PLALYRCircle &>(aLayer));
      break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "Detected unexpected PLALayerType.");
      break;
  }
  GRABinder::Error error(GRABinder::Error::None);
  PLAObject::Manager::RefInstance()->Bind(layer, &error);
  return layer;
}

PLALayer::PLALayer(PLALayerType aType, const PLAVec3 &aOffset, const std::string &aName) :
PLAObject(PLAObjectType::Layer, aName),
_type(aType), _offset(aOffset)
{

}

PLALayer::~PLALayer()
{

}

PLAVec3 PLALYRPoint::GetSize() const
{
  return kPLAVec3None;
}

void PLALYRPoint::GetSize(PLAVec3 *aSize) const
{
  aSize->x = 0;
  aSize->y = 0;
  aSize->z = 0;
}

void PLALYRPoint::SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot)
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

PLAVec3 PLALYRCircle::GetSize() const
{
  return { _radius * 2, _radius * 2, 0 };
}

void PLALYRCircle::GetSize(PLAVec3 *aSize) const
{
  aSize->x = _radius * 2;
  aSize->y = _radius * 2;
  aSize->z = 0;
}

void PLALYRCircle::SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot)
{
  _radius = aSize.x > aSize.y ? aSize.x : aSize.y;
  this->SetOffset(PLAVec3((aPivot.x - 0.5) * _radius * 2,
                          (aPivot.y - 0.5) * _radius * 2,
                          0));
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
