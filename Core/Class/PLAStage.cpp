#include "PLAStage.hpp"
#include "Agent/PLAAGTStage.hpp"
#include "Agent/PLAAGTActor.hpp"

PLAStage *PLAStage::Create()
{
  PLAStage *stage = new PLAStage();
  stage->Bind();
  return stage;
}

PLAStage::PLAStage() :
PLAObject(PLAObjectType::Stage)//,//, "== PLAStage =="),
//PLAInputHandler()
{
  //PLALYRRect layer(kPLAVec3None, kPLAVec2None, kPLAColorWhite);
  _context = PLAActor::CreateRect(kPLAVec3None, kPLAColorGray,
                                  kPLATransformNorm, kPLARectNone);
  _context->SetObjectName("StageContext");
}

PLAStage::~PLAStage()
{
  delete(_context);
  _context = nullptr;
}

void PLAStage::Init()
{
  _context->Init();

  //for (PLAAgent *agent: this->GetAgents()) {
  PLAAgent *agent = this->RefAgent();
    PLAAGTStage *stageAgent = static_cast<PLAAGTStage *>(agent);
    stageAgent->RunFunction(PLAAGTStage::FunctionCode::OnInit);
  //}
  /*
  _functor.RunFunction(FunctionCode::OnInit, this);
  for (GRAListener<PLAAGTStage, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnInit, this); }
   */
}

void PLAStage::Update()
{
  _context->Update();
  //for (PLAAgent *agent: this->GetAgents()) {
  PLAAgent *agent = this->RefAgent();
    PLAAGTStage *stageAgent = static_cast<PLAAGTStage *>(agent);
    stageAgent->RunFunction(PLAAGTStage::FunctionCode::OnUpdate);
  //}
  /*
  _functor.RunFunction(FunctionCode::OnUpdate, this);
  for (GRAListener<PLAAGTStage, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnUpdate, this); }
  */
}

void PLAStage::AddActor(PLAActor *aActor)
{
  GRA_PRINT("AddActor : %s\n", aActor->GetObjectDescription().c_str());

  PLAString actorName = aActor->GetObjectName();
  if (actorName == kPLAStrUndefined) {
    GRA_TRACE("");
  }
  _context->AddActor(aActor);
}

void PLAStage::PrintActors() const
{
  _context->PrintActors();
}

void PLAStage::SetSize(const PLAVec3 &aSize)
{
  _context->SetSize(aSize);
  //for (PLAAgent *agent: this->GetAgents()) {
  PLAAgent *agent = this->RefAgent();
    PLAAGTStage *stageAgent = static_cast<PLAAGTStage *>(agent);
    stageAgent->RunFunction(PLAAGTStage::FunctionCode::OnResize);
  //}
  /*
  _functor.RunFunction(FunctionCode::OnResize, this);
  for (GRAListener<PLAAGTStage, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnResize, this); }
   */
}

// PLAInputHandler /////////////////////////////////////////////////////////////
PLAInputContext *PLAStage::RefContextWithInput(const PLAInput &aInput) const
{
  PLAInputContext *inputContext = nullptr;
  PLAActor *responsiveActor = nullptr;
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
  }
  //stageContext->Release();
  return inputContext;
}
