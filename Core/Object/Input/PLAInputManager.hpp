//
// Created by Kentaro Kawai on 2022/05/13.
//

#ifndef ANHR_PLAINPUTMANAGER_HPP
#define ANHR_PLAINPUTMANAGER_HPP

#include <vector>
#include "PLAInput.hpp"
#include "PLAInputState.hpp"
#include "PLAInputHandler.hpp"

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

#endif //ANHR_PLAINPUTMANAGER_HPP
