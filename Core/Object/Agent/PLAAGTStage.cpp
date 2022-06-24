//
// Created by Kentaro Kawai on 2022/04/28.
//

#include "PLAAGTStage.hpp"
#include "PLAAGTActor.hpp"

PLAAGTStage *PLAAGTStage::Create(PLAOBJStage *aStage)
{
  auto agent = new PLAAGTStage(aStage);
  agent->PLAObject::Bind();
  return agent;
}

PLAAGTStage::PLAAGTStage(PLAOBJStage *aStage) :
  PLAOBJAgent(aStage)
{

}

PLAAGTStage::~PLAAGTStage() noexcept
{

}

void PLAAGTStage::Init()
{
  static_cast<PLAOBJStage *>(this->RefOwner())->Init();
}

void PLAAGTStage::AddActor(PLAAGTActor *aAgent)
{
  PLAId actorId = aAgent->GetOwnerId();
  PLAOBJActor *actor = static_cast<PLAOBJActor *>(PLAObject::Object(actorId));
  PLAId stageId = this->GetOwnerId();
  PLAOBJStage *stage = static_cast<PLAOBJStage *>(PLAObject::Object(stageId));
  stage->AddActor(actor);
}

void PLAAGTStage::PrintActors() const
{
  const PLAOBJStage *stage = this->GetStage();
  stage->PrintActors();
}

PLAVec3 PLAAGTStage::GetSize() const
{
  const PLAOBJStage *stage = this->GetStage();
  return stage->GetSize();
}

// PLAInputHandler /////////////////////////////////////////////////////////////
/*
PLAInputContext *PLAAGTStage::RefContextWithInput(const PLAInput &aInput) const
{
  PLAInputContext *inputContext = nullptr;
  PLAOBJActor *inputContextActor = nullptr;
  const PLAOBJStage *stage = this->GetStage();
  PLAOBJActor *stageContext = stage->RefContext();
  const PLAAGTActor *stageContextAgent =
    static_cast<const PLAAGTActor *>(stageContext->AssignAgent());
  switch (aInput.GetInputDeviceType())
  {
    case PLAInputDeviceType::Touch :
    case PLAInputDeviceType::Mouse :
      inputContextActor =
        stageContext->RefResponsiveActorWithPoint(aInput.GetScreenPoint(),
                                                  aInput.GetInputDeviceType(),
                                                  aInput.GetInputSignalCode());
      break;
    case PLAInputDeviceType::Keyboard :
      inputContextActor =
        stageContext->RefResponsiveActor(aInput.GetInputDeviceType(),
                                         aInput.GetInputSignalCode());
      break;
  }
  return static_cast<PLAAGTActor *>(inputContextActor->AssignAgent());
  //ここから
  // Agentの管理を参照カウンタ方式に変更した
  // ここでAssignしたらどこでReleaseするの？
  // ↑Assignしない。InputHandlerもInputContextもAgentではなくObjectに戻す。Objectの_agentが参照カウンタ方式で単一になったので、そこからAgentを引っ張れる
}
*/