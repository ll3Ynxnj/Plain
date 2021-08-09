#include "PLAScene.hpp"
#include "PLAApp.hpp"
#include "Actor/PLAActor.hpp"

PLAScene *PLAScene::Create() {
  PLAScene *scene = new PLAScene();
  PLAObject::Bind(scene);
  return scene;
}

PLAScene::PLAScene() :
PLAObject(PLAObjectType::Scene),
PLAInputHandler(),
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

const PLAActor *PLAScene::GetActor(const std::string &aName) const {
  return this->RefActor(aName);
}

PLAActor *PLAScene::RefActor(const std::string &aName) const {
  GRABinder<PLAActor>::Error error(GRABinder<PLAActor>::Error::None);
  PLAScene *scene = PLAScene::Manager::Instance()->RefCurrentScene();
  PLAActor *actor = static_cast<PLAActor *>(scene->RefItem(aName, &error));
  return actor;
}

// PLAScene::Manager ///////////////////////////////////////////////////////////

PLAScene::Manager PLAScene::Manager::_instance = PLAScene::Manager();

void PLAScene::Manager::Init()
{
  PLAScene *scene = PLAScene::Create();
  _scenes.push(scene);
  PLAInputManager::GetInstance()->SetHandler(scene);
}

// PLAInputHandler /////////////////////////////////////////////////////////////

PLAInputContext *PLAScene::RefContextWithInput(const PLAInput &aInput) const
{
  PLAActor *actor = PLAApp::Stage()->RefActorWithPoint(aInput.GetScreenPoint());
  return static_cast<PLAInputContext *>(actor);
}
