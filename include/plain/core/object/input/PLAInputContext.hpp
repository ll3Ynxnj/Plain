//
// Created by Kentaro Kawai on 2022/05/13.
//

#ifndef ANHR_PLAINPUTCONTEXT_HPP
#define ANHR_PLAINPUTCONTEXT_HPP

#include <map>
#include <functional>
#include "plain/core/object/input/PLAInput.hpp"

class PLAInputContext
{
  PLABool _active = true;

  std::map<PLAInputDeviceType, std::map<PLAInputSignalCode,
  std::map<PLAInputActionCode,
  std::function<void(PLAInputContext *, const PLAInput &)>>>> _fInputFunctors =
  std::map<PLAInputDeviceType, std::map<PLAInputSignalCode,
  std::map<PLAInputActionCode,
  std::function<void(PLAInputContext *, const PLAInput &)>>>>();

public :
  PLAInputContext();
  ~PLAInputContext();

  bool IsInputActive() const { return _active; };
  bool IsInputResponsive(PLAInputDeviceType aDeviceType,
                         PLAInputSignalCode aSignalCode);
  void InputWithTouch(const PLAInput &aInput,
                      PLAInputActionCodeForTouch aAction);
  void InputWithMouse(const PLAInput &aInput,
                      PLAInputActionCodeForMouse aAction);
  void InputWithKeyboard(const PLAInput &aInput,
                         PLAInputActionCodeForKeyboard aAction);

  void SetInputActive(bool aValue) { _active = aValue; };
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

private:
  void Input(const PLAInput &aInput, PLAInputActionCode aAction);
  void SetFunctorForInput
    (PLAInputDeviceType aDeviceType, PLAInputSignalCode aInputCode,
     PLAInputActionCode aActionCode,
     const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc);
};

#endif //ANHR_PLAINPUTCONTEXT_HPP
