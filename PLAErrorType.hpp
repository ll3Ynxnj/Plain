#ifndef PLAIN_PLAERRORTYPE_HPP
#define PLAIN_PLAERRORTYPE_HPP

#include "Plain.hpp"

enum class PLAErrorType : int
{
  Assert,
  Expect,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_PLAERRORTYPE_HPP
