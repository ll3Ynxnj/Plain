//
// Created by Kentaro Kawai on 2022/04/16.
//

#include "PLAAgent.hpp"
#include "Core/Class/PLAObject.hpp"
#include "Core/Class/PLAError.hpp"

#include "PLAAGTScene.hpp"

const PLAAgent *PLAAgent::Create(PLAObject *aObject)
{
  PLAObjectType type = aObject->GetObjectType();
  switch (type) {
    case PLAObjectType::Scene :
      return PLAAGTScene::Create(static_cast<PLAScene *>(aObject));
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "Unexpected object type detected.");
  }
}

PLAAgent::PLAAgent(PLAObject *aObject) :
  PLAObject(PLAObjectType::Agent),
  _object(aObject)
{

}

PLAAgent::~PLAAgent()
{

}

