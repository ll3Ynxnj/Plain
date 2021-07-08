#ifndef PLAIN_ENGINE_PLAOBJECTTYPE_HPP
#define PLAIN_ENGINE_PLAOBJECTTYPE_HPP

#include "Plain.h"

enum class PLAObjectType : PLAInt
{
  App,
  Input,
  Scene,
  Stage,
  Actor,
  Layer,
  Style,
  Image,
  Error,
  Resource,
  Renderer,
  ImageClip,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif //PLAIN_ENGINE_PLAOBJECTTYPE_HPP
