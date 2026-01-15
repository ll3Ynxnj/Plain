// Copyright (c) 2024. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLATEXTALIGNMENT_HPP
#define PLAIN_ENGINE_PLATEXTALIGNMENT_HPP

#include "plain/core/primitive/PLAPRMType.hpp"

enum class PLATextAlignment : PLAInt
{
  Left,
  Center,
  Right,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLATEXTALIGNMENT_HPP
