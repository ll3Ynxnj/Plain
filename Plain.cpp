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
  //return PLAAGTScene::Create(scene);
}

void Plain::Scene::Push(const PLAAGTScene *aAgent)
{
  PLAId id = aAgent->GetObjectId();
  PLAScene *scene = static_cast<PLAScene *>(PLAObject::Object(id));
  PLAScene::Manager::Instance()->PushScene(scene);
}

const PLAObject *Plain::GetObject(const PLAAgent *aAgent)
{
  PLAId id = aAgent->GetObjectId();
  PLAObject *object = PLAObject::Object(id);
  return object;
}