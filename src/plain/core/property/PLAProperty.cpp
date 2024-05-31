//
// Created by Kentaro Kawai on 2021/09/07.
//

#include "plain/core/property/PLAProperty.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include <grain/grain.h>

const PLAProperty PLAProperty::kNone  = PLAProperty();
const PLAProperty PLAProperty::kBool  = PLAProperty(PLABool(false));
const PLAProperty PLAProperty::kInt   = PLAProperty(PLAInt(0));
const PLAProperty PLAProperty::kFloat = PLAProperty(PLAFloat(0));
const PLAProperty PLAProperty::kColor = PLAProperty(kPLAColorNorm);
const PLAProperty PLAProperty::kVec2f = PLAProperty(kPLAVec2fNone);
const PLAProperty PLAProperty::kVec3f = PLAProperty(kPLAVec3fNone);
const PLAProperty PLAProperty::kVec4f = PLAProperty(kPLAVec4fNone);
const PLAProperty PLAProperty::kVec2i = PLAProperty(kPLAVec2iNone);
const PLAProperty PLAProperty::kVec3i = PLAProperty(kPLAVec3iNone);
const PLAProperty PLAProperty::kVec4i = PLAProperty(kPLAVec4iNone);
const PLAProperty PLAProperty::kVec2s = PLAProperty(kPLAVec2sNone);
const PLAProperty PLAProperty::kVec3s = PLAProperty(kPLAVec3sNone);
const PLAProperty PLAProperty::kVec4s = PLAProperty(kPLAVec4sNone);

void PLAProperty::Print()
{
  GRA_PRINT("PLAProperty: {");
  switch(_type)
  {
    case PLAPropertyType::Bool :
      GRA_PRINT("Bool: %s", this->GetBool()?"true":"false");
      break;
    case PLAPropertyType::Int :
      GRA_PRINT("Int: %d", this->GetInt());
      break;
    case PLAPropertyType::UInt : // it may be abolished
      GRA_PRINT("UInt: %u", this->GetUInt());
      break;
    case PLAPropertyType::Float :
      GRA_PRINT("Float: %f", this->GetFloat());
      break;
    case PLAPropertyType::Color :
      GRA_PRINT("Color: {r: %f, g: %f, b: %f, a: %f}",
                this->GetColor().r, this->GetColor().g,
                this->GetColor().b, this->GetColor().a);
      break;
    case PLAPropertyType::Vec2f :
    {
      GRA_PRINT("Vec2: {x: %f, y: %f}", this->GetVec2f().x, this->GetVec2f().y);
      break;
    }
    case PLAPropertyType::Vec3f :
    {
      GRA_PRINT("Vec3: {x: %f, y: %f, z: %f}",
                this->GetVec3f().x, this->GetVec3f().y, this->GetVec3f().z);
      break;
    }
    case PLAPropertyType::Vec4f :
    {
      GRA_PRINT("Vec4: {x: %f, y: %f, z: %f, w: %f}",
                this->GetVec4f().x, this->GetVec4f().y,
                this->GetVec4f().z, this->GetVec4f().w);
      break;
    }
    case PLAPropertyType::Vec2i :
    {
      GRA_PRINT("Vec2i: {x: %d, y: %d}", this->GetVec2i().x, this->GetVec2i().y);
      break;
    }
    case PLAPropertyType::Vec3i :
    {
      GRA_PRINT("Vec3i: {x: %d, y: %d, z: %d}",
                this->GetVec3i().x, this->GetVec3i().y, this->GetVec3i().z);
      break;
    }
    case PLAPropertyType::Vec4i :
    {
      GRA_PRINT("Vec4i: {x: %d, y: %d, z: %d, w: %d}",
                this->GetVec4i().x, this->GetVec4i().y,
                this->GetVec4i().z, this->GetVec4i().w);
      break;
    }
    case PLAPropertyType::Vec2s : // it may be abolished
    {
      GRA_PRINT("Vec2s: {x: %d, y: %d}", this->GetVec2s().x, this->GetVec2s().y);
      break;
    }
    case PLAPropertyType::Vec3s : // it may be abolished
    {
      GRA_PRINT("Vec3s: {x: %d, y: %d, z: %d}",
                this->GetVec3s().x, this->GetVec3s().y, this->GetVec3s().z);
      break;
    }
    case PLAPropertyType::Vec4s : // it may be abolished
    {
      GRA_PRINT("Vec4s: {x: %d, y: %d, z: %d, w: %d}",
                this->GetVec4s().x, this->GetVec4s().y,
                this->GetVec4s().z, this->GetVec4s().w);
      break;
    }
    case PLAPropertyType::None :
      GRA_PRINT("None");
      break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Detected unexpected PLAPropertyType.");
  }
  GRA_PRINT("}\n");
}

PLAProperty::PLAProperty(PLAPropertyType aType): _type(aType)
{
  switch (aType)
  {
    case PLAPropertyType::None  :                            break;
    case PLAPropertyType::Bool  : _value.b  = false;         break;
    case PLAPropertyType::Int   : _value.i  = 0;             break;
    case PLAPropertyType::UInt  : _value.ui = 0;             break;
    case PLAPropertyType::Float : _value.f  = 0;             break;
    case PLAPropertyType::Color : _value.c  = kPLAColorNorm; break;
    case PLAPropertyType::Vec2f : _value.v2f = kPLAVec2fNone;  break;
    case PLAPropertyType::Vec3f : _value.v3f = kPLAVec3fNone;  break;
    case PLAPropertyType::Vec4f : _value.v4f = kPLAVec4fNone;  break;
    case PLAPropertyType::Vec2i : _value.v2i = kPLAVec2iNone;  break;
    case PLAPropertyType::Vec3i : _value.v3i = kPLAVec3iNone;  break;
    case PLAPropertyType::Vec4i : _value.v4i = kPLAVec4iNone;  break;
    case PLAPropertyType::Vec2s : _value.v2s = kPLAVec2sNone;  break;
    case PLAPropertyType::Vec3s : _value.v3s = kPLAVec3sNone;  break;
    case PLAPropertyType::Vec4s : _value.v4s = kPLAVec4sNone;  break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
  }
}

PLABool PLAProperty::GetBool() const
{
  if (_type != PLAPropertyType::Bool)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLABool type."); }
  return _value.b;
}

PLAInt PLAProperty::GetInt() const
{
  if (_type != PLAPropertyType::Int)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAInt type."); }
  return _value.i;
}

PLAUInt PLAProperty::GetUInt() const
{
  if (_type != PLAPropertyType::UInt)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAUInt type."); }
  return _value.ui;
}

PLAFloat PLAProperty::GetFloat() const
{
  if (_type != PLAPropertyType::Float)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAFloat type."); }
  return _value.f;
}

const PLAColor &PLAProperty::GetColor() const
{
  if (_type != PLAPropertyType::Color)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAColor type."); }
  return _value.c;
}

const PLAVec2f &PLAProperty::GetVec2f() const
{
  if (_type != PLAPropertyType::Vec2f)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec2f type."); }
  return _value.v2f;
}

const PLAVec3f &PLAProperty::GetVec3f() const
{
  if (_type != PLAPropertyType::Vec3f)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec3f type."); }
  return _value.v3f;
}

const PLAVec4f &PLAProperty::GetVec4f() const
{
  if (_type != PLAPropertyType::Vec4f)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec4f type."); }
  return _value.v4f;
}

const PLAVec2i &PLAProperty::GetVec2i() const
{
  if (_type != PLAPropertyType::Vec2i)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec2i type."); }
  return _value.v2i;
}

const PLAVec3i &PLAProperty::GetVec3i() const
{
  if (_type != PLAPropertyType::Vec3i)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec3i type."); }
  return _value.v3i;
}

const PLAVec4i &PLAProperty::GetVec4i() const
{
  if (_type != PLAPropertyType::Vec4i)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec4i type."); }
  return _value.v4i;
}

const PLAVec2s &PLAProperty::GetVec2s() const
{
  if (_type != PLAPropertyType::Vec2s)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec2s type."); }
  return _value.v2s;
}

const PLAVec3s &PLAProperty::GetVec3s() const
{
  if (_type != PLAPropertyType::Vec3s)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec3s type."); }
  return _value.v3s;
}

const PLAVec4s &PLAProperty::GetVec4s() const
{
  if (_type != PLAPropertyType::Vec4s)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec4s type."); }
  return _value.v4s;
}

