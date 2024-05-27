#include "Core/Object/Actor/PLAOBJActor.hpp"
#include "Core/Object/Input/PLAInput.hpp"
#include "Core/Object/PLAOBJError.hpp"

#include "Core/Object/Layer/PLALYRPoint.hpp"
#include "Core/Object/Layer/PLALYRLine.hpp"
#include "Core/Object/Layer/PLALYRRect.hpp"
#include "Core/Object/Layer/PLALYRCircle.hpp"
#include "Core/Object/Layer/PLALYRTile.hpp"

#include "Core/Object/PLAOBJError.hpp"
#include "Core/Object/Layer/PLALYRTile.hpp"

#include "Core/Agent/Actor/PLAAGTActor.hpp"
#include "Core/Agent/Actor/PLAAGTActorForRect.hpp"
#include "Core/Agent/Actor/PLAAGTActorForCircle.hpp"
#include "Core/Agent/Actor/PLAAGTActorForTile.hpp"

// 不要なのでは？同じくBinderItemであるPLAOBJResourceには無い。要調査。
// It's not necessary? PLAOBJResource, which is also a BinderItem, does not have it. Need to investigate.
const std::map<PLAOBJActor::Binder::Error, const char *> PLAOBJActor::kBinderErrorMessages =
{
  { Binder::Error::OverwriteItem, "Overwrite item" },
  { Binder::Error::NameConflict, "Item name conflict" },
  { Binder::Error::NameOverride, "Item name has been over written" },
  { Binder::Error::NameConvertedBySystem, "Item name has been converted to system-generated" },
  { Binder::Error::RegisterExistingKeyToMap, "Register existing key to map" },
  { Binder::Error::NotExistInMap, "Not exist in map" },
  { Binder::Error::OutOfRange, "Out of range" },
};

// 不要なのでは？同じくBinderItemであるPLAOBJResourceには無い。要調査。
// It's not necessary? PLAOBJResource, which is also a BinderItem, does not have it. Need to investigate.
const char *PLAOBJActor::GetBinderErrorMessage(Binder::Error aError)
{
  return kBinderErrorMessages.at(aError);
}

PLAOBJActor *PLAOBJActor::Object(const PLAString &aName)
{
  auto object = PLAObject::Object(PLAObjectType::Actor, aName);
  return static_cast<PLAOBJActor *>(object);
}

PLAOBJActor *PLAOBJActor::Object(PLAId aId)
{
  auto object = PLAObject::Object(PLAObjectType::Actor, aId);
  return static_cast<PLAOBJActor *>(object);
}

PLAOBJActor *PLAOBJActor::ObjectWithTag(PLAId aTag)
{
  GRAOBJBinder<PLAOBJActor>::Error error(GRAOBJBinder<PLAOBJActor>::Error::None);
  auto object = Manager::Instance()->RefItemWithTag(aTag, &error);
  if (error != GRAOBJBinder<PLAOBJActor>::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJActor getting. ERROR : %02d", error);
  }
  return static_cast<PLAOBJActor *>(object);
}

