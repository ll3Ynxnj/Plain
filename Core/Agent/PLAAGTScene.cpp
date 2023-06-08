//
// Created by Kentaro Kawai on 2022/04/16.
//

#include "PLAAGTScene.hpp"
#include "PLAAGTPhase.hpp"
#include "Object/PLAOBJScene.hpp"

PLAAGTScene::PLAAGTScene(PLAOBJScene *aScene) :
  PLAAgent(aScene)
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
  PLAId phaseId = aAgent.GetOwnerId();
  PLAOBJPhase *phase = PLAOBJPhase::Object(phaseId);
  PLAId sceneId = this->GetOwnerId();
  PLAOBJScene *scene = PLAOBJScene::Object(sceneId);
  scene->PushPhase(phase);
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

void PLAAGTScene::RunFunction(PLAFunctionCode::Scene aKey) const
{
  auto owner = this->RefScene();
  owner->RunFunction(aKey);//this->RefStage());
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
