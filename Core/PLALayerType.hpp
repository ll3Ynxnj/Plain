#ifndef PLAIN_ENGINE_PLALAYERTYPE_HPP
#define PLAIN_ENGINE_PLALAYERTYPE_HPP

#include "PLAType.hpp"

enum class PLALayerType : GRAInt
{
  Point,
  Line,
  Rect,
  Circle,

  kNumberOfItems,
  None = kGRAIntUndefined,
};

#endif // PLAIN_ENGINE_PLALAYERTYPE_HPP