void PLAProperty::Set(const PLAProperty &aProperty)
{
  switch (aProperty._type)
  {
    case PLAPropertyType::Bool  : SetBool(aProperty.GetBool());   break;
    case PLAPropertyType::Int   : SetInt(aProperty.GetInt());     break;
    case PLAPropertyType::UInt  : SetUInt(aProperty.GetUInt());   break;
    case PLAPropertyType::Float : SetFloat(aProperty.GetFloat()); break;
    case PLAPropertyType::Color : SetColor(aProperty.GetColor()); break;
    case PLAPropertyType::Vec2f : SetVec2f(aProperty.GetVec2f()); break;
    case PLAPropertyType::Vec3f : SetVec3f(aProperty.GetVec3f()); break;
    case PLAPropertyType::Vec4f : SetVec4f(aProperty.GetVec4f()); break;
    case PLAPropertyType::Vec2i : SetVec2i(aProperty.GetVec2i()); break;
    case PLAPropertyType::Vec3i : SetVec3i(aProperty.GetVec3i()); break;
    case PLAPropertyType::Vec4i : SetVec4i(aProperty.GetVec4i()); break;
    case PLAPropertyType::Vec2s : SetVec2s(aProperty.GetVec2s()); break;
    case PLAPropertyType::Vec3s : SetVec3s(aProperty.GetVec3s()); break;
    case PLAPropertyType::Vec4s : SetVec4s(aProperty.GetVec4s()); break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      break;
  }
}

void PLAProperty::SetBool(PLABool aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Bool; }
  if (_type != PLAPropertyType::Bool)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLABool type.");
  }
  _value.b = aValue;
}

void PLAProperty::SetInt(PLAInt aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Int; }
  if (_type != PLAPropertyType::Int)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAInt type.");
  }
  _value.i = aValue;
}

void PLAProperty::SetUInt(PLAUInt aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::UInt; }
  if (_type != PLAPropertyType::UInt)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAUInt type.");
  }
  _value.ui = aValue;
}

void PLAProperty::SetFloat(PLAFloat aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Float; }
  if (_type != PLAPropertyType::Float)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAFloat type.");
  }
  _value.f = aValue;
}

void PLAProperty::SetColor(const PLAColor &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Color; }
  if (_type != PLAPropertyType::Color)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAColor type.");
  }
  _value.c = aValue;
}

void PLAProperty::SetVec2f(const PLAVec2f &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec2f; }
  if (_type != PLAPropertyType::Vec2f)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec2f type.");
  }
  _value.v2f = aValue;
}

void PLAProperty::SetVec3f(const PLAVec3f &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec3f; }
  if (_type != PLAPropertyType::Vec3f)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec3f type.");
  }
  _value.v3f = aValue;
}

void PLAProperty::SetVec4f(const PLAVec4f &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec4f; }
  if (_type != PLAPropertyType::Vec4f)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec4f type.");
  }
  _value.v4f = aValue;
}

void PLAProperty::SetVec2i(const PLAVec2i &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec2i; }
  if (_type != PLAPropertyType::Vec2i)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec2i type.");
  }
  _value.v2i = aValue;
}

void PLAProperty::SetVec3i(const PLAVec3i &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec3i; }
  if (_type != PLAPropertyType::Vec3i)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec3i type.");
  }
  _value.v3i = aValue;
}

void PLAProperty::SetVec4i(const PLAVec4i &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec4i; }
  if (_type != PLAPropertyType::Vec4i)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec4i type.");
  }
  _value.v4i = aValue;
}

void PLAProperty::SetVec2s(const PLAVec2s &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec2s; }
  if (_type != PLAPropertyType::Vec2s)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec2s type.");
  }
  _value.v2s = aValue;
}

void PLAProperty::SetVec3s(const PLAVec3s &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec3s; }
  if (_type != PLAPropertyType::Vec3s)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec3s type.");
  }
  _value.v3s = aValue;
}

void PLAProperty::SetVec4s(const PLAVec4s &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec4s; }
  if (_type != PLAPropertyType::Vec4s)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec4s type.");
  }
  _value.v4s = aValue;
}


/// Operators for addition /////////////////////////////////////////////////////

