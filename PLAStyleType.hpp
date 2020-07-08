#ifndef PLAIN_PLASTYLETYPE_HPP
#define PLAIN_PLASTYLETYPE_HPP

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

#endif // PLAIN_PLASTYLETYPE_HPP
