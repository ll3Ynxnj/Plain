#include "PLAOBJActor.hpp"
#include "Object/Input/PLAInput.hpp"
#include "Object/PLAOBJError.hpp"

#include "Object/Layer/PLALYRPoint.hpp"
#include "Object/Layer/PLALYRLine.hpp"
#include "Object/Layer/PLALYRRect.hpp"
#include "Object/Layer/PLALYRCircle.hpp"
#include "Object/Layer/PLALYRTile.hpp"

#include "Object/PLAOBJError.hpp"

PLAOBJActor *PLAOBJActor::CreateRect(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLARect &aRect)
{
  //PLAOBJLayer *layer = PLALYRRect::Create(aRect, kPLAColorWhite, kPLAColorNone,
  //                                     kPLAStrUndefined, kPLARectNone);
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
  //PLAOBJLayer *layer = PLALYRRect::Create(aRect, aFillColor, kPLAColorNone,
  //                                     kPLAStrUndefined, kPLARectNone);
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
  //PLAOBJLayer *layer = PLALYRRect::Create(aRect, kPLAColorWhite, kPLAColorNone,
  //                                     aImageName, aClip);
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
  //PLAOBJLayer *layer = PLALYRCircle::Create(aCircle, kPLAColorWhite, kPLAColorNone,
  //                                       kPLAStrUndefined, kPLARectNone);
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
  //PLAOBJLayer *layer = PLALYRCircle::Create(aCircle, aFillColor, kPLAColorNone,
  //                                       kPLAStrUndefined, kPLARectNone);
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
  //PLAOBJLayer *layer = PLALYRCircle::Create(aCircle, kPLAColorWhite, kPLAColorNone,
  //                                       aImageName, aClip);
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
  //PLALYRTile *layer = PLALYRTile::Create(aOffset, aImageName, aTileSize, aChipSize,
  //                                       aDataSource);
  PLALYRTile *layer = new PLALYRTile(aOffset, aImageName, aTileSize, aChipSize,
                                     aDataSource);
  PLAOBJActor *actor = new PLAOBJActor(kPLAVec3fNone, kPLAColorWhite,
                                       kPLATransformNorm, layer);//, motion);
  actor->Bind();
  return actor;
}

/*
void PLAOBJActor::Bind(PLAOBJActor *aActor)
{
  GRAOBJBinder<PLAOBJActor>::Error error(GRAOBJBinder<PLAOBJActor>::Error::None);
  PLAOBJScene *scene = PLAOBJScene::Manager::Instance()->RefCurrentScene();
  scene->GRAOBJBinder<PLAOBJActor>::Bind(aActor, &error);
  if (error != GRAOBJBinder<PLAOBJActor>::Error::None) {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                    "Failed PLAObject binding. ERROR : %02d", error);
  }
}

void PLAOBJActor::Unbind(PLAOBJActor *aActor)
{
  GRAOBJBinder<PLAOBJActor>::Error error(GRAOBJBinder<PLAOBJActor>::Error::None);
  PLAOBJScene *scene = PLAOBJScene::Manager::Instance()->RefCurrentScene();
  scene->GRAOBJBinder<PLAOBJActor>::Unbind(aActor, &error);
}
*/

PLAOBJActor::PLAOBJActor(const PLAVec3f &aPivot,
                         const PLAColor &aColor,
                         const PLATransform &aTransform,
                         PLAOBJLayer *aLayer) ://,
                   //PLATMLMotionNode *aMotion) :
  PLAObject(PLAObjectType::Actor),//"== PLAOBJActor =="),
  PLAInputContext(),
  //PLAOBJTimelineNode::Holder(aMotion),
  PLATimelineHolder(),
  GRAOBJListener<PLAOBJScene, PLAOBJScene::FunctionCode>(),
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
  //_layer->Unbind();
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
  _functor.RunFunction(PLAOBJActorFunctionCode::OnInit, this);
  for (PLAOBJActor *actor : _actors) { actor->Init(); }
}

void PLAOBJActor::Update()
{
  //this->OnUpdateMotions();
  this->OnUpdate();
}

void PLAOBJActor::Appear()
{
  _functor.RunFunction(PLAOBJActorFunctionCode::OnAppear, this);
  for (PLAOBJActor *actor : _actors) { actor->Appear(); }
}

void PLAOBJActor::Disappear()
{
  _functor.RunFunction(PLAOBJActorFunctionCode::OnDisappear, this);
  for (PLAOBJActor *actor : _actors) { actor->Disappear(); }
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
  static const char *kName = "(ActorType)";//"== STUB ==";
  return kName;
}

