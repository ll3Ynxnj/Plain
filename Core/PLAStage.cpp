#include "PLAStage.hpp"

PLAStage *PLAStage::Create()
{
  PLAStage *stage = new PLAStage();
  PLAObject::Bind(stage);
  return stage;
}

PLAStage::PLAStage() :
PLAObject(PLAObjectType::Stage),//, "== PLAStage =="),
PLAInputHandler()
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
  _functor.RunFunction(FunctionCode::OnInit, this);
  for (GRAListener<PLAStage, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnInit, this); }
}

void PLAStage::Update()
{
  _context->Update();
  _functor.RunFunction(FunctionCode::OnUpdate, this);
  for (GRAListener<PLAStage, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnUpdate, this); }
}

void PLAStage::AddActor(PLAActor *aActor)
{
  GRA_PRINT("AddActor : %s\n", aActor->GetObjectDescription().c_str());

  std::string actorName = aActor->GetObjectName();
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
  _functor.RunFunction(FunctionCode::OnResize, this);
  for (GRAListener<PLAStage, FunctionCode> *listener: _listeners)
  { listener->RunListener(FunctionCode::OnResize, this); }
}

// PLAInputHandler /////////////////////////////////////////////////////////////

PLAInputContext *PLAStage::RefContextWithInput(const PLAInput &aInput) const
{
  PLAInputContext *context = nullptr;
  switch (aInput.GetInputDeviceType())
  {
    case PLAInputDeviceType::Touch :
    case PLAInputDeviceType::Mouse :
      context =
        _context->RefResponsiveActorWithPoint(aInput.GetScreenPoint(),
                                              aInput.GetInputDeviceType(),
                                              aInput.GetInputSignalCode());
      break;
    case PLAInputDeviceType::Keyboard :
      context = _context->RefResponsiveActor(aInput.GetInputDeviceType(),
                                             aInput.GetInputSignalCode());
      break;
  }
  return context;
}
