//
// Created by Kentaro Kawai on 2022/04/15.
//

#include "Plain.h"
#include "Grain/Grain.h"

#include "Object/PLAObject.hpp"
#include "Object/PLAOBJError.hpp"

void Plain::Init(PLARendererType aType, PLAUInt aRefreshRate,
                 PLAUInt aBaseScreenLength)
{
  PLAApp::Instance()->Init(aType, aRefreshRate, aBaseScreenLength);
}

/*
void Plain::Delete(const std::string &aName)
{
  //PLAApp::Object(aName)->Unbind();
}
 */

PLAApp *Plain::App()
{
  return PLAApp::Instance();
}

void Plain::Print::Objects()
{
  PLAObject::Manager::Instance()->PrintObjects();
}

void Plain::Print::Resources()
{
  PLAOBJResource::Manager::Instance()->PrintResources();
}

void Plain::Print::Phases() {
  Plain::Scene::Assign().PrintPhases();
}

void Plain::Print::Actors() {
  Plain::Stage::Assign().PrintActors();
}

void Plain::Print::Models() {
  Plain::State::Assign().PrintModels();
}

void Plain::Print::TimelineNodes() {
  PLAApp::Instance()->PrintTimelineNodes();
}

PLAAGTScene Plain::Scene::Assign()
{
  PLAOBJScene *scene = PLAApp::Scene();
  return scene->AssignAgent();
}

void Plain::Scene::PushPhase(const PLAAGTPhase &aPhase)
{
  auto scene = Plain::Scene::Assign();
  scene.PushPhase(aPhase);
}

void Plain::Scene::PopPhase()
{
  auto scene = Plain::Scene::Assign();
  scene.PopPhase();
}

PLAAGTState Plain::State::Assign()
{
  PLAOBJState *state = PLAApp::State();
  return state->AssignAgent();
}

void Plain::State::AddModel(const PLAAGTModel &aModel)
{
  auto state = Plain::State::Assign();
  state.AddModel(aModel);
}

PLAAGTStage Plain::Stage::Assign()
{
  PLAOBJStage *stage = PLAApp::Stage();
  return stage->AssignAgent();
}

void Plain::Stage::AddActor(const PLAAGTActor &aActor)
{
  auto stage = Plain::Stage::Assign();
  stage.AddActor(aActor);
}

void Plain::Stage::AddActor(const PLAString &aName)
{
  auto stage = Plain::Stage::Assign();
  auto actor = Plain::Actor::Assign(aName);
  stage.AddActor(actor);
}

void Plain::Stage::RemoveActor(const PLAAGTActor &aActor)
{
  auto stage = Plain::Stage::Assign();
  stage.RemoveActor(aActor);
}

void Plain::Stage::RemoveActor(const PLAString &aName)
{
  auto stage = Plain::Stage::Assign();
  auto actor = Plain::Actor::Assign(aName);
  stage.RemoveActor(actor);
}

PLAVec3f Plain::Stage::GetSize()
{
  auto stage = Plain::Stage::Assign();
  return stage.GetSize();
}

/*
PLAAGTPhase Plain::Phase::Create()
{
  PLAOBJPhase *phase = PLAOBJPhase::Create();
  return phase->AssignAgent();
}

PLAAGTPhase Plain::Phase::Create(const PLAString &aName)
{
  if (PLAObject::Object(PLAObjectType::Phase, aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Duplicate object names."); }
  PLAOBJPhase *phase = PLAOBJPhase::Create();
  phase->SetObjectName(aName);
  return phase->AssignAgent();
}
 */

PLAAGTPhase Plain::Phase::CreateWithTag(PLAId aTag)
{
  if (PLAOBJPhase::Manager::Instance()->IsExistItemWithTag(aTag))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Duplicate object tags."); }
  PLAOBJPhase *phase = PLAOBJPhase::CreateWithTag(aTag);
  return phase->AssignAgent();
}

PLAAGTPhase Plain::Phase::Assign(const PLAId aId)
{
  PLAOBJPhase *phase = PLAOBJPhase::Object(aId);
  return phase->AssignAgent();
}

PLAAGTPhase Plain::Phase::Assign(const PLAString &aName)
{
  PLAOBJPhase *phase = PLAOBJPhase::Object(aName);
  return phase->AssignAgent();
}

