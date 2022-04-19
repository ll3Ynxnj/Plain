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

const PLAAGTScene *Plain::Scene::Create()
{
  PLAScene *scene = PLAScene::Create();
  return scene->AssignAgent();
}

const PLAAGTScene *Plain::Scene::Create(const PLAString &aName)
{
  if (PLAObject::Object(aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Duplicate object names."); }
  PLAScene *scene = PLAScene::Create();
  scene->SetObjectName(aName);
  return scene->AssignAgent();
}

const PLAAGTScene *Plain::Scene::Assign(const PLAString &aName)
{
  const PLAAgent *agent = Plain::Assign(aName);
  const PLAObject *owner = agent->GetOwner();
  if (owner->GetObjectType() != PLAObjectType::Scene)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Object type %s does not match return type %s",
                    owner->GetObjectTypeName(), "PLAAGTScene");
  }
  return static_cast<const PLAAGTScene *>(agent);
}

void Plain::Scene::Push(const PLAAGTScene *aAgent)
{
  PLAId id = aAgent->GetOwnerId();
  PLAScene *scene = static_cast<PLAScene *>(PLAObject::Object(id));
  PLAScene::Manager::Instance()->PushScene(scene);
}

const PLAObject *Plain::Object(const PLAAgent *aAgent)
{
  PLAId id = aAgent->GetOwnerId();
  PLAObject *object = PLAObject::Object(id);
  return object;
}

const PLAAgent *Plain::Assign(const PLAString &aName)
{
  PLAObject *object = PLAObject::Object(aName);
  if (!object)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Object named %s, does not exist", aName.c_str());
  }
  return object->AssignAgent();
}