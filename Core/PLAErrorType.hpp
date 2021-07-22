#ifndef PLAIN_ENGINE_PLAERRORTYPE_HPP
#define PLAIN_ENGINE_PLAERRORTYPE_HPP

#include "Type/PLAVector.hpp"

enum class PLAErrorType : PLAInt
{
  Assert,
  Expect,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLAERRORTYPE_HPP
