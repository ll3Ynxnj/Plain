//
// Created by Kentaro Kawai on 2022/05/13.
//

#ifndef PLAIN_PLAINPUTCONTEXT_HPP
#define PLAIN_PLAINPUTCONTEXT_HPP

#include <map>
#include <functional>
#include "plain/core/object/input/PLAIPTTouch.hpp"
#include "plain/core/object/input/PLAIPTMouse.hpp"
#include "plain/core/object/input/PLAIPTKey.hpp"

class PLAInputContext
{
  PLABool _active = true;

/*
  std::map<PLAInputSignalCodeForTouch,
           std::map<PLAInputActionCodeForTouch,
                    std::function<void(PLAInputContext *,
                                       const PLAIPTTouch &)>>>
  _fTouchFunctors();

  std::map<PLAInputSignalCodeForMouse,
           std::map<PLAInputActionCodeForMouse,
                    std::function<void(PLAInputContext *,
                                       const PLAIPTMouse &)>>>
  _fMouseFunctors();

  std::map<PLAInputSignalCodeForKeyboard,
           std::map<PLAInputActionCodeForKeyboard,
                    std::function<void(PLAInputContext *,
                                       const PLAIPTKey &)>>>
  _fKeyboardFunctors();
  */

  std::map<PLAInputSignalCodeForTouch,
    std::map<PLAInputActionCodeForTouch,
      std::function<void(PLAInputContext *, const PLAIPTTouch &)>>>
        _fTouchFunctors =
    std::map<PLAInputSignalCodeForTouch,
      std::map<PLAInputActionCodeForTouch,
        std::function<void(PLAInputContext *, const PLAIPTTouch &)>>>();
  std::map<PLAInputSignalCodeForMouse,
    std::map<PLAInputActionCodeForMouse,
      std::function<void(PLAInputContext *, const PLAIPTMouse &)>>>
        _fMouseFunctors =
    std::map<PLAInputSignalCodeForMouse,
      std::map<PLAInputActionCodeForMouse,
        std::function<void(PLAInputContext *, const PLAIPTMouse &)>>>();
  std::map<PLAInputSignalCodeForKeyboard,
    std::map<PLAInputActionCodeForKeyboard,
      std::function<void(PLAInputContext *, const PLAIPTKey &)>>>
        _fKeyboardFunctors =
    std::map<PLAInputSignalCodeForKeyboard,
      std::map<PLAInputActionCodeForKeyboard,
        std::function<void(PLAInputContext *, const PLAIPTKey &)>>>();

  /*
  std::map<PLAInputDeviceType, std::map<PLAInputSignalCode,
  std::map<PLAInputActionCode,
  std::function<void(PLAInputContext *, const PLAInput &)>>>> _fInputFunctors =
  std::map<PLAInputDeviceType, std::map<PLAInputSignalCode,
  std::map<PLAInputActionCode,
  std::function<void(PLAInputContext *, const PLAInput &)>>>>();
   */

public :
  PLAInputContext();
  ~PLAInputContext();

  bool IsInputActive() const { return _active; };
  bool IsInputResponsive(PLAInputDeviceType aDeviceType,
                         PLAInputSignalCode aSignalCode);
  void InputWithTouch(const PLAIPTTouch &aInput,
                      PLAInputActionCodeForTouch aAction);
  void InputWithMouse(const PLAIPTMouse &aInput,
                      PLAInputActionCodeForMouse aAction);
  void InputWithKeyboard(const PLAIPTKey &aInput,
                         PLAInputActionCodeForKeyboard aAction);

  void SetInputActive(bool aValue) { _active = aValue; };
  void SetFunctorForInputWithTouch
    (PLAInputSignalCodeForTouch aSignalCode,
     PLAInputActionCodeForTouch aActionCode,
     const std::function<void(PLAInputContext *, const PLAIPTTouch &)> &aFunc);
  void SetFunctorForInputWithMouse
    (PLAInputSignalCodeForMouse aSignalCode,
     PLAInputActionCodeForMouse aActionCode,
     const std::function<void(PLAInputContext *, const PLAIPTMouse &)> &aFunc);
  void SetFunctorForInputWithKeyboard
    (PLAInputSignalCodeForKeyboard aSignalCode,
     PLAInputActionCodeForKeyboard aActionCode,
     const std::function<void(PLAInputContext *, const PLAIPTKey &)> &aFunc);

private:
  void Input(const PLAInput &aInput, PLAInputActionCode aAction);
  /*
  void SetFunctorForInput
    (PLAInputDeviceType aDeviceType, PLAInputSignalCode aInputCode,
     PLAInputActionCode aActionCode,
     const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc);
     */
  void InputTouch(const PLAIPTTouch &aInput,
                  PLAInputActionCodeForTouch aAction);
  void InputMouse(const PLAIPTMouse &aInput,
                  PLAInputActionCodeForMouse aAction);
  void InputKeyboard(const PLAIPTKey &aInput,
                     PLAInputActionCodeForKeyboard aAction);
};

#endif //PLAIN_PLAINPUTCONTEXT_HPP
