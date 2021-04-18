#ifndef PLAIN_ENGINE_PLALAYERTYPE_HPP
#define PLAIN_ENGINE_PLALAYERTYPE_HPP

#include "PLAType.hpp"

enum class PLALayerType : int
{
  Point,
  Line,
  Rect,
  Circle,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLALAYERTYPE_HPP
