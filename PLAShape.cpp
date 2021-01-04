#include "PLAShape.hpp"
#include "PLACollision.hpp"
#include "PLAError.hpp"

PLAShape *PLAShape::Create(const PLAShape &aShape)
{
  PLAShape *shape = nullptr;
  switch (aShape.GetShapeType())
  {
    case PLAShapeType::Point :
      shape = new PLASHPPoint(static_cast<const PLASHPPoint &>(aShape));
      break;
    case PLAShapeType::Line :
      shape = new PLASHPLine(static_cast<const PLASHPLine  &>(aShape));
      break;
    case PLAShapeType::Rect :
      shape = new PLASHPRect(static_cast<const PLASHPRect &>(aShape));
      break;
    case PLAShapeType::Circle :
      shape = new PLASHPCircle(static_cast<const PLASHPCircle &>(aShape));
      break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "Detected unexpected PLAShapeType.");
      break;
  }
  PLAObject::Manager::GetInstance()->Bind(shape);
  return shape;
}

PLAShape::PLAShape(PLAShapeType aType, const PLAVec3 &aOffset, const std::string &aName) :
PLAObject(PLAObjectType::Shape, aName),
_type(aType), _offset(aOffset)
{

}

PLAShape::~PLAShape()
{

}

PLAVec3 PLASHPPoint::GetSize() const
{
  return kPLAVec3None;
}

void PLASHPPoint::GetSize(PLAVec3 *aSize) const
{
  aSize->x = 0;
  aSize->y = 0;
  aSize->z = 0;
}

void PLASHPPoint::SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot)
{
  return;
}

bool PLASHPPoint::IsCollideWithPoint(const PLAPoint &aPoint) const
{
  return
  PLACollision::IsCollideWithPointAndPoint(this->GetPoint(), aPoint);
}

bool PLASHPPoint::IsCollideWithLine(const PLALine &aLine) const
{
  return
  PLACollision::IsCollideWithPointAndLine(this->GetPoint(), aLine);
}

bool PLASHPPoint::IsCollideWithRect(const PLARect &aRect) const
{
  return
  PLACollision::IsCollideWithPointAndRect(this->GetPoint(), aRect);
}

bool PLASHPPoint::IsCollideWithCircle(const PLACircle &aCircle) const
{
  return
  PLACollision::IsCollideWithPointAndCircle(this->GetPoint(), aCircle);
}

PLAPoint PLASHPPoint::GetPoint() const
{
  return { this->GetOffset().x, this->GetOffset().y };
}

PLAVec3 PLASHPLine::GetSize() const
{
  return { abs(_vector.x), abs(_vector.y), 0 };
}

void PLASHPLine::GetSize(PLAVec3 *aSize) const
{
  aSize->x = abs(_vector.x);
  aSize->y = abs(_vector.y);
  aSize->z = 0;
}

void PLASHPLine::SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot)
{
  _vector.x = aSize.x;
  _vector.y = aSize.y;
  PLAVec3 offset = PLAVec3Make( aSize.x * aPivot.x, aSize.y * aPivot.y, 0 );
  this->SetOffset(offset);
}

bool PLASHPLine::IsCollideWithPoint(const PLAPoint &aPoint) const
{
  return
  PLACollision::IsCollideWithPointAndLine(aPoint, this->GetLine());
}

bool PLASHPLine::IsCollideWithLine(const PLALine &aLine) const
{
  return
  PLACollision::IsCollideWithLineAndLine(this->GetLine(), aLine);
}

bool PLASHPLine::IsCollideWithRect(const PLARect &aRect) const
{
  return
  PLACollision::IsCollideWithLineAndRect(this->GetLine(), aRect);
}

bool PLASHPLine::IsCollideWithCircle(const PLACircle &aCircle) const
{
  return
  PLACollision::IsCollideWithLineAndCircle(this->GetLine(), aCircle);
}

PLALine PLASHPLine::GetLine() const
{
  return { {this->GetOffset().x, this->GetOffset().y}, {_vector.x, _vector.y} };
}

PLAVec3 PLASHPRect::GetSize() const
{
  return { abs(_vector.x), abs(_vector.y), 0 };
}

void PLASHPRect::GetSize(PLAVec3 *aSize) const
{
  aSize->x = abs(_vector.x);
  aSize->y = abs(_vector.y);
  aSize->z = 0;
}

void PLASHPRect::SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot)
{
  this->SetOffset(PLAVec3Make(aSize.x * aPivot.x, aSize.y * aPivot.y, 0));
  _vector.x = aSize.x;
  _vector.y = aSize.y;
}

bool PLASHPRect::IsCollideWithPoint(const PLAPoint &aPoint) const
{
  return
  PLACollision::IsCollideWithPointAndRect(aPoint, this->GetRect());
}

bool PLASHPRect::IsCollideWithLine(const PLALine &aLine) const
{
  return
  PLACollision::IsCollideWithLineAndRect(aLine, this->GetRect());
}

bool PLASHPRect::IsCollideWithRect(const PLARect &aRect) const
{
  return
  PLACollision::IsCollideWithRectAndRect(this->GetRect(), aRect);
}

bool PLASHPRect::IsCollideWithCircle(const PLACircle &aCircle) const
{
  return
  PLACollision::IsCollideWithRectAndCircle(this->GetRect(), aCircle);
}

PLARect PLASHPRect::GetRect() const
{
  return
  { { this->GetOffset().x, this->GetOffset().y }, { _vector.x, _vector.y } };
}

PLAVec3 PLASHPCircle::GetSize() const
{
  return { _radius * 2, _radius * 2, 0 };
}

void PLASHPCircle::GetSize(PLAVec3 *aSize) const
{
  aSize->x = _radius * 2;
  aSize->y = _radius * 2;
  aSize->z = 0;
}

void PLASHPCircle::SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot)
{
  _radius = aSize.x > aSize.y ? aSize.x : aSize.y;
  this->SetOffset(PLAVec3Make((aPivot.x - 0.5) * _radius * 2,
                              (aPivot.y - 0.5) * _radius * 2,
                              0));
}

bool PLASHPCircle::IsCollideWithPoint(const PLAPoint &aPoint) const
{
  return
  PLACollision::IsCollideWithPointAndCircle(aPoint, this->GetCircle());
}

bool PLASHPCircle::IsCollideWithLine(const PLALine &aLine) const
{
  return
  PLACollision::IsCollideWithLineAndCircle(aLine, this->GetCircle());
}

bool PLASHPCircle::IsCollideWithRect(const PLARect &aRect) const
{
  return
  PLACollision::IsCollideWithRectAndCircle(aRect, this->GetCircle());
}

bool PLASHPCircle::IsCollideWithCircle(const PLACircle &aCircle) const
{
  return
  PLACollision::IsCollideWithCircleAndCircle(this->GetCircle(), aCircle);
}

PLACircle PLASHPCircle::GetCircle() const
{
  return {{ this->GetOffset().x + _radius, this->GetOffset().y + _radius },
          _radius };
}
