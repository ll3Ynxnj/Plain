//
// Created by Kentaro Kawai on 2022/05/13.
//

#include "PLAInputHandler.hpp"
#include "Core/Class/PLAError.hpp"

PLAInputHandler::PLAInputHandler()
{

}

PLAInputHandler::~PLAInputHandler()
{

}

void PLAInputHandler::Input(const PLAInput &aInput, const PLAInputState *aState)
{
  if (!_context)
  {
    _context = this->RefContextWithInput(aInput);
    if (!_context)
    {
      PLA_ERROR_ISSUE(PLAErrorType::Expect, "Context not found.");
      return;
    }
  }

  switch (aInput.GetInputDeviceType())
  {
    case PLAInputDeviceType::Touch :
      this->InputForTouch(aInput, aState);
      break;
    case PLAInputDeviceType::Mouse :
      this->InputForMouse(aInput, aState);
      break;
    case PLAInputDeviceType::Keyboard :
      this->InputForKeyboard(aInput, aState);
      break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Detect unexpected PLAInputDeviceType.");
      break;
  }
}

void PLAInputHandler::InputForTouch(const PLAInput &aInput,
                                    const PLAInputState *aState)
{
  PLAInput lastInput = aState->GetInput(aInput);
  if (lastInput.GetInputSignal())
  {
    if (aInput.GetInputSignal())
    {
      _context->InputWithTouch(aInput, PLAInputActionCodeForTouch::Drag);
    }
    else
    {
      _context->InputWithTouch(aInput, PLAInputActionCodeForTouch::Release);
      _context = nullptr;
    }
  }
  else
  {
    _context->InputWithTouch(aInput, PLAInputActionCodeForTouch::Press);
  }
  /*
  PLAInput lastInput = aState->GetInput(aInput);
  if (lastInput.GetInputSignal())
  {
    if (aInput.GetInputSignal())
    {
      _context->InputRefresh(aInput);
    }
    else
    {
      _context->InputRelease(aInput);
      _context = nullptr;
    }
  }
  else
  {
    _context->InputTrigger(aInput);
  }
  */
  /*
  { // No context detected with current input value.
    if (_context)
    { // There is a detected context with the previous input value.
      if (aInput.GetInputSignal())
      {
        _context->_fInputRollout(aInput);
      }
      else
      {
        PLA_ERROR_ISSUE(PLAErrorType::Assert, "Detected unexpected input.");
      }
    }
    else
    { // Context not found
      PLA_ERROR_ISSUE(PLAErrorType::Expect, "Context not found");
    }
  }
  */
}

void PLAInputHandler::InputForMouse(const PLAInput &aInput,
                                    const PLAInputState *aState)
{

}

void PLAInputHandler::InputForKeyboard(const PLAInput &aInput,
                                       const PLAInputState *aState)
{
  PLAInput lastInput = aState->GetInput(aInput);
  if (lastInput.GetInputSignal())
  {
    if (!aInput.GetInputSignal())
    {
      _context->InputWithKeyboard(aInput, PLAInputActionCodeForKeyboard::Release);
      _context = nullptr;
    }
  }
  else
  {
    _context->InputWithKeyboard(aInput, PLAInputActionCodeForKeyboard::Press);
  }
}
