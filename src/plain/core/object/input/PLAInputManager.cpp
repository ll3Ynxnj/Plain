//
// Created by Kentaro Kawai on 2022/05/13.
//

#include "plain/core/object/input/PLAInputManager.hpp"
#include "plain/core/object/input/PLAIPTTouch.hpp"
#include "plain/core/object/input/PLAIPTMouse.hpp"
#include "plain/core/object/input/PLAIPTKey.hpp"

PLAInputManager PLAInputManager::_instance = PLAInputManager();

PLAInputManager::PLAInputManager()
{

}

PLAInputManager::~PLAInputManager()
{

}

void PLAInputManager::Init()
{

}

/*
void PLAInputManager::Input(PLAInputDeviceType aDeviceType,
                            PLAInputSignalCode aCode,
                            PLAInputSignal aSignal,
                            const PLAPoint &aScreenPoint)
{
  GRA_DEBUG("[INPUT] DEVICE: %02x CODE: %02x %1s SIGNAL: %d SCREEN_POINT: x %.2f y %.2f",
            aDeviceType, aCode, &aCode, aSignal,
            aScreenPoint.x, aScreenPoint.y);

  PLAPoint screenPoint = aScreenPoint;
  if (aDeviceType == PLAInputDeviceType::Keyboard)
  { screenPoint = kPLAPointUndefined; }

  const PLAInput *input = new PLAInput(aDeviceType, aCode, aSignal, screenPoint);
  _inputs.push(input);
}
*/

void PLAInputManager::InputTouch(PLAInputSignalCode aCode,
                                 PLAInputSignal aSignal,
                                 const PLAPoint &aScreenPoint)
{
  const PLAIPTTouch *input = new PLAIPTTouch(aCode, aSignal, aScreenPoint);
  _inputs.push(input);
}

void PLAInputManager::InputMouse(PLAInputSignalCode aCode,
                                 PLAInputSignal aSignal,
                                 const PLAPoint &aScreenPoint)
{
  const PLAIPTMouse *input = new PLAIPTMouse(aCode, aSignal, aScreenPoint);
  _inputs.push(input);
}

void PLAInputManager::InputKey(PLAInputSignalCode aCode, PLAInputSignal aSignal)
{
  const PLAIPTKey *input = new PLAIPTKey(aCode, aSignal);
  _inputs.push(input);
}

void PLAInputManager::Flush()
{
  while (_inputs.size())
  {
    const PLAInput *input = _inputs.front();
    _inputs.pop();
    _handler->Input(input, &_state);
    _state.SetInput(input);
    delete input;
  }
}
