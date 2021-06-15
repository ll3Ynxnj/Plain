#ifndef PLAIN_ENGINE_PLAINPUT_HPP
#define PLAIN_ENGINE_PLAINPUT_HPP

#include <set>
#include <map>
#include <queue>
#include "PLAObject.hpp"
#include "PLAInputType.hpp"
#include "Type/PLAPoint.hpp"

class PLAInput : public PLAObject
{
  PLAInputDeviceType _deviceType = PLAInputDeviceType::None;
  PLAInputCode _code = kPLAInputCodeUndefined;
  PLAInputSignal _signal = false;
  PLAPoint _screenPoint = kPLAPointNone;

public:
  /*
  static PLAInput *Create(PLAInputDeviceType aDeviceType, PLAInputCode aCode,
                          PLAInputSignal aSignal, PLAPoint aScreenPoint);
  */
  static PLAInputCode GetCodeForKeyFromChar(unsigned char aCharacter);
  static PLAInputCode GetCodeOfNone(PLAInputDeviceType aType);
  static int GetNumberOfInputCodes(PLAInputDeviceType aDevice);

  PLAInput(PLAInputDeviceType aDevice, PLAInputCode aCode,
           PLAInputSignal aSignal, const PLAPoint &aScreenPoint);
  virtual ~PLAInput();

  PLAInputDeviceType GetInputDeviceType() const { return _deviceType; };
  PLAInputCode GetInputCode() const { return _code; };
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
  PLAInput GetInput(PLAInputDeviceType aDevice, PLAInputCode aCode) const;
  void SetInput(const PLAInput &aInput);
};

// PLAInputContext /////////////////////////////////////////////////////////////

class PLAInputContext
{
  std::function<void(PLAInputContext *, const PLAInput &)> _fInputTrigger =
  [](PLAInputContext *aContext, const PLAInput &aInput){};
  std::function<void(PLAInputContext *, const PLAInput &)> _fInputRefresh =
  [](PLAInputContext *aContext, const PLAInput &aInput){};
  std::function<void(PLAInputContext *, const PLAInput &)> _fInputRelease =
  [](PLAInputContext *aContext, const PLAInput &aInput){};

public :
  PLAInputContext();
  ~PLAInputContext();

  void InputTrigger(const PLAInput &aInput) { _fInputTrigger(this, aInput); };
  void InputRefresh(const PLAInput &aInput) { _fInputRefresh(this, aInput); };
  void InputRelease(const PLAInput &aInput) { _fInputRelease(this, aInput); };

  void SetFunctorForInputTrigger
  (const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
  { _fInputTrigger = aFunc; }
  void SetFunctorForInputRefresh
  (const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
  { _fInputRefresh = aFunc; }
  void SetFunctorForInputRelease
  (const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
  { _fInputRelease = aFunc; }
};

// PLAInputHandler /////////////////////////////////////////////////////////////

class PLAInputHandler
{
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
  void InputForKey(const PLAInput &aInput, const PLAInputState *aState);
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
  static PLAInputManager *GetInstance() { return &_instance; }

  ~PLAInputManager();

  void Init();
  void Input(PLAInputDeviceType aDevice, PLAInputCode aCode,
             PLAInputSignal aSignal, const PLAPoint &aScreenPoint);
  void Flush();
  void SetHandler(PLAInputHandler *aHandler) { _handler = aHandler; };
};

#endif //PLAIN_ENGINE_PLAINPUT_HPP
