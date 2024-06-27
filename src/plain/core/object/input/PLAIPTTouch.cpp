#include "plain/core/object/input/PLAIPTTouch.hpp"

PLAIPTTouch::PLAIPTTouch(PLAInputSignalCode aCode, PLAInputSignal aSignal,
                         const PLAPoint &aScreenPoint):
  PLAInput(PLAInputDeviceType::Touch, aCode, aSignal),
  _screenPoint(aScreenPoint)
{

}

PLAIPTTouch::~PLAIPTTouch()
{

}
