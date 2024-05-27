//
// Created by Kentaro Kawai on 2023/04/07.
//

#include "Core/Agent/PLAAGTState.hpp"
#include "Core/Agent/PLAAGTModel.hpp"
#include "Core/Object/PLAOBJState.hpp"

PLAAGTState::PLAAGTState(PLAOBJState *aOwner) :
  PLAAgent(aOwner)
{

}

PLAAGTState::~PLAAGTState() noexcept
{

}

void PLAAGTState::Init() const
{
  static_cast<PLAOBJState *>(this->RefOwner())->Init();
}

void PLAAGTState::AddModel(const PLAAGTModel &aAgent) const
{
  PLAId modelId = aAgent.GetObjectId();
  //PLAOBJModel *model = static_cast<PLAOBJModel *>(PLAObject::Object(modelId));
  PLAOBJModel *model = PLAOBJModel::Object(modelId);
  PLAId stateId = this->GetObjectId();
  //PLAOBJState *state = static_cast<PLAOBJState *>(PLAObject::Object(stateId));
  PLAOBJState *state = PLAOBJState::Object(stateId);
  state->AddModel(model);
}

void PLAAGTState::PrintModels() const
{
  const PLAOBJState *state = this->GetState();
  state->PrintModels();
}

const PLAOBJState *PLAAGTState::GetState() const
{
  return static_cast<const PLAOBJState *>(this->GetOwner());
}

PLAOBJState *PLAAGTState::RefState() const
{
  return static_cast<PLAOBJState *>(this->RefOwner());
}
