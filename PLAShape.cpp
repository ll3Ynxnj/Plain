#include "PLAShape.hpp"
#include <math.h>

PLAShape *PLAShape::Create(const PLAShape &aShape)
{
  PLAShape *shape = nullptr;
  switch (aShape.GetType())
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
      PLAError::Throw(PLAErrorType::Assert, "Detected unexpected PLAShapeType.");
      break;
  }
  PLAObject::Bind(shape);
  return shape;
}

PLAShape::PLAShape(PLAShapeType aType, const PLAStyle &aStyle) :
_type(aType), _style(aStyle)
{

}

PLAShape::~PLAShape()
{

}

PLAVec3 PLASHPPoint::GetSize() const
{
  return PLAVec3();
}

void PLASHPPoint::GetSize(PLAVec3 *aSize) const
{
  aSize->x = 0;
  aSize->y = 0;
  aSize->z = 0;
}

void PLASHPPoint::SetSize(const PLAVec3 &aSize)
{
  return;
}

PLAVec3 PLASHPLine::GetSize() const
{
  return PLAVec3Make(_vector.x, _vector.y, 0);
}

void PLASHPLine::GetSize(PLAVec3 *aSize) const
{
  aSize->x = _vector.x;
  aSize->y = _vector.y;
  aSize->z = 0;
}

void PLASHPLine::SetSize(const PLAVec3 &aSize)
{
  _vector.x = aSize.x;
  _vector.y = aSize.y;
}

PLAVec3 PLASHPRect::GetSize() const
{
  return PLAVec3Make(_vector.x, _vector.y, 0);
}

void PLASHPRect::GetSize(PLAVec3 *aSize) const
{
  aSize->x = _vector.x;
  aSize->y = _vector.y;
  aSize->z = 0;
}

void PLASHPRect::SetSize(const PLAVec3 &aSize)
{
  _vector.x = aSize.x;
  _vector.y = aSize.y;
}

PLAVec3 PLASHPCircle::GetSize() const
{
  return PLAVec3Make(_radius * 2, _radius * 2, 0);
}

void PLASHPCircle::GetSize(PLAVec3 *aSize) const
{
  aSize->x = _radius * 2;
  aSize->y = _radius * 2;
  aSize->z = 0;
}

void PLASHPCircle::SetSize(const PLAVec3 &aSize)
{
  _radius = aSize.x > aSize.y ? aSize.x : aSize.y;
}
