#include "PLAActor.hpp"
#include "PLAInput.hpp"
#include "PLAError.hpp"

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
PLAInputContext(),
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

void PLAActor::Input(const PLAInput *aInput)
{

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

bool PLAActor::IsCollideWithPoint(PLAPoint aPoint) const
{
  // Provisional : Design that include PLACollider class is desirable.
  const PLAVec3 basePoint = -this->GetOrigin();
  const PLAPoint p0 = PLAPointMake(basePoint.x, basePoint.y);
  const PLAPoint p1 = PLAPointMake(basePoint.x + this->GetSize().x,
                                   basePoint.y + this->GetSize().y);

  if (aPoint.x < p0.x) { return false; }
  if (aPoint.y < p0.y) { return false; }
  if (p1.x <= aPoint.x) { return false; }
  if (p1.y <= aPoint.y) { return false; }

  return true;
}

bool PLAActor::IsCollideWithRect(PLARect aRect) const
{
  return false;
}

PLAActor *PLAActor::RefActorWithPoint(const PLAPoint &aPoint)
{
  for (std::list<PLAActor *>::reverse_iterator it = _actors.rbegin();
       it != _actors.rend(); it++)
  {
    PLA_PRINT("aPoint : x %.2f : y %.2f\n", aPoint.x, aPoint.y);
    PLAPoint offset = PLAPointMake((*it)->GetTransform().translation.x,
                                   (*it)->GetTransform().translation.y);
    PLA_PRINT("offset : x %.2f : y %.2f\n", offset.x, offset.y);
    PLAActor *actor = (*it)->RefActorWithPoint(aPoint - offset);
    if (actor) { return actor; }
  }

  if (this->IsCollideWithPoint(aPoint)) { return this; }

  return nullptr;
}

/*
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
*/

void PLAActor::RefreshOrigin()
{
  PLAVec3 size(this->GetSize());
  _origin.x = size.x * _pivot.x;
  _origin.y = size.y * _pivot.y;
  _origin.z = size.z * _pivot.z;
}

void PLAActor::SetStyle(const PLAStyle &aStyle)
{
  _shape->SetStyle(aStyle);
}
