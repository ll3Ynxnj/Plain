#include "PLAOBJScene.hpp"
#include "Agent/PLAAGTScene.hpp"

PLAAGTScene PLAOBJScene::AssignAgent()
{
  return PLAAGTScene(this);
}

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
  PLAObject(PLAObjectType::Scene)
{
  _context = PLAOBJPhase::Create();
  _context->SetObjectName("SceneContext");
}

PLAOBJScene::~PLAOBJScene() {

}

void PLAOBJScene::Init()
{
  //_context->Init();
  //this->RunFunction(PLAFunctionCode::Scene::OnInit);
}

void PLAOBJScene::Update()
{
  //_context->Update();
  this->RunFunction(PLAFunctionCode::Scene::OnUpdate);
}

void PLAOBJScene::AddListener(GRAOBJListener<PLAAGTScene, PLAFunctionCode::Scene> *aListener)
{ _listeners.push_back(aListener); }

void PLAOBJScene::RemoveListener(GRAOBJListener<PLAAGTScene, PLAFunctionCode::Scene> *aListener)
{ _listeners.remove(aListener); }

void PLAOBJScene::SetFunction(PLAFunctionCode::Scene aKey,
                              const std::function<void(PLAAGTScene)> &aFunc)
{ _functor.SetFunction(aKey, aFunc); }

void PLAOBJScene::PushPhase(PLAOBJPhase *aPhase)
{
  _context->PushChild(aPhase);
}

void PLAOBJScene::PopPhase()
{
  _context->PopChild();
}

void PLAOBJScene::PrintPhases() const
{
  GRA_PRINT("//-- PLAOBJScene::PrintPhases() const --");
  GRA_PRINT("////////////////////////////////////////\n");
  _context->PrintPhases();
  GRA_PRINT("////////////////////////////////////////");
  GRA_PRINT("////////////////////////////////////////\n");
}

void PLAOBJScene::RunFunction(PLAFunctionCode::Scene aKey)
{
  _functor.RunFunction(aKey, this->AssignAgent());//this->RefStage());
  for (GRAOBJListener<PLAAGTScene, PLAFunctionCode::Scene> *listener: _listeners)
  { listener->RunListener(aKey, this->AssignAgent()); }//this->RefStage()); }
}
