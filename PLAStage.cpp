#include "PLAStage.hpp"
#include "Plain.hpp"
#include "PLAActor.hpp"

PLAStage *PLAStage::Create()
{
  PLAStage *stage = new PLAStage();
  PLAObject::Manager::GetInstance()->Bind(stage);
  return stage;
}

PLAStage::PLAStage() :
PLAObject(PLAObjectType::Stage)
{
  PLAStyle style;
  style.SetColorValue(PLAStyleType::FillColor, kPLAColorGray);
  PLASHPRect shape(kPLAVec2None, style);
  _context = PLAActor::Create(PLAVec3Make(0.5, 0.5, 0), kPLAColorWhite,
                              PLATransform(), shape);
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
