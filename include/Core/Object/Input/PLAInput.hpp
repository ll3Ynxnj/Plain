#ifndef PLAIN_ENGINE_PLAOBJINPUT_HPP
#define PLAIN_ENGINE_PLAOBJINPUT_HPP

#include <set>
#include <map>
#include <queue>
#include "Core/Object/PLAObject.hpp"
#include "Core/PLAInputType.hpp"
#include "Core/Primitive/PLAPRMPoint.hpp"

class PLAInput : public PLAObject
{
  PLAInputDeviceType _deviceType = PLAInputDeviceType::None;
  PLAInputSignalCode _code = kPLAInputSignalCodeUndefined;
  PLAInputSignal _signal = false;
  PLAPoint _screenPoint = kPLAPointNone;

public:
  /*
  static PLAInput *Create(PLAInputDeviceType aDeviceType, PLAInputCode aCode,
                          PLAInputSignal aSignal, PLAPoint aScreenPoint);
  */
  static PLAInputSignalCode GetCodeForKeyFromChar(unsigned char aCharacter);
  static PLAInputSignalCode GetCodeOfNone(PLAInputDeviceType aType);
  static int GetNumberOfInputCodes(PLAInputDeviceType aDevice);

  PLAInput(PLAInputDeviceType aDevice, PLAInputSignalCode aCode,
           PLAInputSignal aSignal, const PLAPoint &aScreenPoint);
  virtual ~PLAInput();

  PLAInputDeviceType GetInputDeviceType() const { return _deviceType; };
  PLAInputSignalCode GetInputSignalCode() const { return _code; };
  PLAInputSignal GetInputSignal() const { return _signal; };
  PLAPoint GetScreenPoint() const { return _screenPoint; }
};


#endif //PLAIN_ENGINE_PLAOBJINPUT_HPP
