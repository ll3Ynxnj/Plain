#include "PLAActor.hpp"
#include "Object/Input/PLAInput.hpp"
#include "Object/PLAError.hpp"

#include "Object/Layer/PLALYRPoint.hpp"
#include "Object/Layer/PLALYRLine.hpp"
#include "Object/Layer/PLALYRRect.hpp"
#include "Object/Layer/PLALYRCircle.hpp"
#include "Object/Layer/PLALYRTile.hpp"

#include "Object/PLAError.hpp"

PLAActor *PLAActor::CreateRect(const PLAVec3 &aPivot,
                               const PLAColor &aColor,
                               const PLATransform &aTransform,
                               const PLARect &aRect)
{
  //PLALayer *layer = PLALYRRect::Create(aRect, kPLAColorWhite, kPLAColorNone,
  //                                     kPLAStrUndefined, kPLARectNone);
  PLALayer *layer = new PLALYRRect(aRect, kPLAColorWhite, kPLAColorNone,
                                   kPLAStrUndefined, kPLARectNone);

  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, layer);//, motion);
  actor->Bind();
  return actor;
}

PLAActor *PLAActor::CreateRect(const PLAVec3 &aPivot,
                               const PLAColor &aColor,
                               const PLATransform &aTransform,
                               const PLARect &aRect,
                               const PLAColor &aFillColor)
{
  //PLALayer *layer = PLALYRRect::Create(aRect, aFillColor, kPLAColorNone,
  //                                     kPLAStrUndefined, kPLARectNone);
  PLALayer *layer = new PLALYRRect(aRect, aFillColor, kPLAColorNone,
                                   kPLAStrUndefined, kPLARectNone);
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, layer);//, motion);
  actor->Bind();
  return actor;
}

PLAActor *PLAActor::CreateRect(const PLAVec3 &aPivot,
                               const PLAColor &aColor,
                               const PLATransform &aTransform,
                               const PLARect &aRect,
                               const std::string &aImageName,
                               const PLARect &aClip)
{
  //PLALayer *layer = PLALYRRect::Create(aRect, kPLAColorWhite, kPLAColorNone,
  //                                     aImageName, aClip);
  PLALayer *layer = new PLALYRRect(aRect, kPLAColorWhite, kPLAColorNone,
                                   aImageName, aClip);
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, layer);//, motion);
  actor->Bind();
  return actor;
}

PLAActor *PLAActor::CreateCircle(const PLAVec3 &aPivot,
                                 const PLAColor &aColor,
                                 const PLATransform &aTransform,
                                 const PLACircle &aCircle)
{
  //PLALayer *layer = PLALYRCircle::Create(aCircle, kPLAColorWhite, kPLAColorNone,
  //                                       kPLAStrUndefined, kPLARectNone);
  PLALayer *layer = new PLALYRCircle(aCircle, kPLAColorWhite, kPLAColorNone,
                                     kPLAStrUndefined, kPLARectNone);
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, layer);//, motion);
  actor->Bind();
  return actor;
}

PLAActor *PLAActor::CreateCircle(const PLAVec3 &aPivot,
                                 const PLAColor &aColor,
                                 const PLATransform &aTransform,
                                 const PLACircle &aCircle,
                                 const PLAColor &aFillColor)
{
  //PLALayer *layer = PLALYRCircle::Create(aCircle, aFillColor, kPLAColorNone,
  //                                       kPLAStrUndefined, kPLARectNone);
  PLALayer *layer = new PLALYRCircle(aCircle, aFillColor, kPLAColorNone,
                                     kPLAStrUndefined, kPLARectNone);
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, layer);//, motion);
  actor->Bind();
  return actor;
}

PLAActor *PLAActor::CreateCircle(const PLAVec3 &aPivot,
                                 const PLAColor &aColor,
                                 const PLATransform &aTransform,
                                 const PLACircle &aCircle,
                                 const std::string &aImageName,
                                 const PLARect &aClip)
{
  //PLALayer *layer = PLALYRCircle::Create(aCircle, kPLAColorWhite, kPLAColorNone,
  //                                       aImageName, aClip);
  PLALayer *layer = new PLALYRCircle(aCircle, kPLAColorWhite, kPLAColorNone,
                                     aImageName, aClip);
  PLAActor *actor = new PLAActor(aPivot, aColor, aTransform, layer);//, motion);
  actor->Bind();
  return actor;
}