PLAProperty PLAProperty::operator +(const PLAProperty &aProperty) const
{
  switch (aProperty._type)
  {
    case PLAPropertyType::Int :
      return *this + aProperty.GetInt();
    case PLAPropertyType::UInt :
      return *this + aProperty.GetUInt();
    case PLAPropertyType::Float :
      return *this + aProperty.GetFloat();
    case PLAPropertyType::Vec2f :
      return *this + aProperty.GetVec2f();
    case PLAPropertyType::Vec3f :
      return *this + aProperty.GetVec3f();
    case PLAPropertyType::Vec4f :
      return *this + aProperty.GetVec4f();
    case PLAPropertyType::Color :
      return *this + aProperty.GetColor();
    case PLAPropertyType::Vec2i :
      return *this + aProperty.GetVec2i();
    case PLAPropertyType::Vec3i :
      return *this + aProperty.GetVec3i();
    case PLAPropertyType::Vec4i :
      return *this + aProperty.GetVec4i();
    case PLAPropertyType::Vec2s :
      return *this + aProperty.GetVec2s();
    case PLAPropertyType::Vec3s :
      return *this + aProperty.GetVec3s();
    case PLAPropertyType::Vec4s :
      return *this + aProperty.GetVec4s();
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty::kNone;
  }
}

PLAProperty PLAProperty::operator +(PLAInt aValue) const
{ return PLAProperty(this->GetInt() + aValue); };

PLAProperty PLAProperty::operator +(PLAUInt aValue) const
{ return PLAProperty(this->GetUInt() + aValue); };

PLAProperty PLAProperty::operator +(PLAFloat aValue) const
{ return PLAProperty(this->GetFloat() + aValue); };

PLAProperty PLAProperty::operator +(const PLAVec2f &aValue) const
{ return PLAProperty(this->GetVec2f() + aValue); };

PLAProperty PLAProperty::operator +(const PLAVec3f &aValue) const
{ return PLAProperty(this->GetVec3f() + aValue); };

PLAProperty PLAProperty::operator +(const PLAVec4f &aValue) const
{ return PLAProperty(this->GetVec4f() + aValue); };

PLAProperty PLAProperty::operator +(const PLAColor &aValue) const
{ return PLAProperty(this->GetColor() + aValue); };

PLAProperty PLAProperty::operator +(const PLAVec2i &aValue) const
{ return PLAProperty(this->GetVec2i() + aValue); };

PLAProperty PLAProperty::operator +(const PLAVec3i &aValue) const
{ return PLAProperty(this->GetVec3i() + aValue); };

PLAProperty PLAProperty::operator +(const PLAVec4i &aValue) const
{ return PLAProperty(this->GetVec4i() + aValue); };

PLAProperty PLAProperty::operator +(const PLAVec2s &aValue) const
{ return PLAProperty(this->GetVec2s() + aValue); };

PLAProperty PLAProperty::operator +(const PLAVec3s &aValue) const
{ return PLAProperty(this->GetVec3s() + aValue); };

PLAProperty PLAProperty::operator +(const PLAVec4s &aValue) const
{ return PLAProperty(this->GetVec4s() + aValue); };

void PLAProperty::operator +=(const PLAProperty &aProperty)
{
  switch (aProperty._type)
  {
    case PLAPropertyType::Int   : *this += aProperty.GetInt();   break;
    case PLAPropertyType::UInt  : *this += aProperty.GetUInt();  break;
    case PLAPropertyType::Float : *this += aProperty.GetFloat(); break;
    case PLAPropertyType::Vec2f : *this += aProperty.GetVec2f(); break;
    case PLAPropertyType::Vec3f : *this += aProperty.GetVec3f(); break;
    case PLAPropertyType::Vec4f : *this += aProperty.GetVec4f(); break;
    case PLAPropertyType::Color : *this += aProperty.GetColor(); break;
    case PLAPropertyType::Vec2i : *this += aProperty.GetVec2i(); break;
    case PLAPropertyType::Vec3i : *this += aProperty.GetVec3i(); break;
    case PLAPropertyType::Vec4i : *this += aProperty.GetVec4i(); break;
    case PLAPropertyType::Vec2s : *this += aProperty.GetVec2s(); break;
    case PLAPropertyType::Vec3s : *this += aProperty.GetVec3s(); break;
    case PLAPropertyType::Vec4s : *this += aProperty.GetVec4s(); break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      break;
  }
}

void PLAProperty::operator +=(PLAInt aValue)
{ this->SetInt(this->GetInt() + aValue); };

