#include "PLAActor.hpp"
#include "PLAInput.hpp"
#include "PLAError.hpp"
#include "Grain/GRAFunctor.hpp"

PLAActor *PLAActor::Create(const PLAVec3 &aPivot,
                           const PLAColor &aColor,
                           const PLATransform &aTransform,
                           const PLALayer &aLayer)
{
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, aLayer);
  PLAObject::Manager::Ref()->Bind(actor);
  return actor;
}

PLAActor::PLAActor(const PLAVec3 &aPivot,
                   const PLAColor &aColor,
                   const PLATransform &aTransform,
                   const PLALayer &aLayer) :
  PLAObject(PLAObjectType::Actor, "== PLAActor =="),
  PLAInputContext(),
  _pivot(aPivot),
  _color(aColor),
  _transform(aTransform),
  _layer(PLALayer::Create(aLayer))
{
  this->RefreshLayerOffset();
}

PLAActor::~PLAActor()
{
  PLA_DELETE(_layer);
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
  _functor.RunFunction(FunctionCode::OnInit, this);
  for (PLAActor *actor : _actors) { actor->Init(); }
}

void PLAActor::Update()
{
  _functor.RunFunction(FunctionCode::OnUpdate, this);
  for (PLAActor *actor : _actors) { actor->Update(); }
}

void PLAActor::Appear()
{
  _functor.RunFunction(FunctionCode::OnAppear, this);
  for (PLAActor *actor : _actors) { actor->Appear(); }
}

void PLAActor::Disappear()
{
  _functor.RunFunction(FunctionCode::OnDisappear, this);
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
  return _layer->IsCollideWithPoint(aPoint);
  /*/
  // Provisional : Design that include PLACollider class is desirable.
  const PLAVec3 basePoint = _layer->GetOffset();
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
const PLALYRRect *PLAActor::GetLayerRect() const
{
  if (this->GetLayerType() != PLALayerType::Circle)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Type does not match.");
  }
  return static_cast<PLALYRRect *>(_layer);
}

const PLALYRCircle *PLAActor::GetLayerCircle() const
{
  if (this->GetLayerType() != PLALayerType::Circle)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Type does not match.");
  }
  return static_cast<PLALYRCircle *>(_layer);
}
*/

void PLAActor::RefreshLayerOffset()
{
  PLAVec3 size(this->GetSize());
  _layer->SetOffset(-PLAVec3Make(size.x * _pivot.x,
                                 size.y * _pivot.y,
                                 size.z * _pivot.z));
}
