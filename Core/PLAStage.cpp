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
  _context = PLAActor::CreateRect(kPLAVec3None, kPLAColorWhite,
                                  kPLATransformNorm, kPLARectNone);
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
  GRA_PRINT("AddActor : %s\n", aActor->GetObjectDescription().c_str());

  std::string actorName = aActor->GetObjectName();
  if (actorName == kGRACharUndefined) {
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
}

// PLAInputHandler /////////////////////////////////////////////////////////////
PLAInputContext *PLAStage::RefContextWithInput(const PLAInput &aInput) const
{
  PLAActor *actor = _context->RefActorWithPoint(aInput.GetScreenPoint());
  return static_cast<PLAInputContext *>(actor);
}
