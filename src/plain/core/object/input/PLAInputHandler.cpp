//
// Created by Kentaro Kawai on 2022/05/13.
//

#include "plain/core/object/input/PLAInputHandler.hpp"
#include "plain/core/object/PLAOBJError.hpp"

PLAInputHandler::PLAInputHandler()
{

}

PLAInputHandler::~PLAInputHandler()
{

}

void PLAInputHandler::Input(const PLAInput *aInput, const PLAInputState *aState)
{
  if (!_context)
  {
    _context = this->RefContextWithInput(aInput);
    if (!_context)
    {
      // Context not found - this handler doesn't handle this input type
      // (e.g., Stage doesn't handle Camera input, Stream::Manager doesn't handle Touch)
      // This is not an error, just skip processing
      return;
    }
  }

  switch (aInput->GetInputDeviceType())
  {
    case PLAInputDeviceType::Touch :
      this->InputForTouch(*static_cast<const PLAIPTTouch *>(aInput), aState);
      break;
    case PLAInputDeviceType::Mouse :
      this->InputForMouse(*static_cast<const PLAIPTMouse *>(aInput), aState);
      break;
    case PLAInputDeviceType::Keyboard :
      this->InputForKeyboard(*static_cast<const PLAIPTKey *>(aInput), aState);
      break;
    case PLAInputDeviceType::Camera :
      this->InputForCamera(*static_cast<const PLAIPTCamera *>(aInput), aState);
      break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Detect unexpected PLAInputDeviceType.");
      break;
  }
}

void PLAInputHandler::InputForTouch(const PLAIPTTouch &aInput,
                                    const PLAInputState *aState)
{
  PLAIPTTouch lastInput = *static_cast<const PLAIPTTouch *>(aState->GetInput(aInput));
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
}

void PLAInputHandler::InputForMouse(const PLAIPTMouse &aInput,
                                    const PLAInputState *aState)
{

}

void PLAInputHandler::InputForKeyboard(const PLAIPTKey &aInput,
                                       const PLAInputState *aState)
{
  PLAIPTKey lastInput = *static_cast<const PLAIPTKey *>(aState->GetInput(aInput));
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

void PLAInputHandler::InputForCamera(const PLAIPTCamera &aInput,
                                     const PLAInputState *aState)
{
  _context->InputWithCamera(aInput, PLAInputActionCodeForCamera::FrameUpdate);
}
