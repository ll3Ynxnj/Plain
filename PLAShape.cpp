#include "PLAShape.hpp"
#include <math.h>

PLAShape::PLAShape(PLAShapeType aType, const PLAStyle &aStyle) :
_type(aType), _style(aStyle)
{

}

PLAShape::~PLAShape()
{

}

PLAVec3 PLAShapePoint::GetSize() const
{
  return PLAVec3();
}

void PLAShapePoint::GetSize(PLAVec3 *aSize) const
{
  aSize->x = 0;
  aSize->y = 0;
  aSize->z = 0;
}

void PLAShapePoint::SetSize(const PLAVec3 &aSize)
{
  return;
}

PLAVec3 PLAShapeLine::GetSize() const
{
  return PLAVec3Make(_vector.x, _vector.y, 0);
}

void PLAShapeLine::GetSize(PLAVec3 *aSize) const
{
  aSize->x = _vector.x;
  aSize->y = _vector.y;
  aSize->z = 0;
}

void PLAShapeLine::SetSize(const PLAVec3 &aSize)
{
  _vector.x = aSize.x;
  _vector.y = aSize.y;
}

PLAVec3 PLAShapeRect::GetSize() const
{
  return PLAVec3Make(_vector.x, _vector.y, 0);
}

void PLAShapeRect::GetSize(PLAVec3 *aSize) const
{
  aSize->x = _vector.x;
  aSize->y = _vector.y;
  aSize->z = 0;
}

void PLAShapeRect::SetSize(const PLAVec3 &aSize)
{
  _vector.x = aSize.x;
  _vector.y = aSize.y;
}

PLAVec3 PLAShapeCircle::GetSize() const
{
  return PLAVec3Make(_radius * 2, _radius * 2, 0);
}

void PLAShapeCircle::GetSize(PLAVec3 *aSize) const
{
  aSize->x = _radius * 2;
  aSize->y = _radius * 2;
  aSize->z = 0;
}

void PLAShapeCircle::SetSize(const PLAVec3 &aSize)
{
  _radius = aSize.x > aSize.y ? aSize.x : aSize.y;
}
