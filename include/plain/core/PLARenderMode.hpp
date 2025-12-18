#ifndef PLAIN_ENGINE_PLARENDERMODE_HPP
#define PLAIN_ENGINE_PLARENDERMODE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"

enum class PLARenderMode : PLAInt
{
  Nearest,
  Linear,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLARENDERMODE_HPP
