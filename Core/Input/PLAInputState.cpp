//
// Created by Kentaro Kawai on 2022/05/13.
//

#include "PLAInputState.hpp"
#include "Class/PLAError.hpp"

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
  return this->GetInput(aInput.GetInputDeviceType(), aInput.GetInputSignalCode());
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
  _inputs[device][aInput.GetInputSignalCode()] = aInput;
}
