#ifndef PLAIN_ENGINE_PLAOBJECTTYPE_HPP
#define PLAIN_ENGINE_PLAOBJECTTYPE_HPP

#include "PLAType.hpp"

enum class PLAObjectType : int
{
  App,
  Input,
  Stage,
  Actor,
  Shape,
  Style,
  Error,
  Renderer,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif //PLAIN_ENGINE_PLAOBJECTTYPE_HPP
