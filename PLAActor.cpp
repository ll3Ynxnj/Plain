#include "PLAActor.hpp"
#include "PLAApp.hpp"
#include "PLAError.hpp"
#include "PLAShape.hpp"
#include "PLARenderer.hpp"

PLAActor::PLAActor(const PLAVec3 &aPivot,
                   const PLAColor &aColor,
                   const PLATransform &aTransform,
                   const PLAShape &aShape) :
  PLAObj(),
  _pivot(aPivot),
  _color(aColor),
  _transform(aTransform)
{
  switch (aShape.GetType())
  {
    case PLAShapeType::Point :
      _shape = new PLAShapePoint(static_cast<const PLAShapePoint &>(aShape));
      break;
    case PLAShapeType::Line :
      _shape = new PLAShapeLine(static_cast<const PLAShapeLine  &>(aShape));
      break;
    case PLAShapeType::Rect :
      _shape = new PLAShapeRect(static_cast<const PLAShapeRect &>(aShape));
      break;
    case PLAShapeType::Circle :
      _shape = new PLAShapeCircle(static_cast<const PLAShapeCircle &>(aShape));
      break;
    default :
      PLAError::Throw(PLAErrorType::Assert, "Detected unexpected PLAShapeType.");
      break;
  }
  this->RefreshOrigin();
}

PLAActor::~PLAActor()
{
  PLA_DELETE(_shape);
}

void PLAActor::AddActor(PLAActor *aActor)
{
  _actors.push_back(aActor);
}

void PLAActor::Update()
{
  this->OnUpdate();
  for (PLAActor *actor : _actors)
  {
    actor->Update();
  }
}

void PLAActor::OnUpdate()
{

}

void PLAActor::RefreshOrigin()
{
  PLAVec3 size(this->GetSize());
  _origin.x = size.x * _pivot.x;
  _origin.y = size.y * _pivot.y;
  _origin.z = size.z * _pivot.z;
}

const PLAShapeRect *PLAActor::GetShapeRect() const
{
  if (this->GetShapeType() != PLAShapeType::Circle)
  {
    PLAError::Throw(PLAErrorType::Assert, "Type does not match.");
  }
  return static_cast<PLAShapeRect *>(_shape);
}

const PLAShapeCircle *PLAActor::GetShapeCircle() const
{
  if (this->GetShapeType() != PLAShapeType::Circle)
  {
    PLAError::Throw(PLAErrorType::Assert, "Type does not match.");
  }
  return static_cast<PLAShapeCircle *>(_shape);
}
