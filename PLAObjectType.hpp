#ifndef PLAIN_ENGINE_PLAOBJECTTYPE_HPP
#define PLAIN_ENGINE_PLAOBJECTTYPE_HPP

#include "Plain.hpp"

enum class PLAObjectType : int
{
  App,
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
