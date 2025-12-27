#ifndef PLAIN_ENGINE_PLASTROKEJOINTYPE_HPP
#define PLAIN_ENGINE_PLASTROKEJOINTYPE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"

enum class PLAStrokeJoinType : PLAInt
{
  Miter,
  Round,
  Bevel,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLASTROKEJOINTYPE_HPP
