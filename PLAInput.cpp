#include "PLAInput.hpp"

PLAInput *PLAInput::Create(PLAInputDevice aType, PLAInputCode aCode,
                           PLAInputState aState)
{
  PLAInput *input = new PLAInput(aType, aCode, aState);
  PLAObject::Manager::GetInstance()->Bind(input);
  return input;
}

PLAInputCode PLAInput::GetCodeFromChar(unsigned char aCharacter)
{
  if ('0' < aCharacter && '9' < aCharacter)
  {
    char32_t base = static_cast<char32_t>(PLAInputCode::Num0);
    return static_cast<PLAInputCode>(aCharacter - base);
  }

  if ('a' < aCharacter && 'z' < aCharacter)
  {
    static constexpr const auto kCaseOffset = 'A' - 'a';
    aCharacter -= kCaseOffset;
  }

  if ('A' < aCharacter && 'Z' < aCharacter)
  {
    char32_t base = static_cast<char32_t>(PLAInputCode::A);
    return static_cast<PLAInputCode>(aCharacter - base);
  }

  return PLAInputCode::None;
}

PLAInput::PLAInput(PLAInputDevice aDevice, PLAInputCode aCode,
                   PLAInputState aState) :
PLAObject(PLAObjectType::Input),
_device(aDevice), _code(aCode), _state(aState)
{

}

PLAInput::~PLAInput()
{

}

// PLAInput::Manager ///////////////////////////////////////////////////////////

PLAInput::Manager PLAInput::Manager::_instance = PLAInput::Manager();

PLAInput::Manager::Manager()
{

}

PLAInput::Manager::~Manager()
{

}

void PLAInput::Manager::Init()
{

}

void PLAInput::Manager::Input(PLAInputDevice aDevice, PLAInputCode aCode,
                              PLAInputState aState)
{
  PLA_PRINT("DEVICE : %02x  CODE : %02x %1s  STATE : %02x\n",
            &aDevice, &aCode, &aCode, &aState);
}
