//
// Created by Kentaro Kawai on 2022/04/28.
//

#include "PLAAGTStage.hpp"
#include "PLAAGTActor.hpp"
#include "Object/PLAOBJStage.hpp"

PLAAGTStage::PLAAGTStage(PLAOBJStage *aOwner) :
  PLAAgent(aOwner)
{

}

PLAAGTStage::~PLAAGTStage() noexcept
{

}

void PLAAGTStage::Init() const
{
  static_cast<PLAOBJStage *>(this->RefOwner())->Init();
}

void PLAAGTStage::AddActor(const PLAAGTActor &aAgent) const
{
  PLAId actorId = aAgent.GetOwnerId();
  PLAOBJActor *actor = PLAOBJActor::Object(actorId);
  /*
  PLAId stageId = this->GetOwnerId();
  PLAOBJStage *stage = PLAOBJStage::Object(stageId);
   */
  auto stage = this->RefStage();
  stage->AddActor(actor);
}

void PLAAGTStage::AddListener(GRAOBJListener<PLAAGTStage, PLAFunctionCode::Stage> *aListener) const
{
  auto owner = this->RefStage();
  owner->AddListener(aListener);
};

void PLAAGTStage::RemoveListener(GRAOBJListener<PLAAGTStage, PLAFunctionCode::Stage> *aListener) const
{
  auto owner = this->RefStage();
  owner->RemoveListener(aListener);
};

void PLAAGTStage::SetFunction(PLAFunctionCode::Stage aKey,
                              const std::function<void(PLAAGTStage)> &aFunc) const
{
  auto owner = this->RefStage();
  owner->SetFunction(aKey, aFunc);
};

void PLAAGTStage::RunFunction(PLAFunctionCode::Stage aKey) const
{
  auto owner = this->RefStage();
  owner->RunFunction(aKey);//this->RefStage());
};

void PLAAGTStage::PrintActors() const
{
  const PLAOBJStage *stage = this->GetStage();
  stage->PrintActors();
}

PLAVec3f PLAAGTStage::GetSize() const
{
  const PLAOBJStage *stage = this->GetStage();
  return stage->GetSize();
}

const PLAOBJStage *PLAAGTStage::GetStage() const
{
  return static_cast<const PLAOBJStage *>(this->GetOwner());
}

PLAOBJStage *PLAAGTStage::RefStage() const
{
  return static_cast<PLAOBJStage *>(this->RefOwner());
}
