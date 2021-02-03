//
// Created by Kentaro Kawai on 2021/01/28.
//

#include "PLAScene.hpp"

PLAScene *PLAScene::Create() {
  PLAScene *actor = new PLAScene();
  PLAObject::Manager::Ref()->Bind(actor);
  return actor;
}

PLAScene::PLAScene() :
PLAObject(PLAObjectType::Scene)
{

}

PLAScene::~PLAScene()
{

}

// PLAScene::Manager ///////////////////////////////////////////////////////////

PLAScene::Manager PLAScene::Manager::_instance = PLAScene::Manager();
