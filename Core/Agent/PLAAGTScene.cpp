//
// Created by Kentaro Kawai on 2022/04/16.
//

#include "PLAAGTScene.hpp"

PLAAGTScene *PLAAGTScene::Create(PLAScene *aScene)
{
  auto agent = new PLAAGTScene(aScene);
  agent->PLAObject::Bind();
  return agent;
}

PLAAGTScene::PLAAGTScene(PLAScene *aScene) :
  PLAAgent(aScene)
{

}

PLAAGTScene::~PLAAGTScene() noexcept
{

}