void PLAProperty::operator +=(PLAUInt aValue)
{ this->SetUInt(this->GetUInt() + aValue); };

void PLAProperty::operator +=(PLAFloat aValue)
{ this->SetFloat(this->GetFloat() + aValue); };

void PLAProperty::operator +=(const PLAVec2f &aValue)
{ this->SetVec2f(this->GetVec2f() + aValue); };

void PLAProperty::operator +=(const PLAVec3f &aValue)
{ this->SetVec3f(this->GetVec3f() + aValue); };

void PLAProperty::operator +=(const PLAVec4f &aValue)
{ this->SetVec4f(this->GetVec4f() + aValue); };

void PLAProperty::operator +=(const PLAColor &aValue)
{ this->SetColor(this->GetColor() + aValue); };

void PLAProperty::operator +=(const PLAVec2i &aValue)
{ this->SetVec2i(this->GetVec2i() + aValue); };

void PLAProperty::operator +=(const PLAVec3i &aValue)
{ this->SetVec3i(this->GetVec3i() + aValue); };

void PLAProperty::operator +=(const PLAVec4i &aValue)
{ this->SetVec4i(this->GetVec4i() + aValue); };

void PLAProperty::operator +=(const PLAVec2s &aValue)
{ this->SetVec2s(this->GetVec2s() + aValue); };

void PLAProperty::operator +=(const PLAVec3s &aValue)
{ this->SetVec3s(this->GetVec3s() + aValue); };

void PLAProperty::operator +=(const PLAVec4s &aValue)
{ this->SetVec4s(this->GetVec4s() + aValue); };


/// Operators for substraction /////////////////////////////////////////////////

PLAProperty PLAProperty::operator -(const PLAProperty &aProperty) const
{
  switch (aProperty._type)
  {
    case PLAPropertyType::Int :
      return *this - aProperty.GetInt();
    case PLAPropertyType::UInt :
      return *this - aProperty.GetUInt();
    case PLAPropertyType::Float :
      return *this - aProperty.GetFloat();
    case PLAPropertyType::Vec2f :
      return *this - aProperty.GetVec2f();
    case PLAPropertyType::Vec3f :
      return *this - aProperty.GetVec3f();
    case PLAPropertyType::Vec4f :
      return *this - aProperty.GetVec4f();
    case PLAPropertyType::Color :
      return *this - aProperty.GetColor();
    case PLAPropertyType::Vec2i :
      return *this - aProperty.GetVec2i();
    case PLAPropertyType::Vec3i :
      return *this - aProperty.GetVec3i();
    case PLAPropertyType::Vec4i :
      return *this - aProperty.GetVec4i();
    case PLAPropertyType::Vec2s :
      return *this - aProperty.GetVec2s();
    case PLAPropertyType::Vec3s :
      return *this - aProperty.GetVec3s();
    case PLAPropertyType::Vec4s :
      return *this - aProperty.GetVec4s();
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty::kNone;
  }
}

PLAProperty PLAProperty::operator -(PLAInt aValue) const
{ return PLAProperty(this->GetInt() - aValue); };

PLAProperty PLAProperty::operator -(PLAUInt aValue) const
{ return PLAProperty(this->GetUInt() - aValue); };

PLAProperty PLAProperty::operator -(PLAFloat aValue) const
{ return PLAProperty(this->GetFloat() - aValue); };

PLAProperty PLAProperty::operator -(const PLAVec2f &aValue) const
{ return PLAProperty(this->GetVec2f() - aValue); };

PLAProperty PLAProperty::operator -(const PLAVec3f &aValue) const
{ return PLAProperty(this->GetVec3f() - aValue); };

PLAProperty PLAProperty::operator -(const PLAVec4f &aValue) const
{ return PLAProperty(this->GetVec4f() - aValue); };

PLAProperty PLAProperty::operator -(const PLAColor &aValue) const
{ return PLAProperty(this->GetColor() - aValue); };

PLAProperty PLAProperty::operator -(const PLAVec2i &aValue) const
{ return PLAProperty(this->GetVec2i() - aValue); };

PLAProperty PLAProperty::operator -(const PLAVec3i &aValue) const
{ return PLAProperty(this->GetVec3i() - aValue); };

PLAProperty PLAProperty::operator -(const PLAVec4i &aValue) const
{ return PLAProperty(this->GetVec4i() - aValue); };

