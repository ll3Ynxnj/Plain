//
// Created by Kentaro Kawai on 2023/05/20.
//

#include "PLAOBJPhase.hpp"
#include "Agent/PLAAGTPhase.hpp"
#include "Grain/Library/GRALIBString.hpp"
#include "App/PLAApp.hpp"
#include "Object/PLAOBJError.hpp"

// 不要なのでは？同じくBinderItemであるPLAOBJResourceには無い。要調査。
// It's not necessary? PLAOBJResource, which is also a BinderItem, does not have it. Need to investigate.
const std::map<PLAOBJPhase::Binder::Error, const char *> PLAOBJPhase::kBinderErrorMessages =
{
  { Binder::Error::OverwriteItem, "Overwrite item" },
  { Binder::Error::NameConflict, "Item name conflict" },
  { Binder::Error::NameOverride, "Item name has been over written" },
  { Binder::Error::NameConvertedBySystem, "Item name has been converted to system-generated" },
  { Binder::Error::RegisterExistingKeyToMap, "Register existing key to map" },
  { Binder::Error::NotExistInMap, "Not exist in map" },
  { Binder::Error::OutOfRange, "Out of range" },
};

// 不要なのでは？同じくBinderItemであるPLAOBJResourceには無い。要調査。
// It's not necessary? PLAOBJResource, which is also a BinderItem, does not have it. Need to investigate.
const char *PLAOBJPhase::GetBinderErrorMessage(Binder::Error aError)
{
  return kBinderErrorMessages.at(aError);
}

PLAOBJPhase *PLAOBJPhase::Create()
{
  PLAOBJPhase *phase = new PLAOBJPhase();
  phase->Init();
  phase->Bind();
  return phase;
}

PLAOBJPhase *PLAOBJPhase::CreateWithTag(PLAId aTag)
{
  PLAOBJPhase *phase = new PLAOBJPhase(aTag);
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

PLAOBJPhase *PLAOBJPhase::ObjectWithTag(PLAId aTag)
{
  GRAOBJBinder<PLAOBJPhase>::Error error(GRAOBJBinder<PLAOBJPhase>::Error::None);
  auto object = Manager::Instance()->RefItemWithTag(aTag, &error);
  if (error != GRAOBJBinder<PLAOBJPhase>::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJPhase getting. ERROR : %02d", error);
  }
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

void PLAOBJPhase::Bind()
{
  this->PLAObject::Bind();

  GRAOBJBinder<PLAOBJPhase>::Error error(GRAOBJBinder<PLAOBJPhase>::Error::None);
  PLAOBJPhase::Manager::Instance()->Bind(this, &error);
  if (error != GRAOBJBinder<PLAOBJPhase>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJPhase binding. ERROR : %02d", error); }
}

void PLAOBJPhase::Unbind()
{
  GRAOBJBinder<PLAOBJPhase>::Error error(GRAOBJBinder<PLAOBJPhase>::Error::None);
  PLAOBJPhase::Manager::Instance()->Unbind(this, &error);
  if (error != GRAOBJBinder<PLAOBJPhase>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJPhase unbinding. ERROR : %02d", error); }

  this->PLAObject::Unbind();
}

PLAOBJPhase::PLAOBJPhase() :
  PLAObject(PLAObjectType::Phase),
  GRAOBJBinder<PLAOBJPhase>::Item(Manager::Instance())
{

}

PLAOBJPhase::PLAOBJPhase(PLAId aTag) :
  PLAObject(PLAObjectType::Phase),
  GRAOBJBinder<PLAOBJPhase>::Item(aTag, Manager::Instance())
{

}

PLAOBJPhase::PLAOBJPhase(PLAId aTag, PLAString aName) :
  PLAObject(PLAObjectType::Phase, aName),
  GRAOBJBinder<PLAOBJPhase>::Item(aTag, Manager::Instance())
{

}

PLAOBJPhase::~PLAOBJPhase()
{

}

void PLAOBJPhase::Init()
{
  //this->RunFunction(PLAFunctionCode::Phase::OnInit);
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
  //if (_poppedPhase != nullptr) { _poppedPhase->Unbind(); }
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

  //if (_poppedPhase) { _poppedPhase->Unbind(); }

  auto oldPhase = _phases.top();
  _phases.pop();
  auto newPhase = _phases.top();
  _poppedPhase = oldPhase;

  this->RunFunction(PLAFunctionCode::Phase::OnPopChild);
  oldPhase->RunFunction(PLAFunctionCode::Phase::OnPopped);
  newPhase->RunFunction(PLAFunctionCode::Phase::OnPoppedOver);
}

PLAId PLAOBJPhase::GetPhaseTag() const {
  return this->GRAOBJBinder<PLAOBJPhase>::Item::GetTag();
}

void PLAOBJPhase::SetPhaseTag(PLAId aTag)
{
  //GRAOBJBinder<PLAOBJPhase>::Error error(GRAOBJBinder<PLAOBJPhase>::Error::None);
  Binder::Error error(Binder::Error::None);
  this->Binder::Item::SetTag(aTag, &error);
  if (error != Binder::Error::None)
  {
    switch (error) {
      case GRAOBJBinder<PLAOBJPhase>::Error::TagOverride :
        PLA_ERROR_ISSUE(PLAErrorType::Expect,
                        "Succeed to set phase tag with error. ERROR : %02d : %s",
                        error, PLAOBJPhase::GetBinderErrorMessage(error));
        break;
      default :
        PLA_ERROR_ISSUE(PLAErrorType::Assert,
                        "Failure to set phase tag. ERROR : %02d : %s",
                        error, PLAOBJPhase::GetBinderErrorMessage(error));
        break;
    }
  }
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

const char *PLAOBJPhase::GetPhaseTypeName() const
{
  static const char *kName = "(STUB: PhaseType)";//"== STUB ==";
  return kName;
}

void PLAOBJPhase::RunFunction(PLAFunctionCode::Phase aKey)
{
  _functor.RunFunction(aKey, this->AssignAgent());//this->RefStage());
  for (GRAOBJListener<PLAAGTPhase, PLAFunctionCode::Phase> *listener: _listeners)
  { listener->RunListener(aKey, this->AssignAgent()); }//this->RefStage()); }
}

const char *PLAOBJPhase::GetBinderItemTypeName() const
{
  return this->GetPhaseTypeName();
}

// PLAOBJPhase::Manager ////////////////////////////////////////////////////////

PLAOBJPhase::Manager PLAOBJPhase::Manager::_instance = PLAOBJPhase::Manager();

PLAOBJPhase::Manager::Manager() : GRAOBJBinder<PLAOBJPhase>()
{

}

PLAOBJPhase::Manager::~Manager()
{

}

void PLAOBJPhase::Manager::Init()
{
  GRAOBJBinder<PLAOBJPhase>::Init();
}

PLAOBJPhase *PLAOBJPhase::Manager::Phase(const PLAString &aKey)
{
  GRAOBJBinder<PLAOBJPhase>::Error error(GRAOBJBinder<PLAOBJPhase>::Error::None);
  return static_cast<PLAOBJPhase *>(_instance.RefItemWithName(aKey, &error));
}

void PLAOBJPhase::Manager::PrintPhases() const
{

};

const PLAOBJPhase *PLAOBJPhase::Manager::GetPhase(const PLAString &aName) const
{
  PLAPhaseError error = PLAPhaseError::None;
  const PLAOBJPhase *resource =
    static_cast<const PLAOBJPhase *>(this->GetItemWithName(aName, &error));
  if (error != PLAPhaseError::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to get resource. ERROR : %02d", error);
  }
  return resource;
};
