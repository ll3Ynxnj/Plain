//
// Created by Kentaro Kawai on 2021/09/07.
//

#ifndef ANHR_PLAPROPERTY_HPP
#define ANHR_PLAPROPERTY_HPP

#include "Type/PLAType.hpp"
#include "Type/PLAColor.hpp"
#include "Type/PLAVector.hpp"
#include "PLAPropertyType.hpp"

class PLAProperty
{
  PLAPropertyType _type = PLAPropertyType::None;
  void *_value = nullptr;

public:
  PLAProperty() {};
  PLAProperty(PLAPropertyType aType): _type(aType) {};
  PLAProperty(PLABool aValue):
    _type(PLAPropertyType::Bool), _value(new PLABool(aValue)) {};
  PLAProperty(PLAInt aValue):
    _type(PLAPropertyType::Int), _value(new PLAInt(aValue)) {};
  PLAProperty(PLAFloat aValue):
    _type(PLAPropertyType::Float), _value(new PLAFloat(aValue)) {};
  PLAProperty(PLAColor aValue):
    _type(PLAPropertyType::Color), _value(new PLAColor(aValue)) {};
  PLAProperty(const PLAString &aValue):
    _type(PLAPropertyType::String), _value(new PLAString(aValue)) {};
  PLAProperty(const PLAVec2 &aValue):
    _type(PLAPropertyType::Vec2), _value(new PLAVec2(aValue)) {};
  PLAProperty(const PLAVec3 &aValue):
    _type(PLAPropertyType::Vec3), _value(new PLAVec3(aValue)) {};
  PLAProperty(const PLAVec4 &aValue):
    _type(PLAPropertyType::Vec4), _value(new PLAVec4(aValue)) {};

  ~PLAProperty() { delete _value; _value = nullptr; };

  PLABool GetBool() const;
  PLAInt GetInt() const;
  PLAFloat GetFloat() const;
  const PLAColor &GetColor() const;
  const PLAString &GetString() const;
  const PLAVec2 &GetVec2() const;
  const PLAVec3 &GetVec3() const;
  const PLAVec4 &GetVec4() const;

  void SetBool(PLABool aValue);
  void SetInt(PLAInt aValue);
  void SetFloat(PLAFloat aValue);
  void SetColor(const PLAColor &aValue);
  void SetString(const PLAString &aValue);
  void SetVec2(const PLAVec2 &aValue);
  void SetVec3(const PLAVec3 &aValue);
  void SetVec4(const PLAVec4 &aValue);
};

#endif //ANHR_PLAPROPERTY_HPP