PLAActor *PLAActor::CreateTile(const PLAVec2 &aOffset,
                               const std::string &aImageName,
                               const GRAVec2<PLASize> &aTileSize,
                               const GRAVec2<PLASize> &aChipSize,
                               const IPLALYRTileDataSource *aDataSource)
{
  //PLALYRTile *layer = PLALYRTile::Create(aOffset, aImageName, aTileSize, aChipSize,
  //                                       aDataSource);
  PLALYRTile *layer = new PLALYRTile(aOffset, aImageName, aTileSize, aChipSize,
                                     aDataSource);
  PLAActor *actor = new PLAActor(kPLAVec3None, kPLAColorWhite,
                                 kPLATransformNorm, layer);//, motion);
  actor->Bind();
  return actor;
}

/*
void PLAActor::Bind(PLAActor *aActor)
{
  GRABinder<PLAActor>::Error error(GRABinder<PLAActor>::Error::None);
  PLAScene *scene = PLAScene::Manager::Instance()->RefCurrentScene();
  scene->GRABinder<PLAActor>::Bind(aActor, &error);
  if (error != GRABinder<PLAActor>::Error::None) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAObject binding. ERROR : %02d", error);
  }
}

void PLAActor::Unbind(PLAActor *aActor)
{
  GRABinder<PLAActor>::Error error(GRABinder<PLAActor>::Error::None);
  PLAScene *scene = PLAScene::Manager::Instance()->RefCurrentScene();
  scene->GRABinder<PLAActor>::Unbind(aActor, &error);
}
*/

PLAActor::PLAActor(const PLAVec3 &aPivot,
                   const PLAColor &aColor,
                   const PLATransform &aTransform,
                   PLALayer *aLayer) ://,
                   //PLAMotionNode *aMotion) :
  PLAObject(PLAObjectType::Actor),//"== PLAActor =="),
  PLAInputContext(),
  //PLATimelineNode::Holder(aMotion),
  PLATimelineHolder(),
  GRAListener<PLAScene, PLAScene::FunctionCode>(),
  GRABinder<PLAActor>::Item(),
  _pivot(aPivot),
  _color(aColor),
  _transform(aTransform),
  _layer(aLayer)
{
  this->RefreshLayerOffset();
}

PLAActor::~PLAActor() noexcept
{
  GRA_DELETE(_layer);
}