PLAOBJActor *PLAOBJActor::CreateRect(const PLAVec2f &aOrigin,
                                     const PLAVec2f &aSize,
                                     const PLAColor &aFillColor,
                                     const PLAString &aName)
{
  PLARect rect = PLARect(kPLAVec2fNone, aSize);
  PLAOBJLayer *layer = new PLALYRRect(rect, aFillColor, kPLAColorNone,
                                      kPLAStrUndefined, kPLARectNone);
  PLATransform transform = PLATransform(PLAVec3f(aOrigin.x, aOrigin.y, 0.0f),
                                        kPLAVec3fNone, kPLAVec3fNorm);

  PLAOBJActor *actor =
    aName != kPLAStrUndefined ?
    new PLAOBJActor(kPLAVec3fNone, kPLAColorWhite, transform, layer) :
    new PLAOBJActor(kPLAVec3fNone, kPLAColorWhite, transform, layer, aName);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateRect(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLARect &aRect,
                                     const PLAString &aName)
{
  PLAOBJLayer *layer = new PLALYRRect(aRect, kPLAColorWhite, kPLAColorNone,
                                      kPLAStrUndefined, kPLARectNone);

  //PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
  PLAOBJActor *actor =
    aName != kPLAStrUndefined ?
    new PLAOBJActor(aPivot, aColor, aTransform, layer) :
    new PLAOBJActor(aPivot, aColor, aTransform, layer, aName);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateRect(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLARect &aRect,
                                     const PLAColor &aFillColor,
                                     const PLAString &aName)
{
  PLAOBJLayer *layer = new PLALYRRect(aRect, aFillColor, kPLAColorNone,
                                      kPLAStrUndefined, kPLARectNone);
  //PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
  PLAOBJActor *actor =
    aName != kPLAStrUndefined ?
    new PLAOBJActor(aPivot, aColor, aTransform, layer) :
    new PLAOBJActor(aPivot, aColor, aTransform, layer, aName);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateRect(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLARect &aRect,
                                     const std::string &aImageName,
                                     const PLARect &aClip,
                                     const PLAString &aName)
{
  PLAOBJLayer *layer = new PLALYRRect(aRect, kPLAColorWhite, kPLAColorNone,
                                      aImageName, aClip);
  //PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
  PLAOBJActor *actor =
    aName != kPLAStrUndefined ?
    new PLAOBJActor(aPivot, aColor, aTransform, layer) :
    new PLAOBJActor(aPivot, aColor, aTransform, layer, aName);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateCircle(const PLAVec2f &aOrigin,
                                       const PLAFloat aRadius,
                                       const PLAColor &aFillColor,
                                       const PLAString &aName)
{
  PLACircle circle = PLACircle(kPLAVec2fNone, aRadius);
  PLAOBJLayer *layer = new PLALYRCircle(circle, aFillColor, kPLAColorNone,
                                        kPLAStrUndefined, kPLARectNone);
  PLATransform transform = PLATransform(PLAVec3f(aOrigin.x, aOrigin.y, 0.0f),
                                        kPLAVec3fNone, kPLAVec3fNorm);

  //PLAOBJActor *actor = new PLAOBJActor(kPLAVec3fNone, kPLAColorWhite, transform, layer);
  PLAOBJActor *actor =
    aName != kPLAStrUndefined ?
    new PLAOBJActor(kPLAVec3fNone, kPLAColorWhite, transform, layer) :
    new PLAOBJActor(kPLAVec3fNone, kPLAColorWhite, transform, layer, aName);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateCircle(const PLAVec3f &aPivot,
                                       const PLAColor &aColor,
                                       const PLATransform &aTransform,
                                       const PLACircle &aCircle,
                                       const PLAString &aName)
{
  PLAOBJLayer *layer = new PLALYRCircle(aCircle, kPLAColorWhite, kPLAColorNone,
                                        kPLAStrUndefined, kPLARectNone);
  //PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
  PLAOBJActor *actor =
    aName != kPLAStrUndefined ?
    new PLAOBJActor(aPivot, aColor, aTransform, layer) :
    new PLAOBJActor(aPivot, aColor, aTransform, layer, aName);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateCircle(const PLAVec3f &aPivot,
                                       const PLAColor &aColor,
                                       const PLATransform &aTransform,
                                       const PLACircle &aCircle,
                                       const PLAColor &aFillColor,
                                       const PLAString &aName)
{
  PLAOBJLayer *layer = new PLALYRCircle(aCircle, aFillColor, kPLAColorNone,
                                        kPLAStrUndefined, kPLARectNone);
  //PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
  PLAOBJActor *actor =
    aName != kPLAStrUndefined ?
    new PLAOBJActor(aPivot, aColor, aTransform, layer) :
    new PLAOBJActor(aPivot, aColor, aTransform, layer, aName);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateCircle(const PLAVec3f &aPivot,
                                       const PLAColor &aColor,
                                       const PLATransform &aTransform,
                                       const PLACircle &aCircle,
                                       const std::string &aImageName,
                                       const PLARect &aClip,
                                       const PLAString &aName)
{
  PLAOBJLayer *layer = new PLALYRCircle(aCircle, kPLAColorWhite, kPLAColorNone,
                                        aImageName, aClip);
  //PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
  PLAOBJActor *actor =
    aName != kPLAStrUndefined ?
    new PLAOBJActor(aPivot, aColor, aTransform, layer) :
    new PLAOBJActor(aPivot, aColor, aTransform, layer, aName);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateTile(const PLAVec2f &aOffset,
                                     const std::string &aImageName,
                                     const GRAVec2<PLASize> &aTileSize,
                                     const GRAVec2<PLASize> &aChipSize,
                                     const IPLATileLayerDataSource *aDataSource,
                                     const PLAString &aName)
{
  PLALYRTile *layer = new PLALYRTile(aOffset, aImageName, aTileSize, aChipSize,
                                     aDataSource);
  //PLAOBJActor *actor = new PLAOBJActor(kPLAVec3fNone, kPLAColorWhite,
  //                                     kPLATransformNorm, layer);//, motion);
  PLAOBJActor *actor =
    aName != kPLAStrUndefined ?
    new PLAOBJActor(kPLAVec3fNone, kPLAColorWhite, kPLATransformNorm, layer) :
    new PLAOBJActor(kPLAVec3fNone, kPLAColorWhite, kPLATransformNorm, layer, aName);
  actor->Init();
  actor->Bind();
  return actor;
}

void PLAOBJActor::Bind()
{
  this->PLAObject::Bind();

  GRAOBJBinder<PLAOBJActor>::Error error(GRAOBJBinder<PLAOBJActor>::Error::None);
  PLAOBJActor::Manager::Instance()->Bind(this, &error);
  if (error != GRAOBJBinder<PLAOBJActor>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJActor binding. ERROR : %02d", error); }
}

void PLAOBJActor::Unbind()
{
  GRAOBJBinder<PLAOBJActor>::Error error(GRAOBJBinder<PLAOBJActor>::Error::None);
  PLAOBJActor::Manager::Instance()->Unbind(this, &error);
  if (error != GRAOBJBinder<PLAOBJActor>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJActor unbinding. ERROR : %02d", error); }

  this->RemoveFromParentActor();
  PLAObject::Unbind();
}

PLAOBJActor::PLAOBJActor(const PLAVec3f &aPivot,
                         const PLAColor &aColor,
                         const PLATransform &aTransform,
                         PLAOBJLayer *aLayer) :
  PLAObject(PLAObjectType::Actor),//"== PLAOBJActor =="),
  GRAOBJBinder<PLAOBJActor>::Item(Manager::Instance()),
  PLAInputContext(),
  PLAMotionHolder(),
  _pivot(aPivot),
  _color(aColor),
  _transform(aTransform),
  _layer(aLayer)
{
  this->RefreshLayerOffset();
}

PLAOBJActor::PLAOBJActor(const PLAVec3f &aPivot,
                         const PLAColor &aColor,
                         const PLATransform &aTransform,
                         PLAOBJLayer *aLayer,
                         const PLAString &aName) :
  PLAObject(PLAObjectType::Actor, aName),//"== PLAOBJActor =="),
  GRAOBJBinder<PLAOBJActor>::Item(Manager::Instance()),
  PLAInputContext(),
  PLAMotionHolder(),
  _pivot(aPivot),
  _color(aColor),
  _transform(aTransform),
  _layer(aLayer)
{
  this->RefreshLayerOffset();
}

PLAOBJActor::~PLAOBJActor() noexcept
{
  GRA_DELETE(_layer);
}

void PLAOBJActor::AddActor(PLAOBJActor *aActor)
{
  aActor->_parent = this;
  _actors.push_back(aActor);
}

void PLAOBJActor::RemoveActor(PLAOBJActor *aActor)
{
  aActor->_parent = nullptr;
  _actors.remove(aActor);
}

void PLAOBJActor::RemoveFromParentActor()
{
  if (_parent) { _parent->RemoveActor(this); }
  else { PLA_ERROR_ISSUE(PLAErrorType::Expect, "Parent actor is not exist."); }
}

void PLAOBJActor::Input(const PLAInput *aInput)
{

}

void PLAOBJActor::Init()
{
  //_functor.RunFunction(PLAFunctionCode::Actor::OnInit, this);
  //for (PLAOBJActor *actor : _actors) { actor->Init(); }
}

void PLAOBJActor::Update()
{
  //this->OnUpdateMotions();
  this->OnUpdate();
}

void PLAOBJActor::Appear()
{
  _functor.RunFunction(PLAFunctionCode::Actor::OnAppear, this);
  for (PLAOBJActor *actor : _actors) { actor->Appear(); }
}

void PLAOBJActor::Disappear()
{
  _functor.RunFunction(PLAFunctionCode::Actor::OnDisappear, this);
  for (PLAOBJActor *actor : _actors) { actor->Disappear(); }
}

PLAAGTActor PLAOBJActor::AssignAgent() {
  return PLAAGTActor(this);
}

PLAAGTActorForRect PLAOBJActor::AssignAgentForRect() {
  if (this->GetLayerType() != PLALayerType::Rect)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Layer type is not rect."); }
  return PLAAGTActorForRect(this);
}

PLAAGTActorForCircle PLAOBJActor::AssignAgentForCircle() {
  if (this->GetLayerType() != PLALayerType::Circle)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Layer type is not circle."); }
  return PLAAGTActorForCircle(this);
}

PLAAGTActorForTile PLAOBJActor::AssignAgentForTile() {
  if (this->GetLayerType() != PLALayerType::Tile)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Layer type is not tile."); }
  return PLAAGTActorForTile(this);
}

PLAId PLAOBJActor::GetActorTag() const {
  return this->GRAOBJBinder<PLAOBJActor>::Item::GetTag();
}

void PLAOBJActor::SetActorTag(PLAId aTag)
{
  Binder::Error error(Binder::Error::None);
  this->Binder::Item::SetTag(aTag, &error);
  if (error != Binder::Error::None)
  {
    switch (error) {
      case GRAOBJBinder<PLAOBJActor>::Error::TagOverride :
        PLA_ERROR_ISSUE(PLAErrorType::Expect,
                        "Succeed to set phase tag with error. ERROR : %02d : %s",
                        error, PLAOBJActor::GetBinderErrorMessage(error));
        break;
      default :
        PLA_ERROR_ISSUE(PLAErrorType::Assert,
                        "Failure to set phase tag. ERROR : %02d : %s",
                        error, PLAOBJActor::GetBinderErrorMessage(error));
        break;
    }
  }
}

void PLAOBJActor::PrintActors() const
{
  static int indentLevel = 0;
  GRA_PRINT(this->GetObjectDescription().c_str());
  ++indentLevel;
  for (const PLAOBJActor *actor : _actors)
  {
    for (int i = 0; i < indentLevel; i++) { GRA_PRINT("  "); }
    actor->PrintActors();
  }
  --indentLevel;
}

const char *PLAOBJActor::GetActorTypeName() const
{
  static const char *kName = "(STUB: ActorType)";//"== STUB ==";
  return kName;
};

bool PLAOBJActor::IsCollideWithPoint(PLAPoint aPoint) const
{
  return _layer->IsCollideWithPoint(aPoint);
};

PLAOBJActor *PLAOBJActor::RefResponsiveActor(const PLAInputDeviceType aDeviceType,
                                             const PLAInputSignalCode aSignalCode)
{
  for (std::list<PLAOBJActor *>::const_reverse_iterator it = _actors.rbegin();
       it != _actors.rend(); it++)
  {
    PLAOBJActor *actor = (*it)->RefResponsiveActor(aDeviceType, aSignalCode);
    if (actor) { return actor; }
  }

  if (this->IsInputResponsive(aDeviceType, aSignalCode)) { return this; }

  return nullptr;
}

PLAOBJActor *PLAOBJActor::RefResponsiveActorWithPoint
  (const PLAPoint &aPoint,
   const PLAInputDeviceType aDeviceType,
   const PLAInputSignalCode aSignalCode)
{
  for (std::list<PLAOBJActor *>::reverse_iterator it = _actors.rbegin();
       it != _actors.rend(); it++)
  {
    GRA_PRINT("aPoint : x %.2f : y %.2f\n", aPoint.x, aPoint.y);
    PLAPoint offset = PLAPoint((*it)->GetTransform().translation.x,
                               (*it)->GetTransform().translation.y);
    GRA_PRINT("offset : x %.2f : y %.2f\n", offset.x, offset.y);
    PLAOBJActor *actor =
      (*it)->RefResponsiveActorWithPoint(aPoint - offset,
                                         aDeviceType, aSignalCode);
    if (actor) { return actor; }
  }

  if (this->IsCollideWithPoint(aPoint))
  {
    if (this->IsInputResponsive(aDeviceType, aSignalCode)) { return this; }
  }

  return nullptr;
}

PLALYRPoint *PLAOBJActor::RefLayerForPoint()
{
  if (_layer->GetLayerType() != PLALayerType::Point) { return nullptr; }
  return static_cast<PLALYRPoint *>(_layer);
}

PLALYRLine *PLAOBJActor::RefLayerForLine()
{
  if (_layer->GetLayerType() != PLALayerType::Line) { return nullptr; }
  return static_cast<PLALYRLine *>(_layer);
}

PLALYRRect *PLAOBJActor::RefLayerForRect()
{
  if (_layer->GetLayerType() != PLALayerType::Rect) { return nullptr; }
  return static_cast<PLALYRRect *>(_layer);
}

PLALYRCircle *PLAOBJActor::RefLayerForCircle()
{
  if (_layer->GetLayerType() != PLALayerType::Circle) { return nullptr; }
  return static_cast<PLALYRCircle *>(_layer);
}

PLALYRTile *PLAOBJActor::RefLayerForTile()
{
  if (_layer->GetLayerType() != PLALayerType::Tile) { return nullptr; }
  return static_cast<PLALYRTile *>(_layer);
}

/*
void PLAOBJActor::AddTileMotion(const PLATileDataAddress &aAddress, PLATMLMotion *aThread)
{
  PLALYRTile *layer = this->RefLayerForTile();
  if (!layer) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "LayerType is not Tile.");
  }
  layer->AddMotionThread(aAddress, aThread);
}
 */

void PLAOBJActor::RefreshLayerOffset()
{
  PLAVec3f size(this->GetSize());

  auto offset = _layer->GetOffset();
  _layer->SetOffset(PLAVec3f(offset.x - size.x * _pivot.x,
                             offset.y - size.y * _pivot.y,
                             offset.z - size.z * _pivot.z));
}

void PLAOBJActor::OnUpdate()
{
  _functor.RunFunction(PLAFunctionCode::Actor::OnUpdate, this);
  for (PLAOBJActor *actor : _actors) { actor->OnUpdate(); }
}

//-- GRAOBJBinder::Item --/////////////////////////////////////////////////////////

const char *PLAOBJActor::GetBinderItemTypeName() const
{
  return this->GetActorTypeName();
}

// PLAOBJActor::Manager ////////////////////////////////////////////////////////

PLAOBJActor::Manager PLAOBJActor::Manager::_instance = PLAOBJActor::Manager();

PLAOBJActor::Manager::Manager() : GRAOBJBinder<PLAOBJActor>()
{

}

PLAOBJActor::Manager::~Manager()
{

}

void PLAOBJActor::Manager::Init()
{
  GRAOBJBinder<PLAOBJActor>::Init();
}

PLAOBJActor *PLAOBJActor::Manager::Actor(const PLAString &aKey)
{
  GRAOBJBinder<PLAOBJActor>::Error error(GRAOBJBinder<PLAOBJActor>::Error::None);
  return static_cast<PLAOBJActor *>(_instance.RefItemWithName(aKey, &error));
}

void PLAOBJActor::Manager::PrintActors() const
{

};

const PLAOBJActor *PLAOBJActor::Manager::GetActor(const PLAString &aName) const
{
  PLAActorError error = PLAActorError::None;
  const PLAOBJActor *resource =
    static_cast<const PLAOBJActor *>(this->GetItemWithName(aName, &error));
  if (error != PLAActorError::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to get resource. ERROR : %02d", error);
  }
  return resource;
};
