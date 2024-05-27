//
// Created by Kentaro Kawai on 2023/05/20.
//

#include "Core/Agent/PLAAGTPhase.hpp"
#include "Core/Object/Phase/PLAOBJPhase.hpp"

PLAAGTPhase::PLAAGTPhase(PLAOBJPhase *aOwner) :
  PLAAgent(aOwner)
{

}

PLAAGTPhase::~PLAAGTPhase() noexcept
{

}

void PLAAGTPhase::AddListener(GRAOBJListener<PLAAGTPhase, PLAFunctionCode::Phase> *aListener) const
{
  auto owner = this->RefPhase();
  owner->AddListener(aListener);
}

void PLAAGTPhase::RemoveListener(GRAOBJListener<PLAAGTPhase, PLAFunctionCode::Phase> *aListener) const
{
  auto owner = this->RefPhase();
  owner->RemoveListener(aListener);
}

void PLAAGTPhase::SetFunction(PLAFunctionCode::Phase aKey,
                              const std::function<void(PLAAGTPhase)> &aFunc) const
{
  auto owner = this->RefPhase();
  owner->SetFunction(aKey, aFunc);
};

const PLAOBJPhase *PLAAGTPhase::GetPhase() const
{
  return static_cast<const PLAOBJPhase *>(this->GetOwner());
}

PLAOBJPhase *PLAAGTPhase::RefPhase() const
{
  return static_cast<PLAOBJPhase *>(this->RefOwner());
}

PLAId PLAAGTPhase::GetPhaseTag() const
{
  auto owner = this->GetPhase();
  return owner->GetPhaseTag();
}

void PLAAGTPhase::SetPhaseTag(PLAId aTag) const
{
  auto owner = this->RefPhase();
  owner->SetPhaseTag(aTag);
}
