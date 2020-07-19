#include "PLAActor.hpp"
#include "PLAApp.hpp"
#include "PLAError.hpp"
#include "PLAShape.hpp"

PLAActor *PLAActor::Create(const PLAVec3 &aPivot,
                           const PLAColor &aColor,
                           const PLATransform &aTransform,
                           const PLAShape &aShape)
{
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, aShape);
  PLAObject::Manager::GetInstance()->Bind(actor);
  return actor;
}

PLAActor::PLAActor(const PLAVec3 &aPivot,
                   const PLAColor &aColor,
                   const PLATransform &aTransform,
                   const PLAShape &aShape) :
PLAObject(PLAObjectType::Actor),
_pivot(aPivot),
_color(aColor),
_transform(aTransform),
_shape(PLAShape::Create(aShape))
{
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
  _fUpdate(this);
  for (PLAActor *actor : _actors) { actor->Update(); }
}

void PLAActor::PrintActors() const
{
  static int indentLevel = 0;
  this->Print();
  ++indentLevel;
  for (const PLAActor *actor : _actors)
  {
    for (int i = 0; i < indentLevel; i++) { PLA_PRINT("  "); }
    actor->PrintActors();
  }
  --indentLevel;
}

const PLASHPRect *PLAActor::GetShapeRect() const
{
  if (this->GetShapeType() != PLAShapeType::Circle)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Type does not match.");
  }
  return static_cast<PLASHPRect *>(_shape);
}

const PLASHPCircle *PLAActor::GetShapeCircle() const
{
  if (this->GetShapeType() != PLAShapeType::Circle)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Type does not match.");
  }
  return static_cast<PLASHPCircle *>(_shape);
}

void PLAActor::RefreshOrigin()
{
  PLAVec3 size(this->GetSize());
  _origin.x = size.x * _pivot.x;
  _origin.y = size.y * _pivot.y;
  _origin.z = size.z * _pivot.z;
}
