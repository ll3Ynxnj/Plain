// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLADECODERTYPE_HPP
#define PLAIN_ENGINE_PLADECODERTYPE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"

enum class PLADecoderType : PLAInt
{
  Image,
  Audio,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLADECODERTYPE_HPP
