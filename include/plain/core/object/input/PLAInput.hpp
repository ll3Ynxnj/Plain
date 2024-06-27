#ifndef PLAIN_PLAOBJINPUT_HPP
#define PLAIN_PLAOBJINPUT_HPP

#include <set>
#include <map>
#include <queue>
#include "plain/core/PLAInputType.hpp"
#include "plain/core/primitive/PLAPRMPoint.hpp"

class PLAInput
{
  PLAInputDeviceType _deviceType = PLAInputDeviceType::None;
  PLAInputSignalCode _code = kPLAInputSignalCodeUndefined;
  PLAInputSignal _signal = false;

protected:
  PLAInput(PLAInputDeviceType aDevice, PLAInputSignalCode aCode,
           PLAInputSignal aSignal);

public:
  virtual ~PLAInput();
  /*
  static PLAInput *Create(PLAInputDeviceType aDeviceType, PLAInputCode aCode,
                          PLAInputSignal aSignal, PLAPoint aScreenPoint);
  */
  static PLAInputSignalCode GetCodeForKeyFromChar(unsigned char aCharacter);
  static PLAInputSignalCode GetCodeOfNone(PLAInputDeviceType aType);
  static int GetNumberOfInputCodes(PLAInputDeviceType aDevice);

  PLAInputDeviceType GetInputDeviceType() const { return _deviceType; };
  PLAInputSignalCode GetInputSignalCode() const { return _code; };
  PLAInputSignal GetInputSignal() const { return _signal; };
};


#endif //PLAIN_PLAOBJINPUT_HPP
