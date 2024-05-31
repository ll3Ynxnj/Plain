#ifndef PLAIN_ENGINE_PLAOBJERRORTYPE_HPP
#define PLAIN_ENGINE_PLAOBJERRORTYPE_HPP

#include "plain/core/primitive/PLAPRMVector.hpp"

enum class PLAErrorType : PLAInt
{
  Assert,
  Expect,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLAOBJERRORTYPE_HPP
