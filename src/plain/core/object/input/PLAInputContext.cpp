//
// Created by Kentaro Kawai on 2022/05/13.
//

#include "plain/core/object/input/PLAInputContext.hpp"
#include "plain/core/object/PLAOBJError.hpp"

PLAInputContext::PLAInputContext()
{

}

PLAInputContext::~PLAInputContext()
{

}

bool PLAInputContext::IsInputResponsive(PLAInputDeviceType aDeviceType,
                                        PLAInputSignalCode aSignalCode)
{
  switch (aDeviceType) {
    case PLAInputDeviceType::Touch:
      {
        std::map<PLAInputSignalCodeForTouch,
          std::map<PLAInputActionCodeForTouch,
            std::function<void(PLAInputContext *,
                               const PLAIPTTouch &)>>>::iterator
              sigItr = _fTouchFunctors.find(static_cast<PLAInputSignalCodeForTouch>(aSignalCode));
        if (sigItr == _fTouchFunctors.end()) { return false; }
      }
      break;
    case PLAInputDeviceType::Mouse:
      {
        std::map<PLAInputSignalCodeForMouse,
          std::map<PLAInputActionCodeForMouse,
            std::function<void(PLAInputContext *,
                               const PLAIPTMouse &)>>>::iterator
              sigItr = _fMouseFunctors.find(static_cast<PLAInputSignalCodeForMouse>(aSignalCode));
        if (sigItr == _fMouseFunctors.end()) { return false; }
      }
      break;
    case PLAInputDeviceType::Keyboard:
      {
        std::map<PLAInputSignalCodeForKeyboard,
          std::map<PLAInputActionCodeForKeyboard,
            std::function<void(PLAInputContext *,
                               const PLAIPTKey &)>>>::iterator
              sigItr = _fKeyboardFunctors.find(static_cast<PLAInputSignalCodeForKeyboard>(aSignalCode));
        if (sigItr == _fKeyboardFunctors.end()) { return false; }
      }
      break;
    default:
      {
        PLA_ERROR_ISSUE(PLAErrorType::Assert,
                        "Unknown input device type.");
      }
  }
  /*
  std::map<PLAInputDeviceType, std::map<PLAInputSignalCode,
  std::map<PLAInputActionCode,
  std::function<void(PLAInputContext *, const PLAInput &)>>>>::iterator devItr =
    _fInputFunctors.find(aDeviceType);
  if (devItr == _fInputFunctors.end()) { return false; }

  std::map<PLAInputSignalCode, std::map<PLAInputActionCode,
  std::function<void(PLAInputContext *, const PLAInput &)>>>::iterator sigItr =
    (*devItr).second.find(aSignalCode);
  if (sigItr == (*devItr).second.end()) { return false; }
  */

  return true;
}

void PLAInputContext::InputWithTouch(const PLAIPTTouch &aInput,
                                     PLAInputActionCodeForTouch aAction)
{
  if (!_active) { return; }

  PLAInputSignalCodeForTouch signalCode =
    static_cast<PLAInputSignalCodeForTouch>(aInput.GetInputSignalCode());
  std::map<PLAInputActionCodeForTouch,
    std::function<void(PLAInputContext *, const PLAIPTTouch &)>> actions =
    _fTouchFunctors[signalCode];

  std::map<PLAInputActionCodeForTouch,
    std::function<void(PLAInputContext *, const PLAIPTTouch &)>>::iterator
      actItr = actions.find(aAction);

  if (actItr == actions.end()) { return; }
  (*actItr).second(this, static_cast<const PLAIPTTouch &>(aInput));

  //this->Input(aInput, static_cast<PLAInputActionCode>(aAction));
}

void PLAInputContext::InputWithMouse(const PLAIPTMouse &aInput,
                                     PLAInputActionCodeForMouse aAction)
{
  if (!_active) { return; }

  PLAInputSignalCodeForMouse signalCode =
    static_cast<PLAInputSignalCodeForMouse>(aInput.GetInputSignalCode());
  std::map<PLAInputActionCodeForMouse,
    std::function<void(PLAInputContext *, const PLAIPTMouse &)>> actions =
    _fMouseFunctors[signalCode];
  
  std::map<PLAInputActionCodeForMouse,
    std::function<void(PLAInputContext *, const PLAIPTMouse &)>>::iterator
      actItr = actions.find(aAction);

  if (actItr == actions.end()) { return; }
  (*actItr).second(this, static_cast<const PLAIPTMouse &>(aInput));

  //this->Input(aInput, static_cast<PLAInputActionCode>(aAction));
}

void PLAInputContext::InputWithKeyboard(const PLAIPTKey &aInput,
                                        PLAInputActionCodeForKeyboard aAction)
{
  if (!_active) { return; }

  PLAInputSignalCodeForKeyboard signalCode =
    static_cast<PLAInputSignalCodeForKeyboard>(aInput.GetInputSignalCode());
  std::map<PLAInputActionCodeForKeyboard,
    std::function<void(PLAInputContext *, const PLAIPTKey &)>> actions =
    _fKeyboardFunctors[signalCode];

  std::map<PLAInputActionCodeForKeyboard,
    std::function<void(PLAInputContext *, const PLAIPTKey &)>>::iterator
      actItr = actions.find(aAction);

  if (actItr == actions.end()) { return; }
  (*actItr).second(this, static_cast<const PLAIPTKey &>(aInput));

  //this->Input(aInput, static_cast<PLAInputActionCode>(aAction));
}

