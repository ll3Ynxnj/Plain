//
// Created by Kentaro Kawai on 2021/01/28.
//

#include "PLAScene.hpp"

PLAScene *PLAScene::Create() {
  PLAScene *item = new PLAScene();
  GRABinder::Error error(GRABinder::Error::None);
  PLAObject::Manager::RefInstance()->Bind(item, &error);
  return item;
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
