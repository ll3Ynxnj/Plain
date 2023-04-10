//
// Created by Kentaro Kawai on 2022/04/16.
//

#include "PLAAGTScene.hpp"

PLAAGTScene *PLAAGTScene::Create(PLAOBJScene *aScene)
{
  auto agent = new PLAAGTScene(aScene);
  agent->PLAObject::Bind();
  return agent;
}

PLAAGTScene::PLAAGTScene(PLAOBJScene *aScene) :
  PLAOBJAgent(aScene)
{

}

PLAAGTScene::~PLAAGTScene() noexcept
{

}
