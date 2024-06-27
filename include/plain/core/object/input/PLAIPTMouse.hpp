#ifndef PLAIN_PLAIPTMOUSE_HPP
#define PLAIN_PLAIPTMOUSE_HPP

#include "plain/core/object/input/PLAInput.hpp"
#include "plain/core/primitive/PLAPRMPoint.hpp"

class PLAIPTMouse: public PLAInput
{
  PLAPoint _screenPoint = kPLAPointNone;

public:
  PLAIPTMouse(PLAInputSignalCode aCode, PLAInputSignal aSignal,
              const PLAPoint &aScreenPoint);
  ~PLAIPTMouse();

  PLAPoint GetScreenPoint() const { return _screenPoint; }
};

#endif //PLAIN_PLAIPTMOUSE_HPP
