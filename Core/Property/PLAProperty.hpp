//
// Created by Kentaro Kawai on 2021/09/07.
//

#ifndef ANHR_PLAPROPERTY_HPP
#define ANHR_PLAPROPERTY_HPP

#include "Primitive/PLAPRMType.hpp"
#include "Primitive/PLAPRMColor.hpp"
#include "Primitive/PLAPRMVector.hpp"
#include "PLAPropertyType.hpp"

class PLAProperty
{
public:
  static const PLAProperty kNone;
  static const PLAProperty kBool;
  static const PLAProperty kInt;
  static const PLAProperty kUInt;  // it may be abolished
  static const PLAProperty kFloat;
  static const PLAProperty kColor;
  static const PLAProperty kVec2f;
  static const PLAProperty kVec3f;
  static const PLAProperty kVec4f;
  static const PLAProperty kVec2i;
  static const PLAProperty kVec3i;
  static const PLAProperty kVec4i;
  static const PLAProperty kVec2s; // it may be abolished
  static const PLAProperty kVec3s; // it may be abolished
  static const PLAProperty kVec4s; // it may be abolished

private:
  union Value {
    PLABool b;
    PLAFloat f;
    PLAInt i;
    PLAUInt ui;   // it may be abolished
    PLAColor c;
    PLAVec2f v2f;
    PLAVec3f v3f;
    PLAVec4f v4f;
    PLAVec2i v2i;
    PLAVec3i v3i;
    PLAVec4i v4i;
    PLAVec2s v2s; // it may be abolished
    PLAVec3s v3s; // it may be abolished
    PLAVec4s v4s; // it may be abolished

    Value(): b(0) {};
  };
  PLAPropertyType _type = PLAPropertyType::None;
  Value _value = Value();

public:
  PLAProperty() {};
  PLAProperty(PLAPropertyType aType);
  PLAProperty(PLABool aValue):
    _type(PLAPropertyType::Bool) { _value.b = PLABool(aValue); };
  PLAProperty(PLAInt aValue):
    _type(PLAPropertyType::Int) { _value.i = PLAInt(aValue); };
  PLAProperty(PLAUInt aValue): // it may be abolished
    _type(PLAPropertyType::UInt) { _value.ui = PLAInt(aValue); };
  PLAProperty(PLAFloat aValue):
    _type(PLAPropertyType::Float) { _value.f = PLAFloat(aValue); };
  PLAProperty(PLAColor aValue):
    _type(PLAPropertyType::Color) { _value.c = PLAColor(aValue); };
  PLAProperty(const PLAVec2f &aValue):
    _type(PLAPropertyType::Vec2f) { _value.v2f = PLAVec2f(aValue); };
  PLAProperty(const PLAVec3f &aValue):
    _type(PLAPropertyType::Vec3f) { _value.v3f = PLAVec3f(aValue); };
  PLAProperty(const PLAVec4f &aValue):
    _type(PLAPropertyType::Vec4f) { _value.v4f = PLAVec4f(aValue); };
  PLAProperty(const PLAVec2i &aValue):
    _type(PLAPropertyType::Vec2i) { _value.v2i = PLAVec2i(aValue); };
  PLAProperty(const PLAVec3i &aValue):
    _type(PLAPropertyType::Vec3i) { _value.v3i = PLAVec3i(aValue); };
  PLAProperty(const PLAVec4i &aValue):
    _type(PLAPropertyType::Vec4i) { _value.v4i = PLAVec4i(aValue); };
  PLAProperty(const PLAVec2s &aValue): // it may be abolished
    _type(PLAPropertyType::Vec2s) { _value.v2s = PLAVec2s(aValue); };
  PLAProperty(const PLAVec3s &aValue): // it may be abolished
    _type(PLAPropertyType::Vec3s) { _value.v3s = PLAVec3s(aValue); };
  PLAProperty(const PLAVec4s &aValue): // it may be abolished
    _type(PLAPropertyType::Vec4s) { _value.v4s = PLAVec4s(aValue); };

  ~PLAProperty() {};// delete _value; _value = nullptr; };

  void Print();

  PLAPropertyType GetPropertyType() { return _type; };

  PLABool GetBool() const;
  PLAInt GetInt() const;
  PLAUInt GetUInt() const;          // it may be abolished
  PLAFloat GetFloat() const;
  const PLAColor &GetColor() const;
  const PLAVec2f &GetVec2f() const;
  const PLAVec3f &GetVec3f() const;
  const PLAVec4f &GetVec4f() const;
  const PLAVec2i &GetVec2i() const;
  const PLAVec3i &GetVec3i() const;
  const PLAVec4i &GetVec4i() const;
  const PLAVec2s &GetVec2s() const; // it may be abolished
  const PLAVec3s &GetVec3s() const; // it may be abolished
  const PLAVec4s &GetVec4s() const; // it may be abolished

  void Set(const PLAProperty &aProperty);

