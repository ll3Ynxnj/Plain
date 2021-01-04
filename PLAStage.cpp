#include "PLAStage.hpp"

PLAStage *PLAStage::Create()
{
  PLAStage *stage = new PLAStage();
  PLAObject::Manager::GetInstance()->Bind(stage);
  return stage;
}

PLAStage::PLAStage() :
PLAObject(PLAObjectType::Stage, "== PLAStage =="),
PLAInputHandler()
{
  PLASHPRect shape(kPLAVec3None, kPLAVec2None);
  PLAStyle style;
  style.SetColorValue(PLAStyleType::FillColor, kPLAColorGray);
  /*
  _context = PLAActor::Create(PLAVec3Make(0.5, 0.5, 0), kPLAColorWhite,
                              PLATransform(), shape);
                              */
  _context = PLAActor::Create(kPLAVec3None, kPLAColorWhite,
                              PLATransform(), shape);
  _context->SetStyle(style);
}

PLAStage::~PLAStage()
{
  delete(_context);
  _context = nullptr;
}

void PLAStage::Update()
{
  _context->Update();
}

void PLAStage::AddActor(PLAActor *aActor)
{
  PLA_PRINT("AddActor");
  aActor->PrintObject();

  std::string actorName = aActor->GetObjectName();
  if (actorName == kPLACharUndefined) {
    PLA_TRACE("");
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
}

// PLAInputHandler /////////////////////////////////////////////////////////////
PLAInputContext *PLAStage::RefContextWithInput(const PLAInput &aInput) const
{
  PLAActor *actor = _context->RefActorWithPoint(aInput.GetScreenPoint());
  return static_cast<PLAInputContext *>(actor);
}
