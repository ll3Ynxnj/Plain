//
// Created by Kentaro Kawai on 2022/05/13.
//

#ifndef PLAIN_PLAINPUTMANAGER_HPP
#define PLAIN_PLAINPUTMANAGER_HPP

#include <vector>
#include "plain/core/object/input/PLAInput.hpp"
#include "plain/core/object/input/PLAInputState.hpp"
#include "plain/core/object/input/PLAInputHandler.hpp"

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

#endif //PLAIN_PLAINPUTMANAGER_HPP
