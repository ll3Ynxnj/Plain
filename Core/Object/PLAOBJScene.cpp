#include "PLAOBJScene.hpp"
#include "PLAOBJApp.hpp"
#include "Actor/PLAOBJActor.hpp"
#include "Agent/PLAAGTScene.hpp"

PLAOBJScene *PLAOBJScene::Create()
{
  PLAOBJScene *scene = new PLAOBJScene();
  scene->PLAObject::Bind();
  return scene;
}

PLAOBJScene *PLAOBJScene::Object(const PLAString &aName)
{
  auto object = PLAObject::Object(PLAObjectType::Scene, aName);
  return static_cast<PLAOBJScene *>(object);
}

PLAOBJScene *PLAOBJScene::Object(PLAId aId)
{
  auto object = PLAObject::Object(PLAObjectType::Scene, aId);
  return static_cast<PLAOBJScene *>(object);
}

PLAOBJScene::PLAOBJScene() :
  PLAObject(PLAObjectType::Scene),
  GRAOBJBinder<PLAOBJActor>()
{

}

PLAOBJScene::~PLAOBJScene() {

}

void PLAOBJScene::Init() {
  _functor.RunFunction(PLAFunctionCode::Scene::OnInit, this);
  for (GRAOBJListener<PLAOBJScene *, PLAFunctionCode::Scene> *listener: _listeners)
  { listener->RunListener(PLAFunctionCode::Scene::OnInit, this); }
};

void PLAOBJScene::Update() {
  _functor.RunFunction(PLAFunctionCode::Scene::OnUpdate, this);
  for (GRAOBJListener<PLAOBJScene *, PLAFunctionCode::Scene> *listener: _listeners)
  { listener->RunListener(PLAFunctionCode::Scene::OnUpdate, this); }
};

void PLAOBJScene::Appear() {
  _functor.RunFunction(PLAFunctionCode::Scene::OnAppear, this);
  for (GRAOBJListener<PLAOBJScene *, PLAFunctionCode::Scene> *listener: _listeners)
  { listener->RunListener(PLAFunctionCode::Scene::OnAppear, this); }
};

void PLAOBJScene::Disappear() {
  _functor.RunFunction(PLAFunctionCode::Scene::OnDisappear, this);
  for (GRAOBJListener<PLAOBJScene *, PLAFunctionCode::Scene> *listener: _listeners)
  { listener->RunListener(PLAFunctionCode::Scene::OnDisappear, this); }
};

PLAAGTScene PLAOBJScene::AssignAgent()
{
  return PLAAGTScene(this);
}

void PLAOBJScene::AddActor(PLAOBJActor *aActor) {
  //PLAOBJActor::Bind(aActor);
  GRAOBJBinder<PLAOBJActor>::Error error(GRAOBJBinder<PLAOBJActor>::Error::None);
  this->GRAOBJBinder<PLAOBJActor>::Bind(aActor, &error);
  if (error != GRAOBJBinder<PLAOBJActor>::Error::None) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAObject binding. ERROR : %02d", error);
  }
}

void PLAOBJScene::RemoveActor(PLAOBJActor *aActor) {
  //PLAOBJActor::Unbind(aActor);
  GRAOBJBinder<PLAOBJActor>::Error error(GRAOBJBinder<PLAOBJActor>::Error::None);
  this->GRAOBJBinder<PLAOBJActor>::Unbind(aActor, &error);
}

const PLAOBJActor *PLAOBJScene::GetActor(const PLAString &aName) const {
  return this->RefActor(aName);
}

PLAOBJActor *PLAOBJScene::RefActor(const PLAString &aName) const {
  GRAOBJBinder<PLAOBJActor>::Error error(GRAOBJBinder<PLAOBJActor>::Error::None);
  PLAOBJScene *scene = PLAOBJScene::Manager::Instance()->RefCurrentScene();
  PLAOBJActor *actor = static_cast<PLAOBJActor *>(scene->RefItem(aName, &error));
  return actor;
}

/*
const PLAAGTScene *PLAOBJScene::AssignAgent()
{
  return static_cast<const PLAAGTScene *>(PLAObject::AssignAgent());
}
 */

// PLAOBJScene::Manager ///////////////////////////////////////////////////////////

PLAOBJScene::Manager PLAOBJScene::Manager::_instance = PLAOBJScene::Manager();

void PLAOBJScene::Manager::Init()
{
  //PLAOBJScene *scene = PLAOBJScene::Create();
  //_scenes.push(scene);
}

