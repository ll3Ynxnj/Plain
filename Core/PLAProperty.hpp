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

  void Set(const PLAProperty &aProperty);

  void SetBool(PLABool aValue);
  void SetInt(PLAInt aValue);
  void SetFloat(PLAFloat aValue);
  void SetColor(const PLAColor &aValue);
  void SetString(const PLAString &aValue);
  void SetVec2(const PLAVec2 &aValue);
  void SetVec3(const PLAVec3 &aValue);
  void SetVec4(const PLAVec4 &aValue);

  void Add(const PLAProperty &aProperty);

  //void AddBool(PLABool aValue);
  void AddInt(PLAInt aValue);
  void AddFloat(PLAFloat aValue);
  //void AddColor(const PLAColor &aValue);
  void AddString(const PLAString &aValue);
  void AddVec2(const PLAVec2 &aValue);
  void AddVec3(const PLAVec3 &aValue);
  void AddVec4(const PLAVec4 &aValue);

};

//static const PLAProperty kPLAPropertyNone = PLAProperty();
static const PLAProperty kPLAPropertyBool = PLAProperty(PLABool(false));
static const PLAProperty kPLAPropertyInt = PLAProperty(PLAInt(0));
static const PLAProperty kPLAPropertyFloat = PLAProperty(PLAFloat(0));
static const PLAProperty kPLAPropertyColor = PLAProperty(kPLAColorNorm);
static const PLAProperty kPLAPropertyString = PLAProperty(PLAString(""));
static const PLAProperty kPLAPropertyVec2 = PLAProperty(kPLAVec2None);
static const PLAProperty kPLAPropertyVec3 = PLAProperty(kPLAVec3None);
static const PLAProperty kPLAPropertyVec4 = PLAProperty(kPLAVec4None);

#endif //ANHR_PLAPROPERTY_HPP
