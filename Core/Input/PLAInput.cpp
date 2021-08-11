#include "PLAInput.hpp"
#include "PLAApp.hpp"
#include "PLAError.hpp"

/*
PLAInput *PLAInput::Create(PLAInputDeviceType aType, PLAInputCode aCode,
                           PLAInputSignal aSignal, PLAPoint aScreenPoint)
{
  PLAInput *input = new PLAInput(aType, aCode, aSignal, aScreenPoint);
  PLAObject::Manager::GetInstance()->Bind(input);
  return input;
}
 */

PLAInputSignalCode PLAInput::GetCodeForKeyFromChar(unsigned char aCharacter)
{
  if ('0' <= aCharacter && aCharacter <= '9')
  {
    PLAInputSignalCode base =
      static_cast<PLAInputSignalCode>(PLAInputSignalCodeForKey::_0);
    PLAInputSignalCode offset = aCharacter - '0';
    return static_cast<PLAInputSignalCode>(base + offset);
  }

  if ('a' <= aCharacter && aCharacter <= 'z')
  {
    PLAInputSignalCode base =
      static_cast<PLAInputSignalCode>(PLAInputSignalCodeForKey::A);
    PLAInputSignalCode offset = aCharacter - 'a';
    return static_cast<PLAInputSignalCode>(base + offset);
  }

  if ('A' <= aCharacter && aCharacter <= 'Z')
  {
    PLAInputSignalCode base =
      static_cast<PLAInputSignalCode>(PLAInputSignalCodeForKey::A);
    PLAInputSignalCode offset = aCharacter - 'A';
    return static_cast<PLAInputSignalCode>(base + offset);
  }

  return kPLAInputSignalCodeUndefined;
}

PLAInputSignalCode PLAInput::GetCodeOfNone(PLAInputDeviceType aDevice)
{
  static PLAInputSignalCode
  codes[static_cast<PLAInputSignalCode>(PLAInputDeviceType::kNumberOfItems)] =
  {
    static_cast<PLAInputSignalCode>(PLAInputSignalCodeForTouch::None),
    static_cast<PLAInputSignalCode>(PLAInputSignalCodeForMouse::None),
    static_cast<PLAInputSignalCode>(PLAInputSignalCodeForKey::None)
  };
  return codes[static_cast<unsigned>(aDevice)];
}

int PLAInput::GetNumberOfInputCodes(PLAInputDeviceType aDevice)
{
  static int numberOfItems[static_cast<int>(PLAInputDeviceType::kNumberOfItems)] =
  {
    static_cast<int>(PLAInputSignalCodeForTouch::kNumberOfItems),
    static_cast<int>(PLAInputSignalCodeForMouse::kNumberOfItems),
    static_cast<int>(PLAInputSignalCodeForKey::kNumberOfItems)
  };
  return numberOfItems[static_cast<unsigned>(aDevice)];
}

PLAInput::PLAInput(PLAInputDeviceType aDeviceType, PLAInputSignalCode aCode,
                   PLAInputSignal aSignal, const PLAPoint &aScreenPoint) :
PLAObject(PLAObjectType::Input, "== PLAInput =="),
_deviceType(aDeviceType), _code(aCode), _signal(aSignal),
_screenPoint(aScreenPoint)
{

}

PLAInput::~PLAInput()
{

}

// PLAInputState ///////////////////////////////////////////////////////////////

PLAInputState::PLAInputState()
{
  for (int device = 0;
       device < static_cast<int>(PLAInputDeviceType::kNumberOfItems); device++)
  {
    PLAInputDeviceType deviceType = static_cast<PLAInputDeviceType>(device);
    PLAInputSignalCode code = PLAInput::GetCodeOfNone(deviceType);
    int numberOfCodes = PLAInput::GetNumberOfInputCodes(deviceType);
    PLAInput input = PLAInput(deviceType, code, 0, PLAPoint(0));
    _inputs.push_back({});
    for (int code = 0; code < numberOfCodes; code++)
    { _inputs.back().push_back(input); }
  }
}

PLAInputState::~PLAInputState()
{

}

PLAInput PLAInputState::GetInput(const PLAInput &aInput) const
{
  return this->GetInput(aInput.GetInputDeviceType(), aInput.GetInputCode());
}

PLAInput PLAInputState::GetInput(PLAInputDeviceType aDevice,
                                 PLAInputSignalCode aCode) const
{
  if (aCode >= PLAInput::GetNumberOfInputCodes(aDevice))
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Detected unexpected PLAInputCode.");
  }
  return _inputs[static_cast<unsigned>(aDevice)][aCode];
}

void PLAInputState::SetInput(const PLAInput &aInput)
{
  unsigned device = static_cast<unsigned>(aInput.GetInputDeviceType());
  _inputs[device][aInput.GetInputCode()] = aInput;
}

// PLAInput::Context ///////////////////////////////////////////////////////////

PLAInputContext::PLAInputContext()
{
  for (PLAUInt device = 0;
       device < static_cast<PLAUInt>(PLAInputDeviceType::kNumberOfItems);
       device++)
  {
    _fInputFunctors[static_cast<PLAInputDeviceType>(device)] =
      std::map<PLAInputSignalCode, std::map<PLAInputActionCode,
        std::function<void(PLAInputContext *, const PLAInput &)>>>();
  }
}

PLAInputContext::~PLAInputContext()
{

}

void PLAInputContext::Input(const PLAInput &aInput, PLAInputActionCode aAction)
{
  /*
  std::map<PLAInputCode, std::map<PLAInputFunctor,
  std::function<void(PLAInputContext *, const PLAInput &)>>>::iterator it =
  _fInputFunctors[aInput.GetInputDeviceType()].find(aInput.GetInputCode());
  if (it == _fInputFunctors[aInput.GetInputDeviceType()].end()) { return; }
   */
  _fInputFunctors[aInput.GetInputDeviceType()][aInput.GetInputCode()][aAction]
  (this, aInput);
}

void PLAInputContext::SetFunctorForInput
(PLAInputDeviceType aType, PLAInputSignalCode aCode, PLAInputActionCode aFunctor,
 const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
{
  _fInputFunctors[aType][aCode][aFunctor] = aFunc;
}

// PLAInputHandler /////////////////////////////////////////////////////////////

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
    case PLAInputDeviceType::Touch : this->InputForTouch(aInput, aState); break;
    case PLAInputDeviceType::Mouse : this->InputForMouse(aInput, aState); break;
    case PLAInputDeviceType::Keyboard : this->InputForKey(aInput, aState); break;
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
      _context->
      Input(aInput,
            static_cast<PLAInputActionCode>
            (PLAInputActionCodeForTouch::Drag));
    }
    else
    {
      _context->
      Input(aInput,
            static_cast<PLAInputActionCode>
            (PLAInputActionCodeForTouch::Release));
      _context = nullptr;
    }
  }
  else
  {
    _context->
    Input(aInput,
          static_cast<PLAInputActionCode>
          (PLAInputActionCodeForTouch::Press));
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

void PLAInputHandler::InputForKey(const PLAInput &aInput,
                                  const PLAInputState *aState)
{
  PLAInput lastInput = aState->GetInput(aInput);
  if (lastInput.GetInputSignal())
  {
    if (!aInput.GetInputSignal())
    {
      _context->
        Input(aInput,
              static_cast<PLAInputActionCode>
              (PLAInputActionCodeForKey::Release));
      _context = nullptr;
    }
  }
  else
  {
    _context->
      Input(aInput,
            static_cast<PLAInputActionCode>
            (PLAInputActionCodeForKey::Press));
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
}

// PLAInputManager /////////////////////////////////////////////////////////////

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
