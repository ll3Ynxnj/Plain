#include "PLAOBJStage.hpp"
#include "Agent/PLAAGTStage.hpp"
#include "Agent/PLAAGTActor.hpp"

PLAOBJStage *PLAOBJStage::Create()
{
  PLAOBJStage *stage = new PLAOBJStage();
  stage->Bind();
  return stage;
}

PLAOBJStage::PLAOBJStage() :
PLAObject(PLAObjectType::Stage)
{
  _context = PLAOBJActor::CreateRect(kPLAVec3fNone, kPLAColorGray,
                                     kPLATransformNorm, kPLARectNone);
  _context->SetObjectName("StageContext");
}

PLAOBJStage::~PLAOBJStage()
{
  delete(_context);
  _context = nullptr;
}

void PLAOBJStage::Init()
{
  _context->Init();

  PLAOBJAgent *agent = this->RefAgent();
  PLAAGTStage *stageAgent = static_cast<PLAAGTStage *>(agent);
  stageAgent->RunFunction(PLAAGTStage::FunctionCode::OnInit);
}

void PLAOBJStage::Update()
{
  _context->Update();
  PLAOBJAgent *agent = this->RefAgent();
  PLAAGTStage *stageAgent = static_cast<PLAAGTStage *>(agent);
  stageAgent->RunFunction(PLAAGTStage::FunctionCode::OnUpdate);
}

void PLAOBJStage::AddActor(PLAOBJActor *aActor)
{
  GRA_PRINT("AddActor : %s\n", aActor->GetObjectDescription().c_str());

  PLAString actorName = aActor->GetObjectName();
  if (actorName == kPLAStrUndefined) {
    GRA_TRACE("");
  }
  _context->AddActor(aActor);
}

void PLAOBJStage::PrintActors() const
{
  GRA_PRINT("//-- PLAOBJStage::PrintActors() const --\n");
  GRA_PRINT("////////////////////////////////////////\n");
  _context->PrintActors();
  GRA_PRINT("////////////////////////////////////////\n");
  GRA_PRINT("////////////////////////////////////////\n");
}

void PLAOBJStage::SetSize(const PLAVec3f &aSize)
{
  _context->SetSize(aSize);
  PLAOBJAgent *agent = this->RefAgent();
  PLAAGTStage *stageAgent = static_cast<PLAAGTStage *>(agent);
  stageAgent->RunFunction(PLAAGTStage::FunctionCode::OnResize);
}

// PLAInputHandler /////////////////////////////////////////////////////////////
PLAInputContext *PLAOBJStage::RefContextWithInput(const PLAInput &aInput) const
{
  PLAInputContext *inputContext = nullptr;
  switch (aInput.GetInputDeviceType())
  {
    case PLAInputDeviceType::Touch :
    case PLAInputDeviceType::Mouse :
      inputContext =
        _context->RefResponsiveActorWithPoint(aInput.GetScreenPoint(),
                                              aInput.GetInputDeviceType(),
                                              aInput.GetInputSignalCode());
      break;
    case PLAInputDeviceType::Keyboard :
      inputContext =
        _context->RefResponsiveActor(aInput.GetInputDeviceType(),
                                     aInput.GetInputSignalCode());
      break;
    default:
      PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                      "Unexpected PLAInputDeviceType detected.");
  }
  return inputContext;
}
