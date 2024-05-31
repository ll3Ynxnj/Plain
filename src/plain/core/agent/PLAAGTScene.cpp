//
// Created by Kentaro Kawai on 2022/04/16.
//

#include "plain/core/agent/PLAAGTScene.hpp"
#include "plain/core/agent/PLAAGTPhase.hpp"
#include "plain/core/object/PLAOBJScene.hpp"

PLAAGTScene::PLAAGTScene(PLAOBJScene *aOwner) :
  PLAAgent(aOwner)
{

}

PLAAGTScene::~PLAAGTScene() noexcept
{

}

void PLAAGTScene::Init() const
{
  static_cast<PLAOBJScene *>(this->RefOwner())->Init();
}

void PLAAGTScene::PushPhase(const PLAAGTPhase &aAgent) const
{
  PLAId phaseId = aAgent.GetObjectId();
  PLAOBJPhase *phase = PLAOBJPhase::Object(phaseId);
  PLAId sceneId = this->GetObjectId();
  PLAOBJScene *scene = PLAOBJScene::Object(sceneId);
  scene->PushPhase(phase);
}

void PLAAGTScene::PopPhase() const
{
  PLAId sceneId = this->GetObjectId();
  PLAOBJScene *scene = PLAOBJScene::Object(sceneId);
  scene->PopPhase();
}

void PLAAGTScene::AddListener(GRAOBJListener<PLAAGTScene, PLAFunctionCode::Scene> *aListener) const
{
  auto owner = this->RefScene();
  owner->AddListener(aListener);
};

void PLAAGTScene::RemoveListener(GRAOBJListener<PLAAGTScene, PLAFunctionCode::Scene> *aListener) const
{
  auto owner = this->RefScene();
  owner->RemoveListener(aListener);
};

void PLAAGTScene::SetFunction(PLAFunctionCode::Scene aKey,
                              const std::function<void(PLAAGTScene)> &aFunc) const
{
  auto owner = this->RefScene();
  owner->SetFunction(aKey, aFunc);
};

void PLAAGTScene::PrintPhases() const
{
  const PLAOBJScene *scene = this->GetScene();
  scene->PrintPhases();
}

const PLAOBJScene *PLAAGTScene::GetScene() const
{
  return static_cast<const PLAOBJScene *>(this->GetOwner());
}

PLAOBJScene *PLAAGTScene::RefScene() const
{
  return static_cast<PLAOBJScene *>(this->RefOwner());
}

PLAAGTPhase PLAAGTScene::GetCurrentPhase() const
{
  PLAId sceneId = this->GetObjectId();
  PLAOBJScene *scene = PLAOBJScene::Object(sceneId);
  PLAOBJPhase *phase = scene->RefCurrentPhase();
  return phase->AssignAgent();
}
