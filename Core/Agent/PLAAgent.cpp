//
// Created by Kentaro Kawai on 2022/04/16.
//

#include "PLAAgent.hpp"
#include "Core/Class/PLAObject.hpp"
#include "Core/Class/PLAError.hpp"

#include "PLAAGTScene.hpp"

PLAAgent *PLAAgent::Create(PLAObject *aOwner)
{
  PLAAgent *agent = nullptr;
  switch (aOwner->GetObjectType()) {
    case PLAObjectType::Scene :
      agent = PLAAGTScene::Create(static_cast<PLAScene *>(aOwner));
      break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "Unexpected object type detected.");
  }
  PLAString name = "Agent(" + PLAString(aOwner->GetObjectName() + ")");
  agent->SetObjectName(name);
  return agent;
}

PLAAgent::PLAAgent(PLAObject *aObject) :
  PLAObject(PLAObjectType::Agent),
  _owner(aObject)
{

}

PLAAgent::~PLAAgent()
{

}

void PLAAgent::Release() const
{
  _owner->ReleaseAgent(this);
  _owner->Unbind();
}
