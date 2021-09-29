//
// Created by Kentaro Kawai on 2021/09/07.
//

#ifndef ANHR_PLAPROPERTYTYPE_HPP
#define ANHR_PLAPROPERTYTYPE_HPP

#include "Type/PLAType.hpp"

enum class PLAPropertyType: PLAInt {
  Bool,
  Int,
  Float,
  String,
  Vec2,
  Vec3,
  Vec4,
  Color,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif //ANHR_PLAPROPERTYTYPE_HPP