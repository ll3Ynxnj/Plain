//
// Created by Kentaro Kawai on 2022/04/16.
//

#include "PLAOBJAgent.hpp"
#include "Object/PLAObject.hpp"
#include "Object/PLAOBJError.hpp"

#include "PLAAGTActor.hpp"
#include "PLAAGTStage.hpp"
#include "PLAAGTScene.hpp"

PLAOBJAgent *PLAOBJAgent::Create(PLAObject *aOwner)
{
  PLAOBJAgent *agent = nullptr;
  switch (aOwner->GetObjectType()) {
    case PLAObjectType::Actor :
      agent = PLAAGTActor::Create(static_cast<PLAOBJActor *>(aOwner));
      break;
    case PLAObjectType::Stage :
      agent = PLAAGTStage::Create(static_cast<PLAOBJStage *>(aOwner));
      break;
    case PLAObjectType::Scene :
      agent = PLAAGTScene::Create(static_cast<PLAOBJScene *>(aOwner));
      break;
    default:
      PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Unexpected object type detected.");
  }
  PLAString name = "Agent(" + PLAString(aOwner->GetObjectName() + ")");
  //agent->SetObjectName(name);
  return agent;
}

PLAOBJAgent::PLAOBJAgent(PLAObject *aObject) :
  PLAObject(PLAObjectType::Agent),
  _owner(aObject)
{

}

PLAOBJAgent::~PLAOBJAgent()
{

}

void PLAOBJAgent::Release() const
{
  _owner->ReleaseAgent();
  _owner->Unbind();
}
