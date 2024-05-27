#ifndef PLAIN_ENGINE_PLAOBJLAYERTYPE_HPP
#define PLAIN_ENGINE_PLAOBJLAYERTYPE_HPP

#include "Core/Primitive/PLAPRMVector.hpp"

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

#endif // PLAIN_ENGINE_PLAOBJLAYERTYPE_HPP
