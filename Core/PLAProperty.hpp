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
public:
  static const PLAProperty kBool;
  static const PLAProperty kInt;
  static const PLAProperty kFloat;
  static const PLAProperty kColor;
  static const PLAProperty kVec2;
  static const PLAProperty kVec3;
  static const PLAProperty kVec4;

private:
  union Value {
    PLABool b;
    PLAFloat f;
    PLAInt i;
    PLAColor c;
    PLAVec2 v2;
    PLAVec3 v3;
    PLAVec4 v4;

    Value(): b(0) {};
  };
  PLAPropertyType _type = PLAPropertyType::None;
  Value _value;

public:
  PLAProperty() {};
  PLAProperty(PLAPropertyType aType): _type(aType) {};
  PLAProperty(PLABool aValue):
    _type(PLAPropertyType::Bool) { _value.b = PLABool(aValue); };
  PLAProperty(PLAInt aValue):
    _type(PLAPropertyType::Int) { _value.i = PLAInt(aValue); };
  PLAProperty(PLAFloat aValue):
    _type(PLAPropertyType::Float) { _value.f = PLAFloat(aValue); };
  PLAProperty(PLAColor aValue):
    _type(PLAPropertyType::Color) { _value.c = PLAColor(aValue); };
  PLAProperty(const PLAVec2 &aValue):
    _type(PLAPropertyType::Vec2) { _value.v2 = PLAVec2(aValue); };
  PLAProperty(const PLAVec3 &aValue):
    _type(PLAPropertyType::Vec3) { _value.v3 = PLAVec3(aValue); };
  PLAProperty(const PLAVec4 &aValue):
    _type(PLAPropertyType::Vec4) { _value.v4 = PLAVec4(aValue); };

  ~PLAProperty() {};// delete _value; _value = nullptr; };

  PLABool GetBool() const;
  PLAInt GetInt() const;
  PLAFloat GetFloat() const;
  const PLAColor &GetColor() const;
  const PLAVec2 &GetVec2() const;
  const PLAVec3 &GetVec3() const;
  const PLAVec4 &GetVec4() const;

  void Set(const PLAProperty &aProperty);

  void SetBool(PLABool aValue);
  void SetInt(PLAInt aValue);
  void SetFloat(PLAFloat aValue);
  void SetColor(const PLAColor &aValue);
  //void SetString(const PLAString &aValue);
  void SetVec2(const PLAVec2 &aValue);
  void SetVec3(const PLAVec3 &aValue);
  void SetVec4(const PLAVec4 &aValue);

  void Add(const PLAProperty &aProperty);

  void AddInt(PLAInt aValue);
  void AddFloat(PLAFloat aValue);
  void AddString(const PLAString &aValue);
  void AddVec2(const PLAVec2 &aValue);
  void AddVec3(const PLAVec3 &aValue);
  void AddVec4(const PLAVec4 &aValue);
};

#endif //ANHR_PLAPROPERTY_HPP
