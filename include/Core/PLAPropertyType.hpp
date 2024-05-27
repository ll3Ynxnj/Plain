//
// Created by Kentaro Kawai on 2021/09/07.
//

#ifndef ANHR_PLAPROPERTYTYPE_HPP
#define ANHR_PLAPROPERTYTYPE_HPP

#include "Core/Primitive/PLAPRMType.hpp"

enum class PLAPropertyType: PLAInt {
  Bool,
  Int,
  UInt,
  Float,
  Color,
  Vec2f,
  Vec3f,
  Vec4f,
  Vec2i,
  Vec3i,
  Vec4i,
  Vec2s,
  Vec3s,
  Vec4s,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif //ANHR_PLAPROPERTYTYPE_HPP
