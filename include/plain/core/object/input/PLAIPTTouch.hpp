#ifndef PLAIN_PLAIPTTOUCH_HPP
#define PLAIN_PLAIPTTOUCH_HPP

#include "plain/core/object/input/PLAInput.hpp"
#include "plain/core/primitive/PLAPRMPoint.hpp"

class PLAIPTTouch: public PLAInput
{
  PLAPoint _screenPoint = kPLAPointNone;

public:
  PLAIPTTouch(PLAInputSignalCode aCode, PLAInputSignal aSignal,
              const PLAPoint &aScreenPoint);
  ~PLAIPTTouch();

  PLAPoint GetScreenPoint() const { return _screenPoint; }
};

#endif //PLAIN_PLAIPTTOUCH_HPP
