#ifndef PLAIN_ENGINE_PLALAYERTYPE_HPP
#define PLAIN_ENGINE_PLALAYERTYPE_HPP

#include "Primitive/PLAVector.hpp"

enum class PLALayerType : PLAInt
{
  Point,
  Line,
  Rect,
  Circle,
  Tile,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLALAYERTYPE_HPP
