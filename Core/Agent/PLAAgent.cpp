//
// Created by Kentaro Kawai on 2023/04/13.
//

#include "PLAAgent.hpp"

//
// Created by Kentaro Kawai on 2022/04/16.
//

#include "PLAAgent.hpp"
//#include "Object/PLAObject.hpp"
//#include "Object/PLAOBJError.hpp"

#include "PLAAGTModel.hpp"
#include "PLAAGTActor.hpp"
#include "PLAAGTState.hpp"
#include "PLAAGTStage.hpp"
#include "PLAAGTScene.hpp"

/*
PLAAgent *PLAAgent::Create(PLAObject *aOwner)
{
  PLAAgent *agent = nullptr;
  switch (aOwner->GetObjectType()) {
    case PLAObjectType::Model :
      agent = PLAAGTModel::Create(static_cast<PLAOBJModel *>(aOwner));
      break;
    case PLAObjectType::Actor :
      agent = PLAAGTActor::Create(static_cast<PLAOBJActor *>(aOwner));
      break;
    case PLAObjectType::State :
      agent = PLAAGTState::Create(static_cast<PLAOBJState *>(aOwner));
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
  //PLAString name = "Agent(" + PLAString(aOwner->GetObjectName() + ")");
  //agent->SetObjectName(name);
  return agent;
}
 */

PLAAgent::PLAAgent() noexcept {

}

PLAAgent::PLAAgent(PLAObject *aObject) :
  //PLAObject(PLAObjectType::Agent),
  _owner(aObject)
{
  _owner->RetainAgent();
}

PLAAgent::PLAAgent(const PLAAgent &aAgent) noexcept {
  _owner = aAgent._owner;
  _owner->RetainAgent();
}

PLAAgent::~PLAAgent()
{
  _owner->ReleaseAgent();
}

/*
void PLAAgent::Release() const
{
  _owner->ReleaseAgent();
  _owner->Unbind();
}
 */