PLAAGTPhase Plain::Phase::AssignWithTag(PLAId aTag)
{
  PLAOBJPhase *phase = PLAOBJPhase::ObjectWithTag(aTag);
  return phase->AssignAgent();
}

PLAAGTModel Plain::Model::Create()
{
  PLAOBJModel *model = PLAOBJModel::Create();
  return model->AssignAgent();
}

PLAAGTModel Plain::Model::Create(const PLAString &aName)
{
  if (PLAObject::Object(PLAObjectType::Model, aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Duplicate object names."); }
  PLAOBJModel *model = PLAOBJModel::Create();
  model->SetObjectName(aName);
  return model->AssignAgent();
}

PLAAGTModel Plain::Model::Assign(const PLAId aId)
{
  PLAOBJModel *model = PLAOBJModel::Object(aId);
  return model->AssignAgent();
}

PLAAGTModel Plain::Model::Assign(const PLAString &aName)
{
  PLAOBJModel *model = PLAOBJModel::Object(aName);
  return model->AssignAgent();
}

PLAAGTActorForRect Plain::Actor::CreateRect(const PLAVec2f &aOrigin,
                                            const PLAVec2f &aSize,
                                            const PLAColor &aFillColor)
{
  PLAOBJActor *actor = PLAOBJActor::CreateRect(aOrigin, aSize, aFillColor);
  return actor->AssignAgentForRect();
}

PLAAGTActorForRect Plain::Actor::CreateRect(const PLAVec3f &aPivot,
                                            const PLATransform &aTransform,
                                            const PLARect &aRect)
{
  PLAOBJActor *actor = PLAOBJActor::CreateRect(aPivot, kPLAColorNone, aTransform,
                                               aRect);
  return actor->AssignAgentForRect();
}

PLAAGTActorForRect Plain::Actor::CreateRect(const PLAVec3f &aPivot,
                                            const PLATransform &aTransform,
                                            const PLARect &aRect,
                                            const PLAColor &aFillColor)
{
  PLAOBJActor *actor = PLAOBJActor::CreateRect(aPivot, kPLAColorWhite, aTransform,
                                               aRect, aFillColor);
  return actor->AssignAgentForRect();
}

PLAAGTActorForRect Plain::Actor::CreateRect(const PLAVec3f &aPivot,
                                            const PLATransform &aTransform,
                                            const PLARect &aRect,
                                            const std::string &aImage,
                                            const PLARect &aClip)
{
  PLAOBJActor *actor = PLAOBJActor::CreateRect(aPivot, kPLAColorWhite, aTransform,
                                               aRect, aImage, aClip);
  return actor->AssignAgentForRect();
}

PLAAGTActorForCircle Plain::Actor::CreateCircle(const PLAVec2f &aOrigin,
                                                const PLAFloat aRadius,
                                                const PLAColor &aFillColor)
{
  PLAOBJActor *actor = PLAOBJActor::CreateCircle(aOrigin, aRadius, aFillColor);
  return actor->AssignAgentForCircle();
}

PLAAGTActorForCircle Plain::Actor::CreateCircle(const PLAVec3f &aPivot,
                                                const PLATransform &aTransform,
                                                const PLACircle &aCircle)
{
  PLAOBJActor *actor = PLAOBJActor::CreateCircle(aPivot, kPLAColorWhite, aTransform,
                                                 aCircle);
  return actor->AssignAgentForCircle();
}

PLAAGTActorForCircle Plain::Actor::CreateCircle(const PLAVec3f &aPivot,
                                                const PLATransform &aTransform,
                                                const PLACircle &aCircle,
                                                const PLAColor &aFillColor)
{
  PLAOBJActor *actor = PLAOBJActor::CreateCircle(aPivot, kPLAColorWhite, aTransform,
                                                 aCircle, aFillColor);
  return actor->AssignAgentForCircle();
}

PLAAGTActorForCircle Plain::Actor::CreateCircle(const PLAVec3f &aPivot,
                                                const PLATransform &aTransform,
                                                const PLACircle &aCircle,
                                                const std::string &aImage,
                                                const PLARect &aClip)
{
  PLAOBJActor *actor = PLAOBJActor::CreateCircle(aPivot, kPLAColorWhite, aTransform,
                                                 aCircle, aImage, aClip);
  return actor->AssignAgentForCircle();
}

PLAAGTActorForTile Plain::Actor::CreateTile(const PLAVec2f &aOffset,
                                            const std::string &aImageName,
                                            const GRAVec2<PLASize> &aTileSize,
                                            const GRAVec2<PLASize> &aChipSize,
                                            const IPLATileLayerDataSource *aDataSource)
{
  PLAOBJActor *actor = PLAOBJActor::CreateTile(aOffset, aImageName, aTileSize,
                                               aChipSize, aDataSource);
  return actor->AssignAgentForTile();
}

PLAAGTActor Plain::Actor::Assign(PLAId aId)
{
  PLAOBJActor *actor = PLAOBJActor::Object(aId);
  return actor->AssignAgent();
}

PLAAGTActor Plain::Actor::Assign(const PLAString &aName)
{
  PLAOBJActor *actor = PLAOBJActor::Object(aName);
  return actor->AssignAgent();
}

PLAAGTActor Plain::Actor::AssignWithTag(PLAId aTag)
{
  PLAOBJActor *actor = PLAOBJActor::ObjectWithTag(aTag);
  return actor->AssignAgent();
}

PLAAGTActorForRect Plain::Actor::AssignRect(PLAId aId)
{
  PLAOBJActor *actor = PLAOBJActor::Object(aId);
  return actor->AssignAgentForRect();
}

PLAAGTActorForRect Plain::Actor::AssignRect(const PLAString &aName)
{
  PLAOBJActor *actor = PLAOBJActor::Object(aName);
  return actor->AssignAgentForRect();
}

PLAAGTActorForRect Plain::Actor::AssignRectWithTag(PLAId aTag)
{
  PLAOBJActor *actor = PLAOBJActor::ObjectWithTag(aTag);
  return actor->AssignAgentForRect();
}

PLAAGTActorForCircle Plain::Actor::AssignCircle(PLAId aId)
{
  PLAOBJActor *actor = PLAOBJActor::Object(aId);
  return actor->AssignAgentForCircle();
}

PLAAGTActorForCircle Plain::Actor::AssignCircle(const PLAString &aName)
{
  PLAOBJActor *actor = PLAOBJActor::Object(aName);
  return actor->AssignAgentForCircle();
}

PLAAGTActorForCircle Plain::Actor::AssignCircleWithTag(PLAId aTag)
{
  PLAOBJActor *actor = PLAOBJActor::ObjectWithTag(aTag);
  return actor->AssignAgentForCircle();
}

PLAAGTActorForTile Plain::Actor::AssignTile(PLAId aId)
{
  PLAOBJActor *actor = PLAOBJActor::Object(aId);
  return actor->AssignAgentForTile();
}

PLAAGTActorForTile Plain::Actor::AssignTile(const PLAString &aName)
{
  PLAOBJActor *actor = PLAOBJActor::Object(aName);
  return actor->AssignAgentForTile();
}

PLAAGTActorForTile Plain::Actor::AssignTileWithTag(PLAId aTag)
{
  PLAOBJActor *actor = PLAOBJActor::ObjectWithTag(aTag);
  return actor->AssignAgentForTile();
}

/*
PLAAGTTimeline Plain::Timeline::Create(const PLAAGTTimeline &aParent)
{
  PLAId ownerId = aParent.GetObjectId();
  PLAOBJTimeline *parent = PLAOBJTimeline::Object(ownerId);
  PLAOBJTimeline *motion = PLAOBJTimeline::Create(parent);
  return motion->AssignAgent();
}

PLAAGTTimeline Plain::Timeline::Create(const PLAString &aName)
{
  if (PLAObject::Object(PLAObjectType::Timeline, aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Duplicate object names."); }
  PLAOBJTimeline *motion = PLAOBJTimeline::Create();
  motion->SetObjectName(aName);
  return motion->AssignAgent();
}

PLAAGTTimeline Plain::Timeline::Assign(const PLAString &aName)
{
  PLAOBJTimeline *motion = PLAOBJTimeline::Object(aName);
  return motion->AssignAgent();
}

PLAAGTTimelineNode Plain::TimelineNode::Create()
{
  auto object = PLAOBJTimelineNode::Create();
  return object->AssignAgent();
}

PLAAGTTimelineNode Plain::TimelineNode::Create(const PLAString &aName)
{
  if (PLAObject::Object(PLAObjectType::Model, aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Duplicate object names."); }
  PLAOBJTimelineNode *timelineNode = PLAOBJTimelineNode::Create();
  timelineNode->SetObjectName(aName);
  return timelineNode->AssignAgent();
}

PLAAGTTimelineNode Plain::TimelineNode::Assign(const PLAString &aName)
{
  PLAOBJTimelineNode *timelineNode = PLAOBJTimelineNode::Object(aName);
  return timelineNode->AssignAgent();
}
 */

PLAAGTMotion Plain::Motion::Create()
{
  PLATMLMotion *motion = PLATMLMotion::Create();
  return motion->AssignAgent();
}

PLAAGTMotion Plain::Motion::Create(const PLAString &aName)
{
  if (PLAObject::Object(PLAObjectType::Motion, aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Duplicate object names."); }
  PLATMLMotion *motion = PLATMLMotion::Create();
  motion->SetObjectName(aName);
  return motion->AssignAgent();
}

PLAAGTMotion Plain::Motion::Assign(PLAId aId)
{
  PLATMLMotion *motion = PLATMLMotion::Object(aId);
  return motion->AssignAgent();
}

PLAAGTMotion Plain::Motion::Assign(const PLAString &aName)
{
  PLATMLMotion *motion = PLATMLMotion::Object(aName);
  return motion->AssignAgent();
}

PLAAGTMotionNode Plain::MotionNode::Create()
{
  auto object = PLATMLMotionNode::Create();
  return object->AssignAgent();
}

PLAAGTMotionNode Plain::MotionNode::CreateColor(const PLAColor &aBegin,
                                                const PLAColor &aEnd,
                                                PLAEasing::Type aEasingType,
                                                PLATimeInterval aDuration)
{
  auto object = PLATMLMotionNode::CreateColor(aBegin, aEnd,
                                              aEasingType, aDuration);
  return object->AssignAgent();
}

PLAAGTMotionNode Plain::MotionNode::CreateTranslation(const PLAVec3f &aBegin,
                                                      const PLAVec3f &aEnd,
                                                      PLAEasing::Type aEasingType,
                                                      PLATimeInterval aDuration)
{
  auto object = PLATMLMotionNode::CreateTranslation(aBegin, aEnd,
                                                    aEasingType, aDuration);
  return object->AssignAgent();
}

PLAAGTMotionNode Plain::MotionNode::CreateRotation(const PLAVec3f &aBegin,
                                                   const PLAVec3f &aEnd,
                                                   PLAEasing::Type aEasingType,
                                                   PLATimeInterval aDuration)
{
  auto object = PLATMLMotionNode::CreateRotation(aBegin, aEnd,
                                                 aEasingType, aDuration);
  return object->AssignAgent();
}

PLAAGTMotionNode Plain::MotionNode::CreateScale(const PLAVec3f &aBegin,
                                                const PLAVec3f &aEnd,
                                                PLAEasing::Type aEasingType,
                                                PLATimeInterval aDuration)
{
  auto object = PLATMLMotionNode::CreateScale(aBegin, aEnd,
                                              aEasingType, aDuration);
  return object->AssignAgent();
}

/*
PLAAGTImageClip Plain::ImageClip::Create(const PLAString &aImageName)
{
  auto object = PLAOBJImageClip::Create(aImageName);
  return object->AssignAgent();
}
 */

PLAAGTImageClip Plain::ImageClip::Create(const std::string &aImageName,
                                         const PLARect &aClip)
{
  auto object = PLAOBJImageClip::Create(aImageName, aClip);
  return object->AssignAgent();
}

PLAAGTImageClip Plain::ImageClip::Assign(const PLAId &aId)
{
  auto object = PLAOBJImageClip::Object(aId);
  return object->AssignAgent();
}

PLAAGTImageClip Assign(const std::string &aName)
{
  auto object = PLAOBJImageClip::Object(aName);
  return object->AssignAgent();
}