PLAProperty PLAProperty::operator -(const PLAVec2s &aValue) const
{ return PLAProperty(this->GetVec2s() - aValue); };

PLAProperty PLAProperty::operator -(const PLAVec3s &aValue) const
{ return PLAProperty(this->GetVec3s() - aValue); };

PLAProperty PLAProperty::operator -(const PLAVec4s &aValue) const
{ return PLAProperty(this->GetVec4s() - aValue); };

void PLAProperty::operator -=(const PLAProperty &aProperty)
{
  switch (aProperty._type)
  {
    case PLAPropertyType::Int   : *this -= aProperty.GetInt(); break;
    case PLAPropertyType::UInt  : *this -= aProperty.GetUInt(); break;
    case PLAPropertyType::Float : *this -= aProperty.GetFloat(); break;
    case PLAPropertyType::Vec2f : *this -= aProperty.GetVec2f(); break;
    case PLAPropertyType::Vec3f : *this -= aProperty.GetVec3f(); break;
    case PLAPropertyType::Vec4f : *this -= aProperty.GetVec4f(); break;
    case PLAPropertyType::Color : *this -= aProperty.GetColor(); break;
    case PLAPropertyType::Vec2i : *this -= aProperty.GetVec2i(); break;
    case PLAPropertyType::Vec3i : *this -= aProperty.GetVec3i(); break;
    case PLAPropertyType::Vec4i : *this -= aProperty.GetVec4i(); break;
    case PLAPropertyType::Vec2s : *this -= aProperty.GetVec2s(); break;
    case PLAPropertyType::Vec3s : *this -= aProperty.GetVec3s(); break;
    case PLAPropertyType::Vec4s : *this -= aProperty.GetVec4s(); break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      break;
  }
}

void PLAProperty::operator -=(PLAInt aValue)
{ this->SetInt(this->GetInt() - aValue); };

void PLAProperty::operator -=(PLAUInt aValue)
{ this->SetUInt(this->GetUInt() - aValue); };

void PLAProperty::operator -=(PLAFloat aValue)
{ this->SetFloat(this->GetFloat() - aValue); };

void PLAProperty::operator -=(const PLAVec2f &aValue)
{ this->SetVec2f(this->GetVec2f() - aValue); };

void PLAProperty::operator -=(const PLAVec3f &aValue)
{ this->SetVec3f(this->GetVec3f() - aValue); };

void PLAProperty::operator -=(const PLAVec4f &aValue)
{ this->SetVec4f(this->GetVec4f() - aValue); };

void PLAProperty::operator -=(const PLAColor &aValue)
{ this->SetColor(this->GetColor() - aValue); };

void PLAProperty::operator -=(const PLAVec2i &aValue)
{ this->SetVec2i(this->GetVec2i() - aValue); };

void PLAProperty::operator -=(const PLAVec3i &aValue)
{ this->SetVec3i(this->GetVec3i() - aValue); };

void PLAProperty::operator -=(const PLAVec4i &aValue)
{ this->SetVec4i(this->GetVec4i() - aValue); };

void PLAProperty::operator -=(const PLAVec2s &aValue)
{ this->SetVec2s(this->GetVec2s() - aValue); };

void PLAProperty::operator -=(const PLAVec3s &aValue)
{ this->SetVec3s(this->GetVec3s() - aValue); };

void PLAProperty::operator -=(const PLAVec4s &aValue)
{ this->SetVec4s(this->GetVec4s() - aValue); };


/// Operators for multiplication ///////////////////////////////////////////////

PLAProperty PLAProperty::operator *(const PLAProperty &aProperty) const
{
  switch (aProperty._type) {
    case PLAPropertyType::Int   : return *this * aProperty.GetInt();
    case PLAPropertyType::UInt  : return *this * aProperty.GetUInt();
    case PLAPropertyType::Float : return *this * aProperty.GetFloat();
    case PLAPropertyType::Color : return *this * aProperty.GetColor();
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty::kNone;
  }
}

PLAProperty PLAProperty::operator *(PLAInt aValue) const
{
  switch (_type) {
    case PLAPropertyType::Int   : return PLAProperty(this->GetInt()   * aValue);
    case PLAPropertyType::Vec2i : return PLAProperty(this->GetVec2i() * aValue);
    case PLAPropertyType::Vec3i : return PLAProperty(this->GetVec3i() * aValue);
    case PLAPropertyType::Vec4i : return PLAProperty(this->GetVec4i() * aValue);
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty(aValue);
  }
}

