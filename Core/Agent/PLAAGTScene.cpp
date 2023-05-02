//
// Created by Kentaro Kawai on 2022/04/16.
//

#include "PLAAGTScene.hpp"
#include "Object/PLAOBJScene.hpp"

PLAAGTScene::PLAAGTScene(PLAOBJScene *aScene) :
  PLAAgent(aScene)
{

}

PLAAGTScene::~PLAAGTScene() noexcept
{

}

const PLAOBJScene *PLAAGTScene::GetStage() const
{
  return static_cast<const PLAOBJScene *>(this->GetOwner());
}

PLAOBJScene *PLAAGTScene::RefStage() const
{
  return static_cast<PLAOBJScene *>(this->RefOwner());
}
