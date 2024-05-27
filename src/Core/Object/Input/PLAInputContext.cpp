//
// Created by Kentaro Kawai on 2022/05/13.
//

#include "Core/Object/Input/PLAInputContext.hpp"
#include "Core/Object/PLAOBJError.hpp"

PLAInputContext::PLAInputContext()
{

}

PLAInputContext::~PLAInputContext()
{

}

bool PLAInputContext::IsInputResponsive(PLAInputDeviceType aDeviceType,
                                        PLAInputSignalCode aSignalCode)
{
  std::map<PLAInputDeviceType, std::map<PLAInputSignalCode,
  std::map<PLAInputActionCode,
  std::function<void(PLAInputContext *, const PLAInput &)>>>>::iterator devItr =
    _fInputFunctors.find(aDeviceType);
  if (devItr == _fInputFunctors.end()) { return false; }

  std::map<PLAInputSignalCode, std::map<PLAInputActionCode,
  std::function<void(PLAInputContext *, const PLAInput &)>>>::iterator sigItr =
    (*devItr).second.find(aSignalCode);
  if (sigItr == (*devItr).second.end()) { return false; }

  return true;
}

void PLAInputContext::InputWithTouch(const PLAInput &aInput,
                                     PLAInputActionCodeForTouch aAction)
{
  this->Input(aInput, static_cast<PLAInputActionCode>(aAction));
}

void PLAInputContext::InputWithMouse(const PLAInput &aInput,
                                     PLAInputActionCodeForMouse aAction)
{
  this->Input(aInput, static_cast<PLAInputActionCode>(aAction));
}

void PLAInputContext::InputWithKeyboard(const PLAInput &aInput,
                                        PLAInputActionCodeForKeyboard aAction)
{
  this->Input(aInput, static_cast<PLAInputActionCode>(aAction));
}

void PLAInputContext::SetFunctorForInputWithTouch
  (PLAInputSignalCodeForTouch aSignalCode,
   PLAInputActionCodeForTouch aActionCode,
   const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
{
  this->SetFunctorForInput(PLAInputDeviceType::Touch,
                           static_cast<PLAInputSignalCode>(aSignalCode),
                           static_cast<PLAInputActionCode>(aActionCode), aFunc);
}

void PLAInputContext::SetFunctorForInputWithMouse
  (PLAInputSignalCodeForMouse aSignalCode,
   PLAInputActionCodeForMouse aActionCode,
   const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
{
  this->SetFunctorForInput(PLAInputDeviceType::Mouse,
                           static_cast<PLAInputSignalCode>(aSignalCode),
                           static_cast<PLAInputActionCode>(aActionCode), aFunc);
}

void PLAInputContext::SetFunctorForInputWithKeyboard
  (PLAInputSignalCodeForKeyboard aSignalCode,
   PLAInputActionCodeForKeyboard aActionCode,
   const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
{
  this->SetFunctorForInput(PLAInputDeviceType::Keyboard,
                           static_cast<PLAInputSignalCode>(aSignalCode),
                           static_cast<PLAInputActionCode>(aActionCode), aFunc);
}

void PLAInputContext::Input(const PLAInput &aInput,
                            PLAInputActionCode aActionCode)
{
  if (!_active) { return; }
  // The following responsive checks are redundant because they are performed during context search.
  // 以下のレスポンシブチェックは、コンテキスト検索時に実行しているので冗長な処理。
  if (!this->IsInputResponsive(aInput.GetInputDeviceType(),
                               aInput.GetInputSignalCode())) { return; }

  std::map<PLAInputActionCode,
    std::function<void(PLAInputContext *, const PLAInput &)>> actions =
    _fInputFunctors[aInput.GetInputDeviceType()][aInput.GetInputSignalCode()];
  std::map<PLAInputActionCode,
    std::function<void(PLAInputContext *, const PLAInput &)>>::iterator actItr =
    actions.find(aActionCode);
  if (actItr == actions.end()) { return; }

  (*actItr).second(this, aInput);
}

void PLAInputContext::SetFunctorForInput
  (PLAInputDeviceType aDeviceType, PLAInputSignalCode aSignalCode,
   PLAInputActionCode aActionCode,
   const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
{
  _fInputFunctors[aDeviceType][aSignalCode][aActionCode] = aFunc;
}
