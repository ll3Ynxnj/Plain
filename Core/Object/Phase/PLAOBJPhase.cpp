//
// Created by Kentaro Kawai on 2023/05/20.
//

#include "PLAOBJPhase.hpp"

#include "Agent/PLAAGTPhase.hpp"

#include "Grain/Library/GRALIBString.hpp"

#include "Object/PLAOBJError.hpp"

PLAOBJPhase *PLAOBJPhase::Create()
{
  PLAOBJPhase *phase = new PLAOBJPhase();
  phase->Init();
  phase->Bind();
  return phase;
}

PLAOBJPhase *PLAOBJPhase::Object(const PLAString &aName)
{
  auto object = PLAObject::Object(PLAObjectType::Phase, aName);
  return static_cast<PLAOBJPhase *>(object);
}

PLAOBJPhase *PLAOBJPhase::Object(PLAId aId)
{
  auto object = PLAObject::Object(PLAObjectType::Phase, aId);
  return static_cast<PLAOBJPhase *>(object);
}

PLABool PLAOBJPhase::IsValidPath(const PLAString &aPath)
{
  for(char character : aPath) {
    if(!std::isalnum(character) && character != '/') {
      return false;
    }
  }
  return true;
}

PLAOBJPhase::PLAOBJPhase() :
  PLAObject(PLAObjectType::Phase)
{

}

PLAOBJPhase::PLAOBJPhase(PLAString aName) :
  PLAObject(PLAObjectType::Phase, aName)
{

}

PLAOBJPhase::~PLAOBJPhase()
{

}

void PLAOBJPhase::Init()
{
  this->RunFunction(PLAFunctionCode::Phase::OnInit);
}

PLAAGTPhase PLAOBJPhase::AssignAgent()
{
  return PLAAGTPhase(this);
}

void PLAOBJPhase::AddListener(GRAOBJListener<PLAAGTPhase, PLAFunctionCode::Phase> *aListener)
{
  _listeners.push_back(aListener);
}

void PLAOBJPhase::RemoveListener(GRAOBJListener<PLAAGTPhase, PLAFunctionCode::Phase> *aListener)
{
  _listeners.remove(aListener);
}

void PLAOBJPhase::SetFunction(PLAFunctionCode::Phase aKey,
                              const std::function<void(PLAAGTPhase)> &aFunc)
{
  _functor.SetFunction(aKey, aFunc);
}

void PLAOBJPhase::PushChild(PLAOBJPhase *aPhase)
{
  auto oldPhase = _phases.empty() ? nullptr : _phases.top();
  auto newPhase = aPhase;
  _phases.push(newPhase);
  if (_poppedPhase != nullptr) { _poppedPhase->Unbind(); }
  _poppedPhase = nullptr;

  this->RunFunction(PLAFunctionCode::Phase::OnPushChild);
  newPhase->RunFunction(PLAFunctionCode::Phase::OnPushed);
  if (oldPhase) { oldPhase->RunFunction(PLAFunctionCode::Phase::OnPushedOver); }
}

void PLAOBJPhase::PopChild()
{
  if (_phases.empty()) {
    PLA_ERROR_ISSUE(PLAErrorType::Expect,
                    "Phase stack is empty. Cannot pop phase.");
    return;
  }

  if (_poppedPhase) { _poppedPhase->Unbind(); }

  auto oldPhase = _phases.top();
  _phases.pop();
  auto newPhase = _phases.top();
  _poppedPhase = oldPhase;

  this->RunFunction(PLAFunctionCode::Phase::OnPopChild);
  oldPhase->RunFunction(PLAFunctionCode::Phase::OnPopped);
  newPhase->RunFunction(PLAFunctionCode::Phase::OnPoppedOver);
}

void PLAOBJPhase::PrintPhases() const
{
  static int indentLevel = 0;
  GRA_PRINT(this->GetObjectDescription().c_str());
  ++indentLevel;
  auto phases = _phases;
  while (!phases.empty())
  {
    for (int i = 0; i < indentLevel; i++) { GRA_PRINT("  "); }
    auto phase = phases.top();
    phase->PrintPhases();
    phases.pop();
  }
  --indentLevel;
}

void PLAOBJPhase::RunFunction(PLAFunctionCode::Phase aKey)
{
  _functor.RunFunction(aKey, this->AssignAgent());//this->RefStage());
  for (GRAOBJListener<PLAAGTPhase, PLAFunctionCode::Phase> *listener: _listeners)
  { listener->RunListener(aKey, this->AssignAgent()); }//this->RefStage()); }
}

