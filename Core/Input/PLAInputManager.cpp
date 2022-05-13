//
// Created by Kentaro Kawai on 2022/05/13.
//

#include "PLAInputManager.hpp"
#include "Class/PLAErrorType.hpp"

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

void PLAInputManager::Input(PLAInputDeviceType aDeviceType,
                            PLAInputSignalCode aCode,
                            PLAInputSignal aSignal,
                            const PLAPoint &aScreenPoint)
{
  GRA_PRINT("DEVICE : %02x  CODE : %02x %1s  SIGNAL : %d  "
            "SCREEN_POINT : x %.2f  y %.2f\n",
            aDeviceType, aCode, &aCode, aSignal,
            aScreenPoint.x, aScreenPoint.y);

  PLAPoint screenPoint = aScreenPoint;
  if (aDeviceType == PLAInputDeviceType::Keyboard)
  { screenPoint = kPLAPointUndefined; }

  PLAInput input = PLAInput(aDeviceType, aCode, aSignal, screenPoint);
  _inputs.push(input);
}

void PLAInputManager::Flush()
{
  while (_inputs.size())
  {
    PLAInput input = _inputs.back();
    _inputs.pop();

    //ここからStateの値と照らし合わせて呼ぶべきファンクタを呼ぶ？
    _handler->Input(input, &_state);
    /*
    for (PLAInputHandler *handler : _handlers)
    {

      //PLAInput::Context *detectedContext = context->RefContextWithInput(input);
      //if (detectedContext) { detectedContext->Input(input); };
    }
     */

    _state.SetInput(input);
  }
}

/*
void PLAInputManager::AddHandler(PLAInputHandler *aHandler)
{
  try { _handlers.insert(aHandler); }
  catch(...)
  { PLA_ERROR_ISSUE(PLAErrorType::Expect, "Failed to add context."); }
}

void PLAInputManager::RemoveHandler(PLAInputHandler *aHandler)
{
  try { _handlers.erase(aHandler); }
  catch(...)
  { PLA_ERROR_ISSUE(PLAErrorType::Expect, "Failed to remove context."); }
}
 */
