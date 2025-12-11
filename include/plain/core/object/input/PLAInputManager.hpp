//
// Created by Kentaro Kawai on 2022/05/13.
//

#ifndef PLAIN_PLAINPUTMANAGER_HPP
#define PLAIN_PLAINPUTMANAGER_HPP

#include <queue>
#include "plain/core/object/input/PLAInput.hpp"
#include "plain/core/object/input/PLAInputState.hpp"
#include "plain/core/object/input/PLAInputHandler.hpp"

class PLAInputManager
{
  static PLAInputManager _instance;

  std::queue<const PLAInput *> _inputs = {};

  std::vector<PLAInputHandler *> _handlers = {};
  PLAInputState _state = PLAInputState();

  PLAInputManager();

public:
  static PLAInputManager *Instance() { return &_instance; }

  ~PLAInputManager();

  void Init();
  /*
  void Input(PLAInputDeviceType aDevice, PLAInputSignalCode aCode,
             PLAInputSignal aSignal, const PLAPoint &aScreenPoint);
             */
  void InputTouch(PLAInputSignalCode aCode, PLAInputSignal aSignal,
                  const PLAPoint &aScreenPoint);
  void InputMouse(PLAInputSignalCode aCode, PLAInputSignal aSignal,
                  const PLAPoint &aScreenPoint);
  void InputKey(PLAInputSignalCode aCode, PLAInputSignal aSignal);
  void InputCamera(PLAInputSignalCode aCode, PLAInputSignal aSignal);
  void Flush();
  void AddHandler(PLAInputHandler *aHandler) { _handlers.push_back(aHandler); };
  void RemoveHandler(PLAInputHandler *aHandler);
};

#endif //PLAIN_PLAINPUTMANAGER_HPP
