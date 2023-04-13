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

PLAOBJScene *PLAOBJScene::Scene(const PLAString &aName)
{
  return static_cast<PLAOBJScene *>(PLAObject::Object(aName));
}

PLAOBJScene *PLAOBJScene::Scene(PLAId aId)
{
  return static_cast<PLAOBJScene *>(PLAObject::Object(aId));
}

PLAOBJScene::PLAOBJScene() :
  PLAObject(PLAObjectType::Scene),
  GRAOBJBinder<PLAOBJActor>()
{

}

PLAOBJScene::~PLAOBJScene() {

}

void PLAOBJScene::Init() {
  _functor.RunFunction(FunctionCode::OnInit, this);
  for (GRAOBJListener<PLAOBJScene, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnInit, this); }
};

void PLAOBJScene::Update() {
  _functor.RunFunction(FunctionCode::OnUpdate, this);
  for (GRAOBJListener<PLAOBJScene, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnUpdate, this); }
};

void PLAOBJScene::Appear() {
  _functor.RunFunction(FunctionCode::OnAppear, this);
  for (GRAOBJListener<PLAOBJScene, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnAppear, this); }
};

void PLAOBJScene::Disappear() {
  _functor.RunFunction(FunctionCode::OnDisappear, this);
  for (GRAOBJListener<PLAOBJScene, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnDisappear, this); }
};

void PLAOBJScene::AddActor(PLAOBJActor *aActor) {
  //PLAOBJActor::Bind(aActor);
  GRAOBJBinder<PLAOBJActor>::Error error(GRAOBJBinder<PLAOBJActor>::Error::None);
  this->GRAOBJBinder<PLAOBJActor>::Bind(aActor, &error);
  if (error != GRAOBJBinder<PLAOBJActor>::Error::None) {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
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
