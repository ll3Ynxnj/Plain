//
// Created by Kentaro Kawai on 2022/05/13.
//

#ifndef ANHR_PLAINPUTCONTEXT_HPP
#define ANHR_PLAINPUTCONTEXT_HPP

#include "PLAInput.hpp"

class PLAInputContext
{
  /*
  std::function<void(PLAInputContext *, const PLAInput &)> _fInputTrigger =
  [](PLAInputContext *aContext, const PLAInput &aInput){};
  std::function<void(PLAInputContext *, const PLAInput &)> _fInputRefresh =
  [](PLAInputContext *aContext, const PLAInput &aInput){};
  std::function<void(PLAInputContext *, const PLAInput &)> _fInputRelease =
  [](PLAInputContext *aContext, const PLAInput &aInput){};
   */

  std::map<PLAInputDeviceType, std::map<PLAInputSignalCode, std::map<PLAInputActionCode,
    std::function<void(PLAInputContext *, const PLAInput &)>>>> _fInputFunctors =
  std::map<PLAInputDeviceType, std::map<PLAInputSignalCode,
    std::map<PLAInputActionCode,
    std::function<void(PLAInputContext *, const PLAInput &)>>>>();

public :
  PLAInputContext();
  ~PLAInputContext();

  bool IsResponsive(PLAInputDeviceType aDeviceType,
                    PLAInputSignalCode aSignalCode);
  void InputWithTouch(const PLAInput &aInput,
                      PLAInputActionCodeForTouch aAction);
  void InputWithMouse(const PLAInput &aInput,
                      PLAInputActionCodeForMouse aAction);
  void InputWithKeyboard(const PLAInput &aInput,
                         PLAInputActionCodeForKeyboard aAction);
  /*
  void InputTrigger(const PLAInput &aInput) { _fInputTrigger(this, aInput); };
  void InputRefresh(const PLAInput &aInput) { _fInputRefresh(this, aInput); };
  void InputRelease(const PLAInput &aInput) { _fInputRelease(this, aInput); };
  */

  void SetFunctorForInputWithTouch
    (PLAInputSignalCodeForTouch aSignalCode,
     PLAInputActionCodeForTouch aActionCode,
     const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc);
  void SetFunctorForInputWithMouse
    (PLAInputSignalCodeForMouse aSignalCode,
     PLAInputActionCodeForMouse aActionCode,
     const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc);
  void SetFunctorForInputWithKeyboard
    (PLAInputSignalCodeForKeyboard aSignalCode,
     PLAInputActionCodeForKeyboard aActionCode,
     const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc);
  /*
  void SetFunctorForInputTrigger
  (const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
  { _fInputTrigger = aFunc; }
  void SetFunctorForInputRefresh
  (const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
  { _fInputRefresh = aFunc; }
  void SetFunctorForInputRelease
  (const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
  { _fInputRelease = aFunc; }
   */
private:
  void Input(const PLAInput &aInput, PLAInputActionCode aAction);
  void SetFunctorForInput
    (PLAInputDeviceType aDeviceType, PLAInputSignalCode aInputCode,
     PLAInputActionCode aActionCode,
     const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc);
};

#endif //ANHR_PLAINPUTCONTEXT_HPP
