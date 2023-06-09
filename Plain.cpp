//
// Created by Kentaro Kawai on 2022/04/15.
//

#include "Plain.h"
#include "Grain/Grain.h"

#include "Object/PLAObject.hpp"
#include "Object/PLAOBJApp.hpp"
#include "Object/PLAOBJError.hpp"
#include "Object/Layer/IPLATileLayerDataSource.hpp"

#include "Primitive/PLAPRMType.hpp"

void Plain::Init(PLARendererType aType)
{
  PLAOBJApp::Instance()->Init(aType);
}

void Plain::Delete(const std::string &aName) {
  //PLAOBJApp::Object(aName)->Unbind();
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
  PLAOBJApp::Instance()->PrintTimelineNodes();
}

void Plain::Push(const PLAAGTPhase &aPhase)
{
  auto scene = Plain::Scene::Assign();
  scene.PushPhase(aPhase);
}

PLAAGTScene Plain::Scene::Assign()
{
  PLAOBJScene *scene = PLAOBJApp::Scene();
  return scene->AssignAgent();
}

PLAAGTState Plain::State::Assign()
{
  PLAOBJState *state = PLAOBJApp::State();
  return state->AssignAgent();
}

PLAAGTStage Plain::Stage::Assign()
{
  PLAOBJStage *stage = PLAOBJApp::Stage();
  return stage->AssignAgent();
}

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

PLAAGTPhase Plain::Phase::Assign(const PLAString &aName)
{
  PLAOBJPhase *phase = PLAOBJPhase::Object(aName);
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

PLAAGTModel Plain::Model::Assign(const PLAString &aName)
{
  PLAOBJModel *model = PLAOBJModel::Object(aName);
  return model->AssignAgent();
}

PLAAGTActor Plain::Actor::CreateRect(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLARect &aRect)
{
  PLAOBJActor *actor = PLAOBJActor::CreateRect(aPivot, aColor, aTransform,
                                               aRect);
  return actor->AssignAgent();
}

PLAAGTActor Plain::Actor::CreateRect(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLARect &aRect,
                                     const PLAColor &aFillColor)
{
  PLAOBJActor *actor = PLAOBJActor::CreateRect(aPivot, aColor, aTransform,
                                               aRect, aFillColor);
  return actor->AssignAgent();
}

PLAAGTActor Plain::Actor::CreateRect(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLARect &aRect,
                                     const std::string &aImage,
                                     const PLARect &aClip)
{
  PLAOBJActor *actor = PLAOBJActor::CreateRect(aPivot, aColor, aTransform,
                                               aRect, aImage, aClip);
  return actor->AssignAgent();
}

PLAAGTActor Plain::Actor::CreateCircle(const PLAVec3f &aPivot,
                                       const PLAColor &aColor,
                                       const PLATransform &aTransform,
                                       const PLACircle &aCircle)
{
  PLAOBJActor *actor = PLAOBJActor::CreateCircle(aPivot, aColor, aTransform,
                                                 aCircle);
  return actor->AssignAgent();
}

PLAAGTActor Plain::Actor::CreateCircle(const PLAVec3f &aPivot,
                                       const PLAColor &aColor,
                                       const PLATransform &aTransform,
                                       const PLACircle &aCircle,
                                       const PLAColor &aFillColor)
{
  PLAOBJActor *actor = PLAOBJActor::CreateCircle(aPivot, aColor, aTransform,
                                                 aCircle, aFillColor);
  return actor->AssignAgent();
}

PLAAGTActor Plain::Actor::CreateCircle(const PLAVec3f &aPivot,
                                       const PLAColor &aColor,
                                       const PLATransform &aTransform,
                                       const PLACircle &aCircle,
                                       const std::string &aImage,
                                       const PLARect &aClip)
{
  PLAOBJActor *actor = PLAOBJActor::CreateCircle(aPivot, aColor, aTransform,
                                                 aCircle, aImage, aClip);
  return actor->AssignAgent();
}

PLAAGTActor Plain::Actor::CreateTile(const PLAVec2f &aOffset,
                                     const std::string &aImageName,
                                     const GRAVec2<PLASize> &aTileSize,
                                     const GRAVec2<PLASize> &aChipSize,
                                     const IPLATileLayerDataSource *aDataSource)
{
  PLAOBJActor *actor = PLAOBJActor::CreateTile(aOffset, aImageName, aTileSize,
                                               aChipSize, aDataSource);
  return actor->AssignAgent();
}

PLAAGTActor Plain::Actor::Assign(const PLAString &aName)
{
  PLAOBJActor *actor = PLAOBJActor::Object(aName);
  return actor->AssignAgent();
}