void PLAActor::Unbind()
{
  //_layer->Unbind();
  PLAObject::Unbind();
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
  //this->OnUpdateMotions();
  this->OnUpdate();
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

const char *PLAActor::GetActorTypeName() const
{
  static const char *kName = "(ActorType)";//"== STUB ==";
  return kName;
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

PLAColor PLAActor::GetColor() const
{
  PLAColor color = _color;
  /*
  if (this->GetProperties().contains(PLAMotionType::Color))
  {
    //_color * _motionProperties.at(PLAMotionType::Color).GetColor();
  }
   */
  return color;
};

PLATransform PLAActor::GetTransform() const
{
  PLATransform transform = _transform;
  /*
  if (this->GetProperties().contains(PLAMotionType::Translation))
  {
    transform.translation +=
      this->GetProperties().at(PLAMotionType::Translation).GetVec3();
  }
  if (this->GetProperties().contains(PLAMotionType::Rotation))
  {
    transform.rotation +=
      this->GetProperties().at(PLAMotionType::Rotation).GetVec3();
  }
  if (this->GetProperties().contains(PLAMotionType::Scale))
  {
    PLAVec3 scale = this->GetProperties().at(PLAMotionType::Scale).GetVec3();
    transform.scale.x *= scale.x;
    transform.scale.y *= scale.y;
    transform.scale.z *= scale.z;
  }
   */
  return transform;
};

/*
void PLAActor::AddMotion(PLAMotionNode *aMotion)
{
  _motion.AddQueue(aMotion);
}
 */

/*
void PLAActor::AddMotion(PLAMotionType aType, const PLAProperty &aDistance,
               PLAFloat aDuration)
{

}

void PLAActor::AddMotionAlpha(PLAFloat aAlpha, PLAFloat aDuration)
{

}

void PLAActor::AddMotionColor(const PLAColor &aColor, PLAFloat aDuration)
{

}

void PLAActor::AddMotionTranslation(const PLAVec3 &aTranslation, PLAFloat aDuration)
{

}

void PLAActor::AddMotionRotation(const PLAVec3 &aRotation, PLAFloat aDuration)
{

}

void PLAActor::AddMotionScale(const PLAVec3 &aScale, PLAFloat aDuration)
{

}
 */

PLAActor *PLAActor::RefResponsiveActor(const PLAInputDeviceType aDeviceType,
                                       const PLAInputSignalCode aSignalCode)
{
  for (std::list<PLAActor *>::const_reverse_iterator it = _actors.rbegin();
       it != _actors.rend(); it++)
  {
    PLAActor *actor = (*it)->RefResponsiveActor(aDeviceType, aSignalCode);
    if (actor) { return actor; }
  }

  if (this->IsResponsive(aDeviceType, aSignalCode)) { return this; }

  return nullptr;
}

PLAActor *PLAActor::RefResponsiveActorWithPoint
  (const PLAPoint &aPoint,
   const PLAInputDeviceType aDeviceType,
   const PLAInputSignalCode aSignalCode)
{
  for (std::list<PLAActor *>::reverse_iterator it = _actors.rbegin();
       it != _actors.rend(); it++)
  {
    GRA_PRINT("aPoint : x %.2f : y %.2f\n", aPoint.x, aPoint.y);
    PLAPoint offset = PLAPoint((*it)->GetTransform().translation.x,
                               (*it)->GetTransform().translation.y);
    GRA_PRINT("offset : x %.2f : y %.2f\n", offset.x, offset.y);
    PLAActor *actor =
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

PLALYRPoint *PLAActor::RefLYRPoint()
{
  if (_layer->GetLayerType() != PLALayerType::Point) { return nullptr; }
  return static_cast<PLALYRPoint *>(_layer);
}

PLALYRLine *PLAActor::RefLYRLine()
{
  if (_layer->GetLayerType() != PLALayerType::Line) { return nullptr; }
  return static_cast<PLALYRLine *>(_layer);
}

PLALYRRect *PLAActor::RefLYRRect()
{
  if (_layer->GetLayerType() != PLALayerType::Rect) { return nullptr; }
  return static_cast<PLALYRRect *>(_layer);
}

PLALYRCircle *PLAActor::RefLYRCircle()
{
  if (_layer->GetLayerType() != PLALayerType::Circle) { return nullptr; }
  return static_cast<PLALYRCircle *>(_layer);
}

PLALYRTile *PLAActor::RefLYRTile()
{
  if (_layer->GetLayerType() != PLALayerType::Tile) { return nullptr; }
  return static_cast<PLALYRTile *>(_layer);
}

/*
const PLALYRRect *PLAActor::GetLayerRect() const
{
  if (this->GetLayerType() != PLALayerType::Circle)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Primitive does not match.");
  }
  return static_cast<PLALYRRect *>(_layer);
}

const PLALYRCircle *PLAActor::GetLayerCircle() const
{
  if (this->GetLayerType() != PLALayerType::Circle)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Primitive does not match.");
  }
  return static_cast<PLALYRCircle *>(_layer);
}
*/

/*
void PLAActor::UpdateMotions()
{
  GRA_PRINT("UpdateMotions()\n");
  _motion.Update();

  std::map<PLAMotionType, PLAProperty> properties =
    std::map<PLAMotionType, PLAProperty>();
  _motion.GetProperties(&properties);

  for (const auto &[key, value] : properties) {
    if (!_motionProperties.contains(key)) {
      _motionProperties[key] = PLAMotionNode::MakeProperty(key);
    }
    _motionProperties[key] = properties[key];
    GRA_PRINT("_motionProperties[%s]", PLAMotionNode::GetNameOfType(key));
    _motionProperties[key].Print();
  }
  for (PLAActor *actor : _actors) { actor->UpdateMotions(); }
}
 */

void PLAActor::AddTileMotion(const PLAVec2s &aAddress, PLAMotion *aThread)
{
  PLALYRTile *layer = this->RefLYRTile();
  if (!layer) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "LayerType is not Tile.");
  }
  layer->AddMotionThread(aAddress, aThread);
}

/*
void PLAActor::AddTileMotions(const PLAVec2s &aAddress,
                              const std::vector<PLAMotionNode *> &aMotions)
{
  PLALYRTile *layer = this->RefLYRTile();
  if (!layer) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "LayerType is not Tile.");
  }
  layer->AddMotions(aAddress, aMotions);
}
 */

/*
void PLAActor::SetTileMotion(const PLAVec2s &aAddress, PLAMotionNode *aMotion)
{
  PLALYRTile *layer = this->RefLYRTile();
  if (!layer) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "LayerType is not Tile.");
  }
  layer->SetMotion(aAddress, aMotion);
}
 */

void PLAActor::RefreshLayerOffset()
{
  PLAVec3 size(this->GetSize());
  _layer->SetOffset(-PLAVec3(size.x * _pivot.x,
                             size.y * _pivot.y,
                             size.z * _pivot.z));
}

void PLAActor::OnUpdate()
{
  _functor.RunFunction(PLAActorFunctionCode::OnUpdate, this);
  for (PLAActor *actor : _actors) { actor->OnUpdate(); }
}

/*
void PLAActor::OnUpdateMotions()
{
  //this->UpdateMotionProperties();
  //_layer->UpdateMotionProperties();
  for (PLAActor *actor : _actors) { actor->OnUpdateMotions(); }
}
 */

const char *PLAActor::GetBinderItemTypeName() const
{
  return this->GetActorTypeName();
}
