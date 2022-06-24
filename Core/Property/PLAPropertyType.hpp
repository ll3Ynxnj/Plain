//
// Created by Kentaro Kawai on 2021/09/07.
//

#ifndef ANHR_PLAPROPERTYTYPE_HPP
#define ANHR_PLAPROPERTYTYPE_HPP

#include "Primitive/PLAPRMType.hpp"

enum class PLAPropertyType: PLAInt {
  Bool,
  Int,
  Float,
  Color,
  Vec2,
  Vec3,
  Vec4,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif //ANHR_PLAPROPERTYTYPE_HPP
