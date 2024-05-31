#ifndef PLAIN_PLAACTORCOLLISIONCODE_HPP
#define PLAIN_PLAACTORCOLLISIONCODE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"

enum class PLAActorCollisionCode : PLAInt
{
  Input,
  Actor,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif //PLAIN_PLAACTORCOLLISIONCODE_HPP
