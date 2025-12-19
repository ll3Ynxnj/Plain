// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAFONTRASTERIZERTYPE_HPP
#define PLAIN_ENGINE_PLAFONTRASTERIZERTYPE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"

enum class PLAFontRasterizerType : PLAInt
{
  OpenCV,
  FreeType,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLAFONTRASTERIZERTYPE_HPP
