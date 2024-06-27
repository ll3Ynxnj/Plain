//
// Created by Kentaro Kawai on 2022/05/13.
//

#include "plain/core/object/input/PLAInputState.hpp"
#include "plain/core/object/input/PLAIPTTouch.hpp"
#include "plain/core/object/input/PLAIPTMouse.hpp"
#include "plain/core/object/input/PLAIPTKey.hpp"
#include "plain/core/object/PLAOBJError.hpp"

PLAInputState::PLAInputState()
{
  // 全デバイスの全入力情報を作成
  // All devices create all input information
  for (PLAInt device = 0;
       device < static_cast<int>(PLAInputDeviceType::kNumberOfItems); device++)
  {
    PLAInputDeviceType deviceType = static_cast<PLAInputDeviceType>(device);
    PLAInputSignalCode code = PLAInput::GetCodeOfNone(deviceType);
    PLAInt numberOfCodes = PLAInput::GetNumberOfInputCodes(deviceType);
    for (int code = 0; code < numberOfCodes; code++)
    {
      switch (deviceType)
      {
        case PLAInputDeviceType::Touch:
          _touches.push_back(PLAIPTTouch(code, 0, PLAPoint(0)));
          break;
        case PLAInputDeviceType::Mouse:
          _mouses.push_back(PLAIPTMouse(code, 0, PLAPoint(0)));
          break;
        case PLAInputDeviceType::Keyboard:
          _keys.push_back(PLAIPTKey(code, 0));
          break;
      }
    }
    /*
    PLAInput input = PLAInput(deviceType, code, 0, PLAPoint(0));
    _inputs.push_back({});
    for (int code = 0; code < numberOfCodes; code++)
    { _inputs.back().push_back(input); }
    */
  }
}

PLAInputState::~PLAInputState()
{

}

PLAInput PLAInputState::GetInput(const PLAInput &aInput) const
{
  return this->GetInput(aInput.GetInputDeviceType(), aInput.GetInputSignalCode());
}

PLAInput PLAInputState::GetInput(PLAInputDeviceType aDevice,
                                 PLAInputSignalCode aCode) const
{
  if (aCode >= PLAInput::GetNumberOfInputCodes(aDevice))
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Detected unexpected PLAInputCode.");
  }

  //return _inputs[static_cast<unsigned>(aDevice)][aCode];

  switch (aDevice)
  {
    case PLAInputDeviceType::Touch:
      return _touches[aCode];
    case PLAInputDeviceType::Mouse:
      return _mouses[aCode];
    case PLAInputDeviceType::Keyboard:
      return _keys[aCode];
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Detected unexpected PLAInputDeviceType.");
  }
}

void PLAInputState::SetInput(const PLAInput &aInput)
{
  unsigned device = static_cast<unsigned>(aInput.GetInputDeviceType());

  //_inputs[device][aInput->GetInputSignalCode()] = input;
  
  switch (aInput.GetInputDeviceType())
  {
    case PLAInputDeviceType::Touch:
      _touches[aInput.GetInputSignalCode()] =
        static_cast<const PLAIPTTouch &>(aInput);
      break;
    case PLAInputDeviceType::Mouse:
      _mouses[aInput.GetInputSignalCode()] =
        static_cast<const PLAIPTMouse &>(aInput);
      break;
    case PLAInputDeviceType::Keyboard:
      _keys[aInput.GetInputSignalCode()] =
        static_cast<const PLAIPTKey &>(aInput);
      break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "Detected unexpected PLAInputDeviceType.");
      break;
  }
}
