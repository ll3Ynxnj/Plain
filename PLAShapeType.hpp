#ifndef PLAIN_PLASHAPETYPE_HPP
#define PLAIN_PLASHAPETYPE_HPP

#include "Plain.hpp"

enum class PLAShapeType : int
{
  Point,
  Line,
  Rect,
  Circle,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_PLASHAPETYPE_HPP
