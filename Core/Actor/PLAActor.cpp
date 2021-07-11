#include "PLAActor.hpp"
#include "PLAInput.hpp"
#include "PLAError.hpp"

#include "Layer/PLALYRRect.hpp"
#include "Layer/PLALYRCircle.hpp"
#include "Layer/PLALYRTile.hpp"

PLAActor *PLAActor::CreateRect(const PLAVec3 &aPivot,
                               const PLAColor &aColor,
                               const PLATransform &aTransform,
                               const PLARect &aRect)
{
  PLALayer *layer = PLALYRRect::Create(aRect, kPLAColorWhite, kPLAColorNone,
                                       kPLAStrUndefined, kPLARectNone);
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, layer);
  PLAObject::Bind(actor);
  return actor;
}

PLAActor *PLAActor::CreateRect(const PLAVec3 &aPivot,
                               const PLAColor &aColor,
                               const PLATransform &aTransform,
                               const PLARect &aRect,
                               const PLAColor &aFillColor)
{
  PLALayer *layer = PLALYRRect::Create(aRect, aFillColor, kPLAColorNone,
                                       kPLAStrUndefined, kPLARectNone);
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, layer);
  PLAObject::Bind(actor);
  return actor;
}

PLAActor *PLAActor::CreateRect(const PLAVec3 &aPivot,
                               const PLAColor &aColor,
                               const PLATransform &aTransform,
                               const PLARect &aRect,
                               const std::string &aImageName,
                               const PLARect &aClip)
{
  PLALayer *layer = PLALYRRect::Create(aRect, kPLAColorWhite, kPLAColorNone,
                                       aImageName, aClip);
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, layer);
  PLAObject::Bind(actor);
  return actor;
}

PLAActor *PLAActor::CreateCircle(const PLAVec3 &aPivot,
                                 const PLAColor &aColor,
                                 const PLATransform &aTransform,
                                 const PLACircle &aCircle)
{
  PLALayer *layer = PLALYRCircle::Create(aCircle, kPLAColorWhite, kPLAColorNone,
                                         kPLAStrUndefined, kPLARectNone);
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, layer);
  PLAObject::Bind(actor);
  return actor;
}

PLAActor *PLAActor::CreateCircle(const PLAVec3 &aPivot,
                                 const PLAColor &aColor,
                                 const PLATransform &aTransform,
                                 const PLACircle &aCircle,
                                 const PLAColor &aFillColor)
{
  PLALayer *layer = PLALYRCircle::Create(aCircle, aFillColor, kPLAColorNone,
                                         kPLAStrUndefined, kPLARectNone);
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, layer);
  PLAObject::Bind(actor);
  return actor;
}

PLAActor *PLAActor::CreateCircle(const PLAVec3 &aPivot,
                                 const PLAColor &aColor,
                                 const PLATransform &aTransform,
                                 const PLACircle &aCircle,
                                 const std::string &aImageName,
                                 const PLARect &aClip)
{
  PLALayer *layer = PLALYRCircle::Create(aCircle, kPLAColorWhite, kPLAColorNone,
                                         aImageName, aClip);
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, layer);
  PLAObject::Bind(actor);
  return actor;
}

PLAActor *PLAActor::CreateTile(const PLAVec2 &aOffset,
                               const std::string &aImageName,
                               const GRAVec2<PLASize> &aMapSize,
                               const GRAVec2<PLASize> &aChipSize,
                               PLASize aAddress,
                               const PLALYRTileDataSource *aDataSource)
{
  PLALYRTile *layer = PLALYRTile::Create(aOffset, aImageName, aMapSize, aChipSize,
                                         aAddress, aDataSource);
  PLAActor *actor = new PLAActor(kPLAVec3None, kPLAColorWhite,
                                 kPLATransformNorm, layer);
  PLAObject::Bind(actor);
  return actor;
}

PLAActor::PLAActor(const PLAVec3 &aPivot,
                   const PLAColor &aColor,
                   const PLATransform &aTransform,
                   PLALayer *aLayer) :
  PLAObject(PLAObjectType::Actor),//"== PLAActor =="),
  PLAInputContext(),
  _pivot(aPivot),
  _color(aColor),
  _transform(aTransform),
  _layer(aLayer)
{
  this->RefreshLayerOffset();
}

PLAActor::~PLAActor()
{
  GRA_DELETE(_layer);
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
  _functor.RunFunction(PLAActorFunctionCode::OnInit, this);
  for (PLAActor *actor : _actors) { actor->Init(); }
}

void PLAActor::Update()
{
  _functor.RunFunction(PLAActorFunctionCode::OnUpdate, this);
  for (PLAActor *actor : _actors) { actor->Update(); }
}

void PLAActor::Appear()
{
  _functor.RunFunction(PLAActorFunctionCode::OnAppear, this);
  for (PLAActor *actor : _actors) { actor->Appear(); }
}

void PLAActor::Disappear()
{
  _functor.RunFunction(PLAActorFunctionCode::OnDisappear, this);
  for (PLAActor *actor : _actors) { actor->Disappear(); }
}

void PLAActor::PrintActors() const
{
  static int indentLevel = 0;
  GRA_PRINT(this->GetObjectDescription().c_str());
  ++indentLevel;
  for (const PLAActor *actor : _actors)
  {
    for (int i = 0; i < indentLevel; i++) { GRA_PRINT("  "); }
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
    GRA_PRINT("aPoint : x %.2f : y %.2f\n", aPoint.x, aPoint.y);
    PLAPoint offset = PLAPoint((*it)->GetTransform().translation.x,
                               (*it)->GetTransform().translation.y);
    GRA_PRINT("offset : x %.2f : y %.2f\n", offset.x, offset.y);
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
  _layer->SetOffset(-PLAVec3(size.x * _pivot.x,
                             size.y * _pivot.y,
                             size.z * _pivot.z));
}