  void SetBool(PLABool aValue);
  void SetInt(PLAInt aValue);
  void SetUInt(PLAUInt aValue);          // it may be abolished
  void SetFloat(PLAFloat aValue);
  void SetColor(const PLAColor &aValue);
  void SetVec2f(const PLAVec2f &aValue);
  void SetVec3f(const PLAVec3f &aValue);
  void SetVec4f(const PLAVec4f &aValue);
  void SetVec2i(const PLAVec2i &aValue);
  void SetVec3i(const PLAVec3i &aValue);
  void SetVec4i(const PLAVec4i &aValue);
  void SetVec2s(const PLAVec2s &aValue); // it may be abolished
  void SetVec3s(const PLAVec3s &aValue); // it may be abolished
  void SetVec4s(const PLAVec4s &aValue); // it may be abolished


  /// Operators for addition ///////////////////////////////////////////////////

  PLAProperty operator +(const PLAProperty &aProperty) const;

  PLAProperty operator +(PLAInt aValue) const;
  PLAProperty operator +(PLAUInt aValue) const;         // it may be abolished
  PLAProperty operator +(PLAFloat aValue) const;
  PLAProperty operator +(const PLAVec2f &aValue) const;
  PLAProperty operator +(const PLAVec3f &aValue) const;
  PLAProperty operator +(const PLAVec4f &aValue) const;
  PLAProperty operator +(const PLAVec2i &aValue) const;
  PLAProperty operator +(const PLAVec3i &aValue) const;
  PLAProperty operator +(const PLAVec4i &aValue) const;
  PLAProperty operator +(const PLAVec2s &aValue) const; // it may be abolished
  PLAProperty operator +(const PLAVec3s &aValue) const; // it may be abolished
  PLAProperty operator +(const PLAVec4s &aValue) const; // it may be abolished

  void operator +=(const PLAProperty &aProperty);

  void operator +=(PLAInt aValue);
  void operator +=(PLAUInt aValue);         // it may be abolished
  void operator +=(PLAFloat aValue);
  void operator +=(const PLAVec2f &aValue);
  void operator +=(const PLAVec3f &aValue);
  void operator +=(const PLAVec4f &aValue);
  void operator +=(const PLAVec2i &aValue);
  void operator +=(const PLAVec3i &aValue);
  void operator +=(const PLAVec4i &aValue);
  void operator +=(const PLAVec2s &aValue); // it may be abolished
  void operator +=(const PLAVec3s &aValue); // it may be abolished
  void operator +=(const PLAVec4s &aValue); // it may be abolished


  /// Operators for subtraction ////////////////////////////////////////////////

  PLAProperty operator -(const PLAProperty &aProperty) const;

  PLAProperty operator -(PLAInt aValue) const;
  PLAProperty operator -(PLAUInt aValue) const;         // it may be abolished
  PLAProperty operator -(PLAFloat aValue) const;
  PLAProperty operator -(const PLAVec2f &aValue) const;
  PLAProperty operator -(const PLAVec3f &aValue) const;
  PLAProperty operator -(const PLAVec4f &aValue) const;
  PLAProperty operator -(const PLAVec2i &aValue) const;
  PLAProperty operator -(const PLAVec3i &aValue) const;
  PLAProperty operator -(const PLAVec4i &aValue) const;
  PLAProperty operator -(const PLAVec2s &aValue) const; // it may be abolished
  PLAProperty operator -(const PLAVec3s &aValue) const; // it may be abolished
  PLAProperty operator -(const PLAVec4s &aValue) const; // it may be abolished

  void operator -=(const PLAProperty &aProperty);

  void operator -=(PLAInt aValue);
  void operator -=(PLAUInt aValue);         // it may be abolished
  void operator -=(PLAFloat aValue);
  void operator -=(const PLAVec2f &aValue);
  void operator -=(const PLAVec3f &aValue);
  void operator -=(const PLAVec4f &aValue);
  void operator -=(const PLAVec2i &aValue);
  void operator -=(const PLAVec3i &aValue);
  void operator -=(const PLAVec4i &aValue);
  void operator -=(const PLAVec2s &aValue); // it may be abolished
  void operator -=(const PLAVec3s &aValue); // it may be abolished
  void operator -=(const PLAVec4s &aValue); // it may be abolished


  /// Operators for multiplication /////////////////////////////////////////////

  PLAProperty operator *(const PLAProperty &aProperty) const;

  PLAProperty operator *(PLAInt aValue) const;
  PLAProperty operator *(PLAUInt aValue) const;   // it may be abolished
  PLAProperty operator *(PLAFloat aValue) const;

  void operator *=(const PLAProperty &aProperty);

  void operator *=(PLAInt aValue);
  void operator *=(PLAUInt aValue);               // it may be abolished
  void operator *=(PLAFloat aValue);


  /// Operators for division ///////////////////////////////////////////////////

  PLAProperty operator /(const PLAProperty &aProperty) const;

  PLAProperty operator /(PLAInt aValue) const;
  PLAProperty operator /(PLAUInt aValue) const;   // it may be abolished
  PLAProperty operator /(PLAFloat aValue) const;

  void operator /=(const PLAProperty &aProperty);

  void operator /=(PLAInt aValue);
  void operator /=(PLAUInt aValue);               // it may be abolished
  void operator /=(PLAFloat aValue);
};

#endif //ANHR_PLAPROPERTY_HPP
