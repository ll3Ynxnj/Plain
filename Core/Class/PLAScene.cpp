#include "PLAScene.hpp"
#include "PLAApp.hpp"
#include "Actor/PLAActor.hpp"
#include "Agent/PLAAGTScene.hpp"

PLAScene *PLAScene::Create()
{
  PLAScene *scene = new PLAScene();
  scene->PLAObject::Bind();
  return scene;
}

PLAScene *PLAScene::Scene(const PLAString &aName)
{
  return static_cast<PLAScene *>(PLAObject::Object(aName));
}

PLAScene *PLAScene::Scene(PLAId aId)
{
  return static_cast<PLAScene *>(PLAObject::Object(aId));
}

PLAScene::PLAScene() :
PLAObject(PLAObjectType::Scene),
GRABinder<PLAActor>()
{

}

PLAScene::~PLAScene() {

}

void PLAScene::Init() {
  _functor.RunFunction(FunctionCode::OnInit, this);
  for (GRAListener<PLAScene, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnInit, this); }
};

void PLAScene::Update() {
  _functor.RunFunction(FunctionCode::OnUpdate, this);
  for (GRAListener<PLAScene, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnUpdate, this); }
};

void PLAScene::Appear() {
  _functor.RunFunction(FunctionCode::OnAppear, this);
  for (GRAListener<PLAScene, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnAppear, this); }
};

void PLAScene::Disappear() {
  _functor.RunFunction(FunctionCode::OnDisappear, this);
  for (GRAListener<PLAScene, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnDisappear, this); }
};

void PLAScene::AddActor(PLAActor *aActor) {
  //PLAActor::Bind(aActor);
  GRABinder<PLAActor>::Error error(GRABinder<PLAActor>::Error::None);
  this->GRABinder<PLAActor>::Bind(aActor, &error);
  if (error != GRABinder<PLAActor>::Error::None) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAObject binding. ERROR : %02d", error);
  }
}

void PLAScene::RemoveActor(PLAActor *aActor) {
  //PLAActor::Unbind(aActor);
  GRABinder<PLAActor>::Error error(GRABinder<PLAActor>::Error::None);
  this->GRABinder<PLAActor>::Unbind(aActor, &error);
}

const PLAActor *PLAScene::GetActor(const PLAString &aName) const {
  return this->RefActor(aName);
}

PLAActor *PLAScene::RefActor(const PLAString &aName) const {
  GRABinder<PLAActor>::Error error(GRABinder<PLAActor>::Error::None);
  PLAScene *scene = PLAScene::Manager::Instance()->RefCurrentScene();
  PLAActor *actor = static_cast<PLAActor *>(scene->RefItem(aName, &error));
  return actor;
}

const PLAAGTScene *PLAScene::AssignAgent()
{
  return static_cast<const PLAAGTScene *>(PLAObject::AssignAgent());
}

// PLAScene::Manager ///////////////////////////////////////////////////////////

PLAScene::Manager PLAScene::Manager::_instance = PLAScene::Manager();

void PLAScene::Manager::Init()
{
  //PLAScene *scene = PLAScene::Create();
  //_scenes.push(scene);
}

