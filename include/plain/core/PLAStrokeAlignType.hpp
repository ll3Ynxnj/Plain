#ifndef PLAIN_ENGINE_PLASTROKEALIGNTYPE_HPP
#define PLAIN_ENGINE_PLASTROKEALIGNTYPE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"

enum class PLAStrokeAlignType : PLAInt
{
  Inside,
  Center,
  Outside,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLASTROKEALIGNTYPE_HPP
