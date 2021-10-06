#include "PLAActor.hpp"
#include "Core/Input/PLAInput.hpp"
#include "PLAError.hpp"

#include "Layer/PLALYRPoint.hpp"
#include "Layer/PLALYRLine.hpp"
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
                               const GRAVec2<PLASize> &aTileSize,
                               const GRAVec2<PLASize> &aChipSize,
                               const IPLALYRTileDataSource *aDataSource)
{
  PLALYRTile *layer = PLALYRTile::Create(aOffset, aImageName, aTileSize, aChipSize,
                                         aDataSource);
  PLAActor *actor = new PLAActor(kPLAVec3None, kPLAColorWhite,
                                 kPLATransformNorm, layer);
  PLAObject::Bind(actor);
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
                   PLALayer *aLayer) :
  PLAObject(PLAObjectType::Actor),//"== PLAActor =="),
  GRABinder<PLAActor>::Item(),
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
  this->UpdateMotions();

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

void PLAActor::AddMotion(PLAMotion *aMotion)
{
  _motion.AddMain(aMotion);
}

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
  for (std::list<PLAActor *>::reverse_iterator it = _actors.rbegin();
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

void PLAActor::UpdateMotions()
{
  std::map<PLAMotionType, PLAProperty> properties =
    std::map<PLAMotionType, PLAProperty>();
  _motion.GetProperty(&properties);

  for (const auto &[key, value] : properties) {
    if (!_motionProperties.contains(key)) {
      _motionProperties[key] = PLAMotion::MakeProperty(key);
    }
    _motionProperties[key].Add(properties[key]); //ここから
  }
  /*
  for (const auto &[key, value] : _motionProperties) {
    _motionProperties[key]; //ここから
  }
   */
  for (PLAActor *actor : _actors) { actor->UpdateMotions(); }
}


void PLAActor::RefreshLayerOffset()
{
  PLAVec3 size(this->GetSize());
  _layer->SetOffset(-PLAVec3(size.x * _pivot.x,
                             size.y * _pivot.y,
                             size.z * _pivot.z));
}