void PLAInputContext::SetFunctorForInputWithTouch
  (PLAInputSignalCodeForTouch aSignalCode,
   PLAInputActionCodeForTouch aActionCode,
   const std::function<void(PLAInputContext *, const PLAIPTTouch &)> &aFunc)
{
  _fTouchFunctors[aSignalCode][aActionCode] = aFunc;
  /*
  this->SetFunctorForInput(PLAInputDeviceType::Touch,
                           static_cast<PLAInputSignalCode>(aSignalCode),
                           static_cast<PLAInputActionCode>(aActionCode), aFunc);
                           */
}

void PLAInputContext::SetFunctorForInputWithMouse
  (PLAInputSignalCodeForMouse aSignalCode,
   PLAInputActionCodeForMouse aActionCode,
   const std::function<void(PLAInputContext *, const PLAIPTMouse &)> &aFunc)
{
  _fMouseFunctors[aSignalCode][aActionCode] = aFunc;
  /*
  this->SetFunctorForInput(PLAInputDeviceType::Mouse,
                           static_cast<PLAInputSignalCode>(aSignalCode),
                           static_cast<PLAInputActionCode>(aActionCode), aFunc);
                           */
}

void PLAInputContext::SetFunctorForInputWithKeyboard
  (PLAInputSignalCodeForKeyboard aSignalCode,
   PLAInputActionCodeForKeyboard aActionCode,
   const std::function<void(PLAInputContext *, const PLAIPTKey &)> &aFunc)
{
  _fKeyboardFunctors[aSignalCode][aActionCode] = aFunc;
  /*
  this->SetFunctorForInput(PLAInputDeviceType::Keyboard,
                           static_cast<PLAInputSignalCode>(aSignalCode),
                           static_cast<PLAInputActionCode>(aActionCode), aFunc);
                           */
}

/*
void PLAInputContext::Input(const PLAInput &aInput,
                            PLAInputActionCode aActionCode)
{
  if (!_active) { return; }
  // The following responsive checks are redundant because they are performed during context search.
  // 以下のレスポンシブチェックは、コンテキスト検索時に実行しているので冗長な処理。
  if (!this->IsInputResponsive(aInput.GetInputDeviceType(),
                               aInput.GetInputSignalCode())) { return; }
 

  switch (aInput.GetInputDeviceType())
  {
    case PLAInputDeviceType::Touch:
      {
        std::map<PLAInputActionCode,
          std::function<void(PLAInputContext *, const PLAIPTTouch &)>> actions =
          _fTouchFunctors[aInput.GetInputSignalCode()];
        std::map<PLAInputActionCode,
          std::function<void(PLAInputContext *, const PLAIPTTouch &)>>::iterator
            actItr = actions.find(aActionCode);
        if (actItr == actions.end()) { return; }
        (*actItr).second(this, static_cast<const PLAIPTTouch &>(aInput));
      }
      break;
    case PLAInputDeviceType::Mouse:
      {
        std::map<PLAInputActionCode,
          std::function<void(PLAInputContext *, const PLAIPTMouse &)>> actions =
          _fMouseFunctors[aInput.GetInputSignalCode()];
        std::map<PLAInputActionCode,
          std::function<void(PLAInputContext *, const PLAIPTMouse &)>>::iterator
            actItr = actions.find(aActionCode);
        if (actItr == actions.end()) { return; }
        (*actItr).second(this, static_cast<const PLAIPTMouse &>(aInput));
      }
      break;
    case PLAInputDeviceType::Keyboard:
      {
        std::map<PLAInputActionCode,
          std::function<void(PLAInputContext *, const PLAIPTKey &)>> actions =
          _fKeyboardFunctors[aInput.GetInputSignalCode()];
        std::map<PLAInputActionCode,
          std::function<void(PLAInputContext *, const PLAIPTKey &)>>::iterator
            actItr = actions.find(aActionCode);
        if (actItr == actions.end()) { return; }
        (*actItr).second(this, static_cast<const PLAIPTKey &>(aInput));
      }
      break;
    default:
      {
        PLA_ERROR_ISSUE(PLAErrorType::Assert,
                        "Unknown input device type.");
      }
  }
  // std::map<PLAInputActionCode,
  //   std::function<void(PLAInputContext *, const PLAInput &)>> actions =
  //   _fInputFunctors[aInput.GetInputDeviceType()][aInput.GetInputSignalCode()];
  // std::map<PLAInputActionCode,
  //   std::function<void(PLAInputContext *, const PLAInput &)>>::iterator actItr =
  //   actions.find(aActionCode);

  // if (actItr == actions.end()) { return; }

  // (*actItr).second(this, aInput);
}
*/

/*
void PLAInputContext::SetFunctorForInput
  (PLAInputDeviceType aDeviceType, PLAInputSignalCode aSignalCode,
   PLAInputActionCode aActionCode,
   const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
{
  _fInputFunctors[aDeviceType][aSignalCode][aActionCode] = aFunc;
}
*/
