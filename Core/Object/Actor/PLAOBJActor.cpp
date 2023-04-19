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

PLAOBJActor *PLAOBJActor::CreateRect(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLARect &aRect)
{
  PLAOBJLayer *layer = new PLALYRRect(aRect, kPLAColorWhite, kPLAColorNone,
                                      kPLAStrUndefined, kPLARectNone);

  PLAOBJActor *actor = new PLAOBJActor(aPivot, aColor, aTransform, layer);//, motion);
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
  actor->Bind();
  return actor;
}

PLAOBJActor::PLAOBJActor(const PLAVec3f &aPivot,
                         const PLAColor &aColor,
                         const PLATransform &aTransform,
                         PLAOBJLayer *aLayer) :
  PLAObject(PLAObjectType::Actor),//"== PLAOBJActor =="),
  PLAInputContext(),
  PLATimelineHolder(),
  //GRAOBJListener<PLAOBJScene, PLAFunctionCode::Scene>(),
  PLAOBJScene::Listener(),
  GRAOBJBinder<PLAOBJActor>::Item(),
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

void PLAOBJActor::Unbind()
{
  PLAObject::Unbind();
}

void PLAOBJActor::AddActor(PLAOBJActor *aActor)
{
  _actors.push_back(aActor);
}

void PLAOBJActor::Input(const PLAInput *aInput)
{

}

void PLAOBJActor::Init()
{
  _functor.RunFunction(PLAFunctionCode::Actor::OnInit, this);
  for (PLAOBJActor *actor : _actors) { actor->Init(); }
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
  _layer->SetOffset(-PLAVec3f(size.x * _pivot.x,
                             size.y * _pivot.y,
                             size.z * _pivot.z));
}

void PLAOBJActor::OnUpdate()
{
  _functor.RunFunction(PLAFunctionCode::Actor::OnUpdate, this);
  for (PLAOBJActor *actor : _actors) { actor->OnUpdate(); }
}

const char *PLAOBJActor::GetBinderItemTypeName() const
{
  return this->GetActorTypeName();
}