bool PLAOBJActor::IsCollideWithPoint(PLAPoint aPoint) const
{
  //*
  return _layer->IsCollideWithPoint(aPoint);
  /*/
  // Provisional : Design that include PLACollider class is desirable.
  const PLAVec3f basePoint = _layer->GetOffset();
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
bool PLAOBJActor::IsCollideWithRect(PLARect aRect) const
{
  return false;
}
 */

PLAColor PLAOBJActor::GetColor() const
{
  PLAColor color = _color;
  /*
  if (this->GetProperties().contains(PLATMLMotionType::Color))
  {
    //_color * _motionProperties.at(PLATMLMotionType::Color).GetColor();
  }
   */
  return color;
};

PLATransform PLAOBJActor::GetTransform() const
{
  PLATransform transform = _transform;
  /*
  if (this->GetProperties().contains(PLATMLMotionType::Translation))
  {
    transform.translation +=
      this->GetProperties().at(PLATMLMotionType::Translation).GetVec3f();
  }
  if (this->GetProperties().contains(PLATMLMotionType::Rotation))
  {
    transform.rotation +=
      this->GetProperties().at(PLATMLMotionType::Rotation).GetVec3f();
  }
  if (this->GetProperties().contains(PLATMLMotionType::Scale))
  {
    PLAVec3f scale = this->GetProperties().at(PLATMLMotionType::Scale).GetVec3f();
    transform.scale.x *= scale.x;
    transform.scale.y *= scale.y;
    transform.scale.z *= scale.z;
  }
   */
  return transform;
};

/*
void PLAOBJActor::AddMotion(PLATMLMotionNode *aMotion)
{
  _motion.AddQueue(aMotion);
}
 */

/*
void PLAOBJActor::AddMotion(PLATMLMotionType aType, const PLAProperty &aDistance,
               PLAFloat aDuration)
{

}

void PLAOBJActor::AddMotionAlpha(PLAFloat aAlpha, PLAFloat aDuration)
{

}

void PLAOBJActor::AddMotionColor(const PLAColor &aColor, PLAFloat aDuration)
{

}

void PLAOBJActor::AddMotionTranslation(const PLAVec3f &aTranslation, PLAFloat aDuration)
{

}

void PLAOBJActor::AddMotionRotation(const PLAVec3f &aRotation, PLAFloat aDuration)
{

}

void PLAOBJActor::AddMotionScale(const PLAVec3f &aScale, PLAFloat aDuration)
{

}
 */

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
  if (_layer->GetLayerType() != PLAOBJLayerType::Point) { return nullptr; }
  return static_cast<PLALYRPoint *>(_layer);
}

PLALYRLine *PLAOBJActor::RefLYRLine()
{
  if (_layer->GetLayerType() != PLAOBJLayerType::Line) { return nullptr; }
  return static_cast<PLALYRLine *>(_layer);
}

PLALYRRect *PLAOBJActor::RefLYRRect()
{
  if (_layer->GetLayerType() != PLAOBJLayerType::Rect) { return nullptr; }
  return static_cast<PLALYRRect *>(_layer);
}

PLALYRCircle *PLAOBJActor::RefLYRCircle()
{
  if (_layer->GetLayerType() != PLAOBJLayerType::Circle) { return nullptr; }
  return static_cast<PLALYRCircle *>(_layer);
}

PLALYRTile *PLAOBJActor::RefLYRTile()
{
  if (_layer->GetLayerType() != PLAOBJLayerType::Tile) { return nullptr; }
  return static_cast<PLALYRTile *>(_layer);
}

/*
const PLALYRRect *PLAOBJActor::GetLayerRect() const
{
  if (this->GetLayerType() != PLAOBJLayerType::Circle)
  {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Primitive does not match.");
  }
  return static_cast<PLALYRRect *>(_layer);
}

const PLALYRCircle *PLAOBJActor::GetLayerCircle() const
{
  if (this->GetLayerType() != PLAOBJLayerType::Circle)
  {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Primitive does not match.");
  }
  return static_cast<PLALYRCircle *>(_layer);
}
*/

/*
void PLAOBJActor::UpdateMotions()
{
  GRA_PRINT("UpdateMotions()\n");
  _motion.Update();

  std::map<PLATMLMotionType, PLAProperty> properties =
    std::map<PLATMLMotionType, PLAProperty>();
  _motion.GetProperties(&properties);

  for (const auto &[key, value] : properties) {
    if (!_motionProperties.contains(key)) {
      _motionProperties[key] = PLATMLMotionNode::MakeProperty(key);
    }
    _motionProperties[key] = properties[key];
    GRA_PRINT("_motionProperties[%s]", PLATMLMotionNode::GetNameOfType(key));
    _motionProperties[key].Print();
  }
  for (PLAOBJActor *actor : _actors) { actor->UpdateMotions(); }
}
 */

void PLAOBJActor::AddTileMotion(const PLAVec2s &aAddress, PLATMLMotion *aThread)
{
  PLALYRTile *layer = this->RefLYRTile();
  if (!layer) {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                    "LayerType is not Tile.");
  }
  layer->AddMotionThread(aAddress, aThread);
}

/*
void PLAOBJActor::AddTileMotions(const PLAVec2s &aAddress,
                              const std::vector<PLATMLMotionNode *> &aMotions)
{
  PLALYRTile *layer = this->RefLYRTile();
  if (!layer) {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                    "LayerType is not Tile.");
  }
  layer->AddMotions(aAddress, aMotions);
}
 */

/*
void PLAOBJActor::SetTileMotion(const PLAVec2s &aAddress, PLATMLMotionNode *aMotion)
{
  PLALYRTile *layer = this->RefLYRTile();
  if (!layer) {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                    "LayerType is not Tile.");
  }
  layer->SetMotion(aAddress, aMotion);
}
 */

void PLAOBJActor::RefreshLayerOffset()
{
  PLAVec3f size(this->GetSize());
  _layer->SetOffset(-PLAVec3f(size.x * _pivot.x,
                             size.y * _pivot.y,
                             size.z * _pivot.z));
}

void PLAOBJActor::OnUpdate()
{
  _functor.RunFunction(PLAOBJActorFunctionCode::OnUpdate, this);
  for (PLAOBJActor *actor : _actors) { actor->OnUpdate(); }
}

/*
void PLAOBJActor::OnUpdateMotions()
{
  //this->UpdateMotionProperties();
  //_layer->UpdateMotionProperties();
  for (PLAOBJActor *actor : _actors) { actor->OnUpdateMotions(); }
}
 */

const char *PLAOBJActor::GetBinderItemTypeName() const
{
  return this->GetActorTypeName();
}
