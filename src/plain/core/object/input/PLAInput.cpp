#include "plain/core/object/input/PLAInput.hpp"
#include "plain/core/app/PLAApp.hpp"
#include "plain/core/object/PLAOBJError.hpp"

/*
PLAInput *PLAInput::Create(PLAInputDeviceType aType, PLAInputCode aCode,
                           PLAInputSignal aSignal, PLAPoint aScreenPoint)
{
  PLAInput *input = new PLAInput(aType, aCode, aSignal, aScreenPoint);
  PLAObject::Manager::Instance()->Bind(input);
  return input;
}
 */

PLAInputSignalCode PLAInput::GetCodeForKeyFromChar(unsigned char aCharacter)
{
  if ('0' <= aCharacter && aCharacter <= '9')
  {
    PLAInputSignalCode base =
      static_cast<PLAInputSignalCode>(PLAInputSignalCodeForKeyboard::_0);
    PLAInputSignalCode offset = aCharacter - '0';
    return static_cast<PLAInputSignalCode>(base + offset);
  }

  if ('a' <= aCharacter && aCharacter <= 'z')
  {
    PLAInputSignalCode base =
      static_cast<PLAInputSignalCode>(PLAInputSignalCodeForKeyboard::A);
    PLAInputSignalCode offset = aCharacter - 'a';
    return static_cast<PLAInputSignalCode>(base + offset);
  }

  if ('A' <= aCharacter && aCharacter <= 'Z')
  {
    PLAInputSignalCode base =
      static_cast<PLAInputSignalCode>(PLAInputSignalCodeForKeyboard::A);
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
    static_cast<PLAInputSignalCode>(PLAInputSignalCodeForKeyboard::None)
  };
  return codes[static_cast<unsigned>(aDevice)];
}

int PLAInput::GetNumberOfInputCodes(PLAInputDeviceType aDevice)
{
  static int numberOfItems[static_cast<int>(PLAInputDeviceType::kNumberOfItems)] =
  {
    static_cast<int>(PLAInputSignalCodeForTouch::kNumberOfItems),
    static_cast<int>(PLAInputSignalCodeForMouse::kNumberOfItems),
    static_cast<int>(PLAInputSignalCodeForKeyboard::kNumberOfItems)
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



