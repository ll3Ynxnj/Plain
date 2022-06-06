//
// Created by Kentaro Kawai on 2021/09/07.
//

#include "PLAProperty.hpp"
#include "PLAError.hpp"
#include "Grain.h"

const PLAProperty PLAProperty::kNone  = PLAProperty();
const PLAProperty PLAProperty::kBool  = PLAProperty(PLABool(false));
const PLAProperty PLAProperty::kInt   = PLAProperty(PLAInt(0));
const PLAProperty PLAProperty::kFloat = PLAProperty(PLAFloat(0));
const PLAProperty PLAProperty::kColor = PLAProperty(kPLAColorNorm);
const PLAProperty PLAProperty::kVec2  = PLAProperty(kPLAVec2None);
const PLAProperty PLAProperty::kVec3  = PLAProperty(kPLAVec3None);
const PLAProperty PLAProperty::kVec4  = PLAProperty(kPLAVec4None);

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
    case PLAPropertyType::Float :
      GRA_PRINT("Float: %f", this->GetFloat());
      break;
    case PLAPropertyType::Color :
      GRA_PRINT("Color: {r: %f, g: %f, b: %f, a: %f}",
                this->GetColor().r, this->GetColor().g,
                this->GetColor().b, this->GetColor().a);
      break;
    case PLAPropertyType::Vec2 :
    {
      GRA_PRINT("Vec2: {x: %f, y: %f}", this->GetVec2().x, this->GetVec2().y);
      break;
    }
    case PLAPropertyType::Vec3 :
    {
      GRA_PRINT("Vec3: {x: %f, y: %f, z: %f}",
                this->GetVec3().x, this->GetVec3().y, this->GetVec3().z);
      break;
    }
    case PLAPropertyType::Vec4 :
    {
      GRA_PRINT("Vec4: {x: %f, y: %f, z: %f, w: %f}",
                this->GetVec4().x, this->GetVec4().y,
                this->GetVec4().z, this->GetVec4().w);
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
    case PLAPropertyType::Float : _value.f  = 0;             break;
    case PLAPropertyType::Color : _value.c  = kPLAColorNorm; break;
    case PLAPropertyType::Vec2  : _value.v2 = kPLAVec2None;  break;
    case PLAPropertyType::Vec3  : _value.v3 = kPLAVec3None;  break;
    case PLAPropertyType::Vec4  : _value.v4 = kPLAVec4None;  break;
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

const PLAVec2 &PLAProperty::GetVec2() const
{
  if (_type != PLAPropertyType::Vec2)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec2 type."); }
  return _value.v2;
}

const PLAVec3 &PLAProperty::GetVec3() const
{
  if (_type != PLAPropertyType::Vec3)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec3 type."); }
  return _value.v3;
}

const PLAVec4 &PLAProperty::GetVec4() const
{
  if (_type != PLAPropertyType::Vec4)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec4 type."); }
  return _value.v4;
}

void PLAProperty::Set(const PLAProperty &aProperty)
{
  switch (aProperty._type)
  {
    case PLAPropertyType::Bool  : SetBool(aProperty.GetBool());   break;
    case PLAPropertyType::Int   : SetInt(aProperty.GetInt());     break;
    case PLAPropertyType::Float : SetFloat(aProperty.GetFloat()); break;
    case PLAPropertyType::Color : SetColor(aProperty.GetColor()); break;
    case PLAPropertyType::Vec2  : SetVec2(aProperty.GetVec2());   break;
    case PLAPropertyType::Vec3  : SetVec3(aProperty.GetVec3());   break;
    case PLAPropertyType::Vec4  : SetVec4(aProperty.GetVec4());   break;
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

void PLAProperty::SetVec2(const PLAVec2 &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec2; }
  if (_type != PLAPropertyType::Vec2)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec2 type.");
  }
  _value.v2 = aValue;
}

void PLAProperty::SetVec3(const PLAVec3 &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec3; }
  if (_type != PLAPropertyType::Vec3)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec3 type.");
  }
  _value.v3 = aValue;
}

void PLAProperty::SetVec4(const PLAVec4 &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec4; }
  if (_type != PLAPropertyType::Vec4)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec4 type.");
  }
  _value.v4 = aValue;
}

PLAProperty PLAProperty::operator +(const PLAProperty &aProperty) const
{
  switch (aProperty._type)
  {
    case PLAPropertyType::Int :
      return *this + aProperty.GetInt();
    case PLAPropertyType::Float :
      return *this + aProperty.GetFloat();
    case PLAPropertyType::Vec2 :
      return *this + aProperty.GetVec2();
    case PLAPropertyType::Vec3 :
      return *this + aProperty.GetVec3();
    case PLAPropertyType::Vec4 :
      return *this + aProperty.GetVec4();
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty::kNone;
  }
}

void PLAProperty::operator +=(const PLAProperty &aProperty)
{
  switch (aProperty._type)
  {
    case PLAPropertyType::Int   : *this += aProperty.GetInt();   break;
    case PLAPropertyType::Float : *this += aProperty.GetFloat(); break;
    case PLAPropertyType::Vec2  : *this += aProperty.GetVec2();  break;
    case PLAPropertyType::Vec3  : *this += aProperty.GetVec3();  break;
    case PLAPropertyType::Vec4  : *this += aProperty.GetVec4();  break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      break;
  }
}

PLAProperty PLAProperty::operator *(const PLAProperty &aProperty) const
{
  switch (aProperty._type)
  {
    case PLAPropertyType::Int   : return *this * aProperty.GetInt();
    case PLAPropertyType::Float : return *this * aProperty.GetFloat();
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty::kNone;
  }
}

PLAProperty PLAProperty::operator *(PLAFloat aValue) const
{
  switch (_type) {
    case PLAPropertyType::Float : return PLAProperty(this->GetFloat() * aValue);
    case PLAPropertyType::Vec2  : return PLAProperty(this->GetVec2()  * aValue);
    case PLAPropertyType::Vec3  : return PLAProperty(this->GetVec3()  * aValue);
    case PLAPropertyType::Vec4  : return PLAProperty(this->GetVec4()  * aValue);
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      return PLAProperty(aValue);
  }
}

void PLAProperty::operator *=(const PLAProperty &aProperty)
{
  switch (aProperty._type)
  {
    case PLAPropertyType::Int   : *this *= aProperty.GetInt();     break;
    case PLAPropertyType::Float : *this *= aProperty.GetFloat(); break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      break;
  }
}


void PLAProperty::operator *=(PLAFloat aValue)
{
  switch (_type) {
    case PLAPropertyType::Float :
      this->SetFloat(this->GetFloat() * aValue);
      break;
    case PLAPropertyType::Vec2 :
      this->SetVec2(this->GetVec2() * aValue);
      break;
    case PLAPropertyType::Vec3 :
      this->SetVec3(this->GetVec3() * aValue);
      break;
    case PLAPropertyType::Vec4 :
      this->SetVec4(this->GetVec4() * aValue);
      break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
  }
}

