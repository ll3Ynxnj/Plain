//
// Created by Kentaro Kawai on 2022/04/15.
//

#include "Plain.h"

#include "Object/PLAOBJApp.hpp"
#include "Object/PLAOBJError.hpp"

void Plain::Init(PLARendererType aType)
{
  PLAOBJApp::Instance()->Init(aType);
}

void Plain::Delete(const std::string &aName) {
  PLAOBJApp::Object(aName)->Unbind();
}

PLAAGTState *Plain::State()
{
  static PLAAGTState *agent = nullptr;
  if (agent == nullptr) {
    PLAOBJState *state = PLAOBJApp::State();
    agent = static_cast<PLAAGTState *>(state->AssignAgent());
  }
  return agent;
}

PLAAGTStage *Plain::Stage()
{
  static PLAAGTStage *agent = nullptr;
  if (agent == nullptr) {
    PLAOBJStage *stage = PLAOBJApp::Stage();
    agent = static_cast<PLAAGTStage *>(stage->AssignAgent());
  }
  return agent;
}

/*
void Plain::Stage::AddListener(GRAOBJListener<PLAAGTStage, PLAAGTStage::FunctionCode> *aListener)
{

}

void Plain::Stage::RemoveListener(GRAOBJListener<PLAAGTStage, PLAAGTStage::FunctionCode> *aListener)
{

}

void Plain::Stage::SetFunction(PLAAGTStage::FunctionCode aKey,
                               const std::function<void(PLAAGTStage *)> &aFunc)
{

}
 */

PLAAGTScene *Plain::Scene::Create()
{
  PLAOBJScene *scene = PLAOBJScene::Create();
  return static_cast<PLAAGTScene *>(scene->AssignAgent());
}

PLAAGTScene *Plain::Scene::Create(const PLAString &aName)
{
  if (PLAObject::Object(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Duplicate object names."); }
  PLAOBJScene *scene = PLAOBJScene::Create();
  scene->SetObjectName(aName);
  return static_cast<PLAAGTScene *>(scene->AssignAgent());
}

PLAAGTScene *Plain::Scene::Assign(const PLAString &aName)
{
  PLAOBJAgent *agent = Plain::Assign(aName);
  const PLAObject *owner = PLAObject::Object(agent->GetOwnerId());
  if (owner->GetObjectType() != PLAObjectType::Scene)
  {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                    "Object type %s does not match return type %s",
                    owner->GetObjectTypeName(), "PLAAGTScene");
  }
  return static_cast<PLAAGTScene *>(agent);
}

void Plain::Scene::Push(const PLAAGTScene *aAgent)
{
  PLAId id = aAgent->GetOwnerId();
  PLAOBJScene *scene = static_cast<PLAOBJScene *>(PLAObject::Object(id));
  PLAOBJScene::Manager::Instance()->PushScene(scene);
}

PLAAGTModel *Plain::Model::Create()
{
  PLAOBJModel *model = PLAOBJModel::Create();
  return static_cast<PLAAGTModel *>(model->AssignAgent());
}

PLAAGTModel *Plain::Model::Create(const PLAString &aName)
{
  if (PLAObject::Object(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Duplicate object names."); }
  PLAOBJModel *model = PLAOBJModel::Create();
  model->SetObjectName(aName);
  return static_cast<PLAAGTModel *>(model->AssignAgent());
}

PLAAGTModel *Plain::Model::Assign(const PLAString &aName)
{
  PLAOBJAgent *agent = Plain::Assign(aName);
  const PLAObject *owner = PLAObject::Object(agent->GetOwnerId());
  if (owner->GetObjectType() != PLAObjectType::Model)
  {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                    "Object type %s does not match return type %s",
                    owner->GetObjectTypeName(), "PLAAGTModel");
  }
  return static_cast<PLAAGTModel *>(agent);
}

PLAAGTActor *Plain::Actor::CreateRect(const PLAVec3f &aPivot,
                                      const PLAColor &aColor,
                                      const PLATransform &aTransform,
                                      const PLARect &aRect)
{
  PLAOBJActor *actor = PLAOBJActor::CreateRect(aPivot, aColor, aTransform, aRect);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::CreateRect(const PLAVec3f &aPivot,
                                      const PLAColor &aColor,
                                      const PLATransform &aTransform,
                                      const PLARect &aRect,
                                      const PLAColor &aFillColor)
{
  PLAOBJActor *actor = PLAOBJActor::CreateRect(aPivot, aColor, aTransform, aRect,
                                               aFillColor);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::CreateRect(const PLAVec3f &aPivot,
                                      const PLAColor &aColor,
                                      const PLATransform &aTransform,
                                      const PLARect &aRect,
                                      const std::string &aImage,
                                      const PLARect &aClip)
{
  PLAOBJActor *actor = PLAOBJActor::CreateRect(aPivot, aColor, aTransform, aRect,
                                               aImage, aClip);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::CreateCircle(const PLAVec3f &aPivot,
                                        const PLAColor &aColor,
                                        const PLATransform &aTransform,
                                        const PLACircle &aCircle)
{
  PLAOBJActor *actor = PLAOBJActor::CreateCircle(aPivot, aColor, aTransform, aCircle);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::CreateCircle(const PLAVec3f &aPivot,
                                        const PLAColor &aColor,
                                        const PLATransform &aTransform,
                                        const PLACircle &aCircle,
                                        const PLAColor &aFillColor)
{
  PLAOBJActor *actor = PLAOBJActor::CreateCircle(aPivot, aColor, aTransform, aCircle,
                                                 aFillColor);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::CreateCircle(const PLAVec3f &aPivot,
                                        const PLAColor &aColor,
                                        const PLATransform &aTransform,
                                        const PLACircle &aCircle,
                                        const std::string &aImage,
                                        const PLARect &aClip)
{
  PLAOBJActor *actor = PLAOBJActor::CreateCircle(aPivot, aColor, aTransform, aCircle,
                                                 aImage, aClip);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::CreateTile(const PLAVec2f &aOffset,
                                      const std::string &aImageName,
                                      const GRAVec2<PLASize> &aTileSize,
                                      const GRAVec2<PLASize> &aChipSize,
                                      const IPLATileLayerDataSource *aDataSource)
{
  PLAOBJActor *actor = PLAOBJActor::CreateTile(aOffset, aImageName, aTileSize,
                                               aChipSize, aDataSource);
  return static_cast<PLAAGTActor *>(actor->AssignAgent());
}

PLAAGTActor *Plain::Actor::Assign(const PLAString &aName)
{
  PLAOBJAgent *agent = Plain::Assign(aName);
  const PLAObject *owner = PLAObject::Object(agent->GetOwnerId());
  if (owner->GetObjectType() != PLAObjectType::Actor)
  {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                    "Object type %s does not match return type %s",
                    owner->GetObjectTypeName(), "PLAAGTActor");
  }
  return static_cast<PLAAGTActor *>(agent);
}

const PLAObject *Plain::Object(const PLAOBJAgent *aAgent)
{
  PLAId id = aAgent->GetOwnerId();
  PLAObject *object = PLAObject::Object(id);
  return object;
}

PLAOBJAgent *Plain::Assign(const PLAString &aName)
{
  PLAObject *object = PLAObject::Object(aName);
  if (!object)
  {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                    "Object named %s, does not exist", aName.c_str());
  }
  return object->AssignAgent();
}
