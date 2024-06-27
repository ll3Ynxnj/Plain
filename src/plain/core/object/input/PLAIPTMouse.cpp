#include "plain/core/object/input/PLAIPTMouse.hpp"

PLAIPTMouse::PLAIPTMouse(PLAInputSignalCode aCode, PLAInputSignal aSignal,
                         const PLAPoint &aScreenPoint):
  PLAInput(PLAInputDeviceType::Mouse, aCode, aSignal),
  _screenPoint(aScreenPoint)
{

}

PLAIPTMouse::~PLAIPTMouse()
{

}
