#ifndef PLAIN_ENGINE_PLASTYLETYPE_HPP
#define PLAIN_ENGINE_PLASTYLETYPE_HPP

#include "Plain.hpp"

enum class PLAStyleType : int
{
  FillColor,
  //FillImage,
  StrokeColor,
  StrokeWidth,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLASTYLETYPE_HPP
