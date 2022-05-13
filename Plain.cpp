//
// Created by Kentaro Kawai on 2022/04/15.
//

#include "Plain.h"

#include "Class/PLAApp.hpp"
#include "Class/PLAError.hpp"

void Plain::Init(PLARendererType aType)
{
  PLAApp::Instance()->Init(aType);
}

void Plain::Delete(const std::string &aName) {
  PLAApp::Object(aName)->Unbind();
}

PLAAGTStage *Plain::Stage()
{
  static PLAAGTStage *agent = nullptr;
  if (agent == nullptr) {
    PLAStage *stage = PLAApp::Stage();
    agent = static_cast<PLAAGTStage *>(stage->AssignAgent());
  }
  return agent;
}

/*
void Plain::Stage::AddListener(GRAListener<PLAAGTStage, PLAAGTStage::FunctionCode> *aListener)
{

}

void Plain::Stage::RemoveListener(GRAListener<PLAAGTStage, PLAAGTStage::FunctionCode> *aListener)
{

}

void Plain::Stage::SetFunction(PLAAGTStage::FunctionCode aKey,
                               const std::function<void(PLAAGTStage *)> &aFunc)
{

}
 */

PLAAGTScene *Plain::Scene::Create()
{
  PLAScene *scene = PLAScene::Create();
  return static_cast<PLAAGTScene *>(scene->AssignAgent());
}

PLAAGTScene *Plain::Scene::Create(const PLAString &aName)
{
  if (PLAObject::Object(aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Duplicate object names."); }
  PLAScene *scene = PLAScene::Create();
  scene->SetObjectName(aName);
  return static_cast<PLAAGTScene *>(scene->AssignAgent());
}

PLAAGTScene *Plain::Scene::Assign(const PLAString &aName)
{
  PLAAgent *agent = Plain::Assign(aName);
  const PLAObject *owner = PLAObject::Object(agent->GetOwnerId());
  if (owner->GetObjectType() != PLAObjectType::Scene)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Object type %s does not match return type %s",
                    owner->GetObjectTypeName(), "PLAAGTScene");
  }
  return static_cast<PLAAGTScene *>(agent);
}

void Plain::Scene::Push(const PLAAGTScene *aAgent)
{
  PLAId id = aAgent->GetOwnerId();
  PLAScene *scene = static_cast<PLAScene *>(PLAObject::Object(id));
  PLAScene::Manager::Instance()->PushScene(scene);
}

PLAAGTActor *Plain::Actor::CreateRect(const PLAVec3 &aPivot,
                                      const PLAColor &aColor,
                                      const PLATransform &aTransform,
                                      const PLARect &aRect)
{
  PLAActor *actor = PLAActor::CreateRect(aPivot, aColor, aTransform, aRect);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::CreateRect(const PLAVec3 &aPivot,
                                      const PLAColor &aColor,
                                      const PLATransform &aTransform,
                                      const PLARect &aRect,
                                      const PLAColor &aFillColor)
{
  PLAActor *actor = PLAActor::CreateRect(aPivot, aColor, aTransform, aRect,
                                         aFillColor);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::CreateRect(const PLAVec3 &aPivot,
                                      const PLAColor &aColor,
                                      const PLATransform &aTransform,
                                      const PLARect &aRect,
                                      const std::string &aImage,
                                      const PLARect &aClip)
{
  PLAActor *actor = PLAActor::CreateRect(aPivot, aColor, aTransform, aRect,
                                         aImage, aClip);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::CreateCircle(const PLAVec3 &aPivot,
                                        const PLAColor &aColor,
                                        const PLATransform &aTransform,
                                        const PLACircle &aCircle)
{
  PLAActor *actor = PLAActor::CreateCircle(aPivot, aColor, aTransform, aCircle);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::CreateCircle(const PLAVec3 &aPivot,
                                        const PLAColor &aColor,
                                        const PLATransform &aTransform,
                                        const PLACircle &aCircle,
                                        const PLAColor &aFillColor)
{
  PLAActor *actor = PLAActor::CreateCircle(aPivot, aColor, aTransform, aCircle,
                                           aFillColor);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::CreateCircle(const PLAVec3 &aPivot,
                                        const PLAColor &aColor,
                                        const PLATransform &aTransform,
                                        const PLACircle &aCircle,
                                        const std::string &aImage,
                                        const PLARect &aClip)
{
  PLAActor *actor = PLAActor::CreateCircle(aPivot, aColor, aTransform, aCircle,
                                           aImage, aClip);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::CreateTile(const PLAVec2 &aOffset,
                                      const std::string &aImageName,
                                      const GRAVec2<PLASize> &aTileSize,
                                      const GRAVec2<PLASize> &aChipSize,
                                      const IPLALYRTileDataSource *aDataSource)
{
  PLAActor *actor = PLAActor::CreateTile(aOffset, aImageName, aTileSize,
                                         aChipSize, aDataSource);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::Assign(const PLAString &aName)
{
  PLAAgent *agent = Plain::Assign(aName);
  const PLAObject *owner = PLAObject::Object(agent->GetOwnerId());
  if (owner->GetObjectType() != PLAObjectType::Actor)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Object type %s does not match return type %s",
                    owner->GetObjectTypeName(), "PLAAGTActor");
  }
  return static_cast<PLAAGTActor *>(agent);
}

const PLAObject *Plain::Object(const PLAAgent *aAgent)
{
  PLAId id = aAgent->GetOwnerId();
  PLAObject *object = PLAObject::Object(id);
  return object;
}

PLAAgent *Plain::Assign(const PLAString &aName)
{
  PLAObject *object = PLAObject::Object(aName);
  if (!object)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Object named %s, does not exist", aName.c_str());
  }
  return object->AssignAgent();
}
