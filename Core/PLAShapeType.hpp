#ifndef PLAIN_ENGINE_PLASHAPETYPE_HPP
#define PLAIN_ENGINE_PLASHAPETYPE_HPP

#include "PLAType.hpp"

enum class PLAShapeType : int
{
  Point,
  Line,
  Rect,
  Circle,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLASHAPETYPE_HPP
