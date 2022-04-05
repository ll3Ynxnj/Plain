#ifndef PLAIN_ENGINE_PLAINPUT_HPP
#define PLAIN_ENGINE_PLAINPUT_HPP

#include <set>
#include <map>
#include <queue>
#include "Core/Class/PLAObject.hpp"
#include "PLAInputType.hpp"
#include "Type/PLAPoint.hpp"

class PLAInput : public PLAObject
{
  PLAInputDeviceType _deviceType = PLAInputDeviceType::None;
  PLAInputSignalCode _code = kPLAInputSignalCodeUndefined;
  PLAInputSignal _signal = false;
  PLAPoint _screenPoint = kPLAPointNone;

public:
  /*
  static PLAInput *Create(PLAInputDeviceType aDeviceType, PLAInputCode aCode,
                          PLAInputSignal aSignal, PLAPoint aScreenPoint);
  */
  static PLAInputSignalCode GetCodeForKeyFromChar(unsigned char aCharacter);
  static PLAInputSignalCode GetCodeOfNone(PLAInputDeviceType aType);
  static int GetNumberOfInputCodes(PLAInputDeviceType aDevice);

  PLAInput(PLAInputDeviceType aDevice, PLAInputSignalCode aCode,
           PLAInputSignal aSignal, const PLAPoint &aScreenPoint);
  virtual ~PLAInput();

  PLAInputDeviceType GetInputDeviceType() const { return _deviceType; };
  PLAInputSignalCode GetInputSignalCode() const { return _code; };
  PLAInputSignal GetInputSignal() const { return _signal; };
  PLAPoint GetScreenPoint() const { return _screenPoint; }
};

// PLAInputState ///////////////////////////////////////////////////////////////
class PLAInputState
{
  std::vector<std::vector<PLAInput>> _inputs = {};

public:
  PLAInputState();
  ~PLAInputState();

  PLAInput GetInput(const PLAInput &aInput) const;
  PLAInput GetInput(PLAInputDeviceType aDevice, PLAInputSignalCode aCode) const;
  void SetInput(const PLAInput &aInput);
};

// PLAInputContext /////////////////////////////////////////////////////////////
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

// PLAInputHandler /////////////////////////////////////////////////////////////
class PLAInputHandler
{
  /// \~ja 入力の対象は常に一つ
  PLAInputContext *_context = nullptr;

public:
  PLAInputHandler();
  ~PLAInputHandler();

  void Input(const PLAInput &aInput, const PLAInputState *aState);
  virtual PLAInputContext *RefContextWithInput(const PLAInput &aInput) const = 0;
  const PLAInputContext *GetContextWithInput(const PLAInput &aInput) const
  { return this->RefContextWithInput(aInput); }

private:
  void InputForTouch(const PLAInput &aInput, const PLAInputState *aState);
  void InputForMouse(const PLAInput &aInput, const PLAInputState *aState);
  void InputForKeyboard(const PLAInput &aInput, const PLAInputState *aState);
};

// PLAInputManager /////////////////////////////////////////////////////////////
class PLAInputManager
{
  static PLAInputManager _instance;

  std::queue<PLAInput> _inputs = {};
  PLAInputHandler *_handler = nullptr;
  PLAInputState _state = PLAInputState();

  PLAInputManager();

public:
  static PLAInputManager *Instance() { return &_instance; }

  ~PLAInputManager();

  void Init();
  void Input(PLAInputDeviceType aDevice, PLAInputSignalCode aCode,
             PLAInputSignal aSignal, const PLAPoint &aScreenPoint);
  void Flush();
  void SetHandler(PLAInputHandler *aHandler) { _handler = aHandler; };
};

#endif //PLAIN_ENGINE_PLAINPUT_HPP
