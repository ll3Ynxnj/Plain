#include "PLAOBJStage.hpp"
#include "Agent/PLAAGTStage.hpp"
#include "Agent/PLAAGTActor.hpp"

PLAOBJStage *PLAOBJStage::Create()
{
  PLAOBJStage *stage = new PLAOBJStage();
  stage->Bind();
  return stage;
}

PLAOBJStage *PLAOBJStage::Object(const PLAString &aName)
{
  auto object = PLAObject::Object(PLAObjectType::Stage, aName);
  return static_cast<PLAOBJStage *>(object);
}

PLAOBJStage *PLAOBJStage::Object(PLAId aId)
{
  auto object = PLAObject::Object(PLAObjectType::Stage, aId);
  return static_cast<PLAOBJStage *>(object);
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
  PLAAGTStage agent = this->AssignAgent();
  agent.RunFunction(PLAOBJStage::FunctionCode::OnInit);
}

void PLAOBJStage::Update()
{
  _context->Update();
  PLAAGTStage agent = this->AssignAgent();
  agent.RunFunction(PLAOBJStage::FunctionCode::OnUpdate);
}

PLAAGTStage PLAOBJStage::AssignAgent()
{
  return PLAAGTStage(this);
}

void PLAOBJStage::AddListener(GRAOBJListener<PLAAGTStage, PLAOBJStage::FunctionCode> *aListener)
{ _listeners.push_back(aListener); };

void PLAOBJStage::RemoveListener(GRAOBJListener<PLAAGTStage, PLAOBJStage::FunctionCode> *aListener)
{ _listeners.remove(aListener); };

void PLAOBJStage::SetFunction(PLAOBJStage::FunctionCode aKey,
                 const std::function<void(PLAAGTStage)> &aFunc)
{ _functor.SetFunction(aKey, aFunc); };

void PLAOBJStage::RunFunction(PLAOBJStage::FunctionCode aKey)
{
  _functor.RunFunction(aKey, this->AssignAgent());//this->RefStage());
  for (GRAOBJListener<PLAAGTStage, PLAOBJStage::FunctionCode> *listener: _listeners)
  { listener->RunListener(aKey, this->AssignAgent()); }//this->RefStage()); }
};

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
  PLAAGTStage agent = this->AssignAgent();
  agent.RunFunction(PLAOBJStage::FunctionCode::OnResize);
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