PLAProperty PLAProperty::operator *(PLAUInt aValue) const
{
  switch (_type) {
    case PLAPropertyType::UInt  : return PLAProperty(this->GetUInt()  * aValue);
    case PLAPropertyType::Vec2s : return PLAProperty(this->GetVec2s() * aValue);
    case PLAPropertyType::Vec3s : return PLAProperty(this->GetVec3s() * aValue);
    case PLAPropertyType::Vec4s : return PLAProperty(this->GetVec4s() * aValue);
    case PLAPropertyType::Color : return PLAProperty(this->GetColor() * aValue);
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty(aValue);
  }
}

PLAProperty PLAProperty::operator *(PLAFloat aValue) const
{
  switch (_type) {
    case PLAPropertyType::Float : return PLAProperty(this->GetFloat() * aValue);
    case PLAPropertyType::Vec2f : return PLAProperty(this->GetVec2f() * aValue);
    case PLAPropertyType::Vec3f : return PLAProperty(this->GetVec3f() * aValue);
    case PLAPropertyType::Vec4f : return PLAProperty(this->GetVec4f() * aValue);
    case PLAPropertyType::Color : return PLAProperty(this->GetColor() * aValue);
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty(aValue);
  }
}

PLAProperty PLAProperty::operator *(const PLAColor &aValue) const
{
  switch (_type) {
    case PLAPropertyType::Color :
      return PLAProperty(this->GetColor() * aValue);
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty(aValue);
  }
}


void PLAProperty::operator *=(const PLAProperty &aProperty)
{
  switch (aProperty._type) {
    case PLAPropertyType::Int   : *this *= aProperty.GetInt();   break;
    case PLAPropertyType::UInt  : *this *= aProperty.GetUInt();  break;
    case PLAPropertyType::Float : *this *= aProperty.GetFloat(); break;
    case PLAPropertyType::Color : *this *= aProperty.GetColor(); break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      break;
  }
}

void PLAProperty::operator *=(PLAInt aValue)
{
  switch (_type) {
    case PLAPropertyType::Int   : this->SetInt(this->GetInt() * aValue);     break;
    case PLAPropertyType::Vec2i : this->SetVec2i(this->GetVec2i() * aValue); break;
    case PLAPropertyType::Vec3i : this->SetVec3i(this->GetVec3i() * aValue); break;
    case PLAPropertyType::Vec4i : this->SetVec4i(this->GetVec4i() * aValue); break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
  }
}

void PLAProperty::operator *=(PLAUInt aValue)
{
  switch (_type) {
    case PLAPropertyType::UInt  : this->SetUInt(this->GetUInt() * aValue);   break;
    case PLAPropertyType::Vec2s : this->SetVec2s(this->GetVec2s() * aValue); break;
    case PLAPropertyType::Vec3s : this->SetVec3s(this->GetVec3s() * aValue); break;
    case PLAPropertyType::Vec4s : this->SetVec4s(this->GetVec4s() * aValue); break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
  }
}

void PLAProperty::operator *=(PLAFloat aValue)
{
  switch (_type) {
    case PLAPropertyType::Float : this->SetFloat(this->GetFloat() * aValue); break;
    case PLAPropertyType::Vec2f : this->SetVec2f(this->GetVec2f() * aValue); break;
    case PLAPropertyType::Vec3f : this->SetVec3f(this->GetVec3f() * aValue); break;
    case PLAPropertyType::Vec4f : this->SetVec4f(this->GetVec4f() * aValue); break;
    case PLAPropertyType::Color : this->SetColor(this->GetColor() * aValue); break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
  }
}

void PLAProperty::operator *=(const PLAColor &aValue)
{
  switch (_type) {
    case PLAPropertyType::Color :
      this->SetColor(this->GetColor() * aValue);
      break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
  }
}


/// Operators for division /////////////////////////////////////////////////////

PLAProperty PLAProperty::operator /(const PLAProperty &aProperty) const
{
  switch (aProperty._type) {
    case PLAPropertyType::Int   : return *this / aProperty.GetInt();
    case PLAPropertyType::UInt  : return *this / aProperty.GetUInt();
    case PLAPropertyType::Float : return *this / aProperty.GetFloat();
    case PLAPropertyType::Color : return *this / aProperty.GetColor();
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty::kNone;
  }
}

