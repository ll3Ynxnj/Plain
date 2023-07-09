#include "PLAOBJActor.hpp"
#include "Object/Input/PLAInput.hpp"
#include "Object/PLAOBJError.hpp"

#include "Object/Layer/PLALYRPoint.hpp"
#include "Object/Layer/PLALYRLine.hpp"
#include "Object/Layer/PLALYRRect.hpp"
#include "Object/Layer/PLALYRCircle.hpp"
#include "Object/Layer/PLALYRTile.hpp"

#include "Object/PLAOBJError.hpp"

#include "Agent/PLAAGTActor.hpp"

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
                                     const PLAColor &aFillColor)
{
  PLARect rect = PLARect(kPLAVec2fNone, aSize);
  PLAOBJLayer *layer = new PLALYRRect(rect, aFillColor, kPLAColorNone,
                                      kPLAStrUndefined, kPLARectNone);
  PLATransform transform = PLATransform(PLAVec3f(aOrigin.x, aOrigin.y, 0.0f),
                                        kPLAVec3fNone, kPLAVec3fNorm);

  PLAOBJActor *actor = new PLAOBJActor(kPLAVec3fNone, kPLAColorWhite, transform, layer);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateRect(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLARect &aRect)
{
  PLAOBJLayer *layer = new PLALYRRect(aRect, kPLAColorWhite, kPLAColorNone,
                                      kPLAStrUndefined, kPLARectNone);

  PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateRect(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLARect &aRect,
                                     const PLAColor &aFillColor)
{
  PLAOBJLayer *layer = new PLALYRRect(aRect, aFillColor, kPLAColorNone,
                                      kPLAStrUndefined, kPLARectNone);
  PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateRect(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLARect &aRect,
                                     const std::string &aImageName,
                                     const PLARect &aClip)
{
  PLAOBJLayer *layer = new PLALYRRect(aRect, kPLAColorWhite, kPLAColorNone,
                                      aImageName, aClip);
  PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateCircle(const PLAVec2f &aOrigin,
                                       const PLAFloat aRadius,
                                       const PLAColor &aFillColor)
{
  PLACircle circle = PLACircle(kPLAVec2fNone, aRadius);
  PLAOBJLayer *layer = new PLALYRCircle(circle, aFillColor, kPLAColorNone,
                                        kPLAStrUndefined, kPLARectNone);
  PLATransform transform = PLATransform(PLAVec3f(aOrigin.x, aOrigin.y, 0.0f),
                                        kPLAVec3fNone, kPLAVec3fNorm);

  PLAOBJActor *actor = new PLAOBJActor(kPLAVec3fNone, kPLAColorWhite, transform, layer);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateCircle(const PLAVec3f &aPivot,
                                       const PLAColor &aColor,
                                       const PLATransform &aTransform,
                                       const PLACircle &aCircle)
{
  PLAOBJLayer *layer = new PLALYRCircle(aCircle, kPLAColorWhite, kPLAColorNone,
                                        kPLAStrUndefined, kPLARectNone);
  PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateCircle(const PLAVec3f &aPivot,
                                       const PLAColor &aColor,
                                       const PLATransform &aTransform,
                                       const PLACircle &aCircle,
                                       const PLAColor &aFillColor)
{
  PLAOBJLayer *layer = new PLALYRCircle(aCircle, aFillColor, kPLAColorNone,
                                        kPLAStrUndefined, kPLARectNone);
  PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateCircle(const PLAVec3f &aPivot,
                                       const PLAColor &aColor,
                                       const PLATransform &aTransform,
                                       const PLACircle &aCircle,
                                       const std::string &aImageName,
                                       const PLARect &aClip)
{
  PLAOBJLayer *layer = new PLALYRCircle(aCircle, kPLAColorWhite, kPLAColorNone,
                                        aImageName, aClip);
  PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
  actor->Init();
  actor->Bind();
  return actor;
}

PLAOBJActor *PLAOBJActor::CreateTile(const PLAVec2f &aOffset,
                                     const std::string &aImageName,
                                     const GRAVec2<PLASize> &aTileSize,
                                     const GRAVec2<PLASize> &aChipSize,
                                     const IPLATileLayerDataSource *aDataSource)
{
  PLALYRTile *layer = new PLALYRTile(aOffset, aImageName, aTileSize, aChipSize,
                                     aDataSource);
  PLAOBJActor *actor = new PLAOBJActor(kPLAVec3fNone, kPLAColorWhite,
                                       kPLATransformNorm, layer);//, motion);
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
  PLATimelineHolder(),
  //GRAOBJListener<PLAOBJScene, PLAFunctionCode::Scene>(),
  //PLAOBJPhase::Listener(),
  //GRAOBJBinder<PLAOBJActor>::Item(Manager::Instance()),
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
}

bool PLAOBJActor::IsCollideWithPoint(PLAPoint aPoint) const
{
  return _layer->IsCollideWithPoint(aPoint);
}

PLAColor PLAOBJActor::GetColor() const
{
  PLAColor color = _color;
  return color;
};

PLATransform PLAOBJActor::GetTransform() const
{
  PLATransform transform = _transform;
  return transform;
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

  if (this->IsResponsive(aDeviceType, aSignalCode)) { return this; }

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
    if (this->IsResponsive(aDeviceType, aSignalCode)) { return this; }
  }

  return nullptr;
}

PLALYRPoint *PLAOBJActor::RefLYRPoint()
{
  if (_layer->GetLayerType() != PLALayerType::Point) { return nullptr; }
  return static_cast<PLALYRPoint *>(_layer);
}

PLALYRLine *PLAOBJActor::RefLYRLine()
{
  if (_layer->GetLayerType() != PLALayerType::Line) { return nullptr; }
  return static_cast<PLALYRLine *>(_layer);
}

PLALYRRect *PLAOBJActor::RefLYRRect()
{
  if (_layer->GetLayerType() != PLALayerType::Rect) { return nullptr; }
  return static_cast<PLALYRRect *>(_layer);
}

PLALYRCircle *PLAOBJActor::RefLYRCircle()
{
  if (_layer->GetLayerType() != PLALayerType::Circle) { return nullptr; }
  return static_cast<PLALYRCircle *>(_layer);
}

PLALYRTile *PLAOBJActor::RefLYRTile()
{
  if (_layer->GetLayerType() != PLALayerType::Tile) { return nullptr; }
  return static_cast<PLALYRTile *>(_layer);
}

void PLAOBJActor::AddTileMotion(const PLAVec2s &aAddress, PLATMLMotion *aThread)
{
  PLALYRTile *layer = this->RefLYRTile();
  if (!layer) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "LayerType is not Tile.");
  }
  layer->AddMotionThread(aAddress, aThread);
}

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
