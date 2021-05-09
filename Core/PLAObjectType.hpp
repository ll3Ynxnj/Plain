#ifndef PLAIN_ENGINE_PLAOBJECTTYPE_HPP
#define PLAIN_ENGINE_PLAOBJECTTYPE_HPP

#include "PLAType.hpp"

enum class PLAObjectType : GRAInt
{
  App,
  Input,
  Scene,
  Stage,
  Actor,
  Layer,
  Style,
  Error,
  Resource,
  Renderer,
  ImageClip,

  kNumberOfItems,
  None = kGRAIntUndefined,
};

#endif //PLAIN_ENGINE_PLAOBJECTTYPE_HPP
