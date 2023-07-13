#include "PLAOBJStage.hpp"
#include "Agent/PLAAGTStage.hpp"
#include "Core/Agent/Actor/PLAAGTActor.hpp"

PLAOBJStage *PLAOBJStage::Create()
{
  PLAOBJStage *stage = new PLAOBJStage();
  stage->Init();
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
  _context = PLAOBJActor::CreateRect(kPLAVec3fNone, kPLAColorWhite,
                                     kPLATransformNorm, kPLARectNone,
                                     kPLAColorGray);
  _context->SetObjectName("StageContext");
}

PLAOBJStage::~PLAOBJStage()
{
  delete(_context);
  _context = nullptr;
}

void PLAOBJStage::Init()
{
  //_context->Init();
  //this->RunFunction(PLAFunctionCode::Stage::OnInit);
}

void PLAOBJStage::Update()
{
  _context->Update();
  //this->RunFunction(PLAFunctionCode::Stage::OnUpdate);
}

PLAAGTStage PLAOBJStage::AssignAgent()
{
  return PLAAGTStage(this);
}

void PLAOBJStage::AddListener(GRAOBJListener<PLAAGTStage, PLAFunctionCode::Stage> *aListener)
{
  _listeners.push_back(aListener);
};

void PLAOBJStage::RemoveListener(GRAOBJListener<PLAAGTStage, PLAFunctionCode::Stage> *aListener)
{
  _listeners.remove(aListener);
};

void PLAOBJStage::SetFunction(PLAFunctionCode::Stage aKey,
                              const std::function<void(PLAAGTStage)> &aFunc)
{
  _functor.SetFunction(aKey, aFunc);
};

void PLAOBJStage::RunFunction(PLAFunctionCode::Stage aKey)
{
  _functor.RunFunction(aKey, this->AssignAgent());//this->RefStage());
  for (GRAOBJListener<PLAAGTStage, PLAFunctionCode::Stage> *listener: _listeners)
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
  GRA_PRINT("//-- PLAOBJStage::PrintActors() const --");
  GRA_PRINT("////////////////////////////////////////\n");
  _context->PrintActors();
  GRA_PRINT("////////////////////////////////////////");
  GRA_PRINT("////////////////////////////////////////\n");
}

void PLAOBJStage::SetSize(const PLAVec3f &aSize)
{
  _context->SetSize(aSize);
  //PLAAGTStage agent = this->AssignAgent();
  //agent.RunFunction(PLAOBJStage::FunctionCode::OnResize);
  this->RunFunction(PLAFunctionCode::Stage::OnResize);
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
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Unexpected PLAInputDeviceType detected.");
  }
  return inputContext;
}
