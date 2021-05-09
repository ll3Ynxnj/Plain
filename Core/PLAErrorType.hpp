#ifndef PLAIN_ENGINE_PLAERRORTYPE_HPP
#define PLAIN_ENGINE_PLAERRORTYPE_HPP

#include "PLAType.hpp"

enum class PLAErrorType : GRAInt
{
  Assert,
  Expect,

  kNumberOfItems,
  None = kGRAIntUndefined,
};

#endif // PLAIN_ENGINE_PLAERRORTYPE_HPP