PLAProperty PLAProperty::operator /(PLAInt aValue) const
{
  switch (_type) {
    case PLAPropertyType::Int   : return PLAProperty(this->GetInt()   / aValue);
    case PLAPropertyType::Vec2i : return PLAProperty(this->GetVec2i() / aValue);
    case PLAPropertyType::Vec3i : return PLAProperty(this->GetVec3i() / aValue);
    case PLAPropertyType::Vec4i : return PLAProperty(this->GetVec4i() / aValue);
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty::kNone;
  }
}

PLAProperty PLAProperty::operator /(PLAUInt aValue) const
{
  switch (_type) {
    case PLAPropertyType::UInt  : return PLAProperty(this->GetUInt()  / aValue);
    case PLAPropertyType::Vec2s : return PLAProperty(this->GetVec2s() / aValue);
    case PLAPropertyType::Vec3s : return PLAProperty(this->GetVec3s() / aValue);
    case PLAPropertyType::Vec4s : return PLAProperty(this->GetVec4s() / aValue);
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty::kNone;
  }
}

PLAProperty PLAProperty::operator /(PLAFloat aValue) const
{
  switch (_type) {
    case PLAPropertyType::Float : return PLAProperty(this->GetFloat() / aValue);
    case PLAPropertyType::Vec2f : return PLAProperty(this->GetVec2f() / aValue);
    case PLAPropertyType::Vec3f : return PLAProperty(this->GetVec3f() / aValue);
    case PLAPropertyType::Vec4f : return PLAProperty(this->GetVec4f() / aValue);
    case PLAPropertyType::Color : return PLAProperty(this->GetColor() / aValue);
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty::kNone;
  }
}

PLAProperty PLAProperty::operator /(const PLAColor &aValue) const
{
  switch (_type) {
    case PLAPropertyType::Color :
      return PLAProperty(this->GetColor() / aValue);
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty::kNone;
  }
}

void PLAProperty::operator /=(const PLAProperty &aProperty)
{
  switch (aProperty._type) {
    case PLAPropertyType::Int   : *this /= aProperty.GetInt();   break;
    case PLAPropertyType::UInt  : *this /= aProperty.GetUInt();  break;
    case PLAPropertyType::Float : *this /= aProperty.GetFloat(); break;
    case PLAPropertyType::Color : *this /= aProperty.GetColor(); break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      break;
  }
}

void PLAProperty::operator /=(PLAInt aValue)
{
  switch (_type) {
    case PLAPropertyType::Int   : this->SetInt(this->GetInt() / aValue);     break;
    case PLAPropertyType::Vec2i : this->SetVec2i(this->GetVec2i() / aValue); break;
    case PLAPropertyType::Vec3i : this->SetVec3i(this->GetVec3i() / aValue); break;
    case PLAPropertyType::Vec4i : this->SetVec4i(this->GetVec4i() / aValue); break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
  }
}

void PLAProperty::operator /=(PLAUInt aValue)
{
  switch (_type) {
    case PLAPropertyType::UInt  : this->SetUInt(this->GetUInt() / aValue);   break;
    case PLAPropertyType::Vec2s : this->SetVec2s(this->GetVec2s() / aValue); break;
    case PLAPropertyType::Vec3s : this->SetVec3s(this->GetVec3s() / aValue); break;
    case PLAPropertyType::Vec4s : this->SetVec4s(this->GetVec4s() / aValue); break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
  }
}

void PLAProperty::operator /=(PLAFloat aValue)
{
  switch (_type) {
    case PLAPropertyType::Float : this->SetFloat(this->GetFloat() / aValue); break;
    case PLAPropertyType::Vec2f : this->SetVec2f(this->GetVec2f() / aValue); break;
    case PLAPropertyType::Vec3f : this->SetVec3f(this->GetVec3f() / aValue); break;
    case PLAPropertyType::Vec4f : this->SetVec4f(this->GetVec4f() / aValue); break;
    case PLAPropertyType::Color : this->SetColor(this->GetColor() / aValue); break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
  }
}

void PLAProperty::operator /=(const PLAColor &aValue)
{
  switch (_type) {
    case PLAPropertyType::Color :
      this->SetColor(this->GetColor() / aValue);
      break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
  }
}
