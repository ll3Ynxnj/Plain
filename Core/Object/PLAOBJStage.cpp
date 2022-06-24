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
PLAObject(PLAObjectType::Stage)//,//, "== PLAOBJStage =="),
//PLAInputHandler()
{
  //PLALYRRect layer(kPLAVec3None, kPLAVec2None, kPLAColorWhite);
  _context = PLAOBJActor::CreateRect(kPLAVec3None, kPLAColorGray,
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

  //for (PLAOBJAgent *agent: this->GetAgents()) {
  PLAOBJAgent *agent = this->RefAgent();
    PLAAGTStage *stageAgent = static_cast<PLAAGTStage *>(agent);
    stageAgent->RunFunction(PLAAGTStage::FunctionCode::OnInit);
  //}
  /*
  _functor.RunFunction(FunctionCode::OnInit, this);
  for (GRAOBJListener<PLAAGTStage, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnInit, this); }
   */
}

void PLAOBJStage::Update()
{
  _context->Update();
  //for (PLAOBJAgent *agent: this->GetAgents()) {
  PLAOBJAgent *agent = this->RefAgent();
    PLAAGTStage *stageAgent = static_cast<PLAAGTStage *>(agent);
    stageAgent->RunFunction(PLAAGTStage::FunctionCode::OnUpdate);
  //}
  /*
  _functor.RunFunction(FunctionCode::OnUpdate, this);
  for (GRAOBJListener<PLAAGTStage, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnUpdate, this); }
  */
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
  _context->PrintActors();
}

void PLAOBJStage::SetSize(const PLAVec3 &aSize)
{
  _context->SetSize(aSize);
  //for (PLAOBJAgent *agent: this->GetAgents()) {
  PLAOBJAgent *agent = this->RefAgent();
    PLAAGTStage *stageAgent = static_cast<PLAAGTStage *>(agent);
    stageAgent->RunFunction(PLAAGTStage::FunctionCode::OnResize);
  //}
  /*
  _functor.RunFunction(FunctionCode::OnResize, this);
  for (GRAOBJListener<PLAAGTStage, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnResize, this); }
   */
}

// PLAInputHandler /////////////////////////////////////////////////////////////
PLAInputContext *PLAOBJStage::RefContextWithInput(const PLAInput &aInput) const
{
  PLAInputContext *inputContext = nullptr;
  //PLAOBJActor *responsiveActor = nullptr;
  switch (aInput.GetInputDeviceType())
  {
    case PLAInputDeviceType::Touch :
    case PLAInputDeviceType::Mouse :
      inputContext =
      //responsiveActor =
        _context->RefResponsiveActorWithPoint(aInput.GetScreenPoint(),
                                              aInput.GetInputDeviceType(),
                                              aInput.GetInputSignalCode());
      break;
    case PLAInputDeviceType::Keyboard :
      inputContext =
      //responsiveActor =
        _context->RefResponsiveActor(aInput.GetInputDeviceType(),
                                     aInput.GetInputSignalCode());
      break;
    default:
      PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                      "Unexpected PLAInputDeviceType detected.");
  }
  //stageContext->Release();
  return inputContext;
}
