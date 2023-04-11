//
// Created by Kentaro Kawai on 2023/04/07.
//

#include "PLAAGTState.hpp"
#include "PLAAGTModel.hpp"

PLAAGTState *PLAAGTState::Create(PLAOBJState *aState)
{
  auto agent = new PLAAGTState(aState);
  agent->PLAObject::Bind();
  return agent;
}

PLAAGTState::PLAAGTState(PLAOBJState *aState) :
  PLAOBJAgent(aState)
{

}

PLAAGTState::~PLAAGTState() noexcept
{

}

void PLAAGTState::Init()
{
  static_cast<PLAOBJState *>(this->RefOwner())->Init();
}

void PLAAGTState::AddModel(PLAAGTModel *aAgent)
{
  PLAId modelId = aAgent->GetOwnerId();
  PLAOBJModel *model = static_cast<PLAOBJModel *>(PLAObject::Object(modelId));
  PLAId stateId = this->GetOwnerId();
  PLAOBJState *state = static_cast<PLAOBJState *>(PLAObject::Object(stateId));
  state->AddModel(model);
}

void PLAAGTState::PrintModels() const
{
  const PLAOBJState *state = this->GetState();
  state->PrintModels();
}
