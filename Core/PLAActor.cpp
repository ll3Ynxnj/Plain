#include "PLAActor.hpp"
#include "PLAInput.hpp"
#include "PLAError.hpp"
#include "PLAFunctor.hpp"

PLAActor *PLAActor::Create(const PLAVec3 &aPivot,
                           const PLAColor &aColor,
                           const PLATransform &aTransform,
                           const PLAShape &aShape)
{
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, aShape);
  PLAObject::Manager::Ref()->Bind(actor);
  return actor;
}

PLAActor::PLAActor(const PLAVec3 &aPivot,
                   const PLAColor &aColor,
                   const PLATransform &aTransform,
                   const PLAShape &aShape) :
  PLAObject(PLAObjectType::Actor, "== PLAActor =="),
  PLAInputContext(),
  PLAScene::Delegate(),
  _pivot(aPivot),
  _color(aColor),
  _transform(aTransform),
  _shape(PLAShape::Create(aShape))
{
  this->RefreshShapeOffset();
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

void PLAActor::Init()
{
  _functor.RunFunction("OnInit", this);
  for (PLAActor *actor : _actors) { actor->Init(); }
}

void PLAActor::Update()
{
  _functor.RunFunction("OnUpdate", this);
  for (PLAActor *actor : _actors) { actor->Update(); }
}

void PLAActor::Appear()
{
  _functor.RunFunction("OnAppear", this);
  for (PLAActor *actor : _actors) { actor->Appear(); }
}

void PLAActor::Disappear()
{
  _functor.RunFunction("OnDisappear", this);
  for (PLAActor *actor : _actors) { actor->Disappear(); }
}

void PLAActor::PrintActors() const
{
  static int indentLevel = 0;
  this->PrintObject();
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
  //*
  return _shape->IsCollideWithPoint(aPoint);
  /*/
  // Provisional : Design that include PLACollider class is desirable.
  const PLAVec3 basePoint = _shape->GetOffset();
  const PLAPoint p0 = PLAPointMake(basePoint.x, basePoint.y);
  const PLAPoint p1 = PLAPointMake(basePoint.x + this->GetSize().x,
                                   basePoint.y + this->GetSize().y);

  if (aPoint.x < p0.x) { return false; }
  if (aPoint.y < p0.y) { return false; }
  if (p1.x <= aPoint.x) { return false; }
  if (p1.y <= aPoint.y) { return false; }

  return true;
  //*/
}

/*
bool PLAActor::IsCollideWithRect(PLARect aRect) const
{
  return false;
}
 */

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

void PLAActor::RefreshShapeOffset()
{
  PLAVec3 size(this->GetSize());
  _shape->SetOffset(-PLAVec3Make(size.x * _pivot.x,
                                 size.y * _pivot.y,
                                 size.z * _pivot.z));
}
