//
// Created by Kentaro Kawai on 2021/09/07.
//

#include "PLAProperty.hpp"
#include "PLAError.hpp"

const PLAProperty PLAProperty::kBool  = PLAProperty(PLABool(false));
const PLAProperty PLAProperty::kInt   = PLAProperty(PLAInt(0));
const PLAProperty PLAProperty::kFloat = PLAProperty(PLAFloat(0));
const PLAProperty PLAProperty::kColor = PLAProperty(kPLAColorNorm);
const PLAProperty PLAProperty::kVec2  = PLAProperty(kPLAVec2None);
const PLAProperty PLAProperty::kVec3  = PLAProperty(kPLAVec3None);
const PLAProperty PLAProperty::kVec4  = PLAProperty(kPLAVec4None);

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

void PLAProperty::Add(const PLAProperty &aProperty)
{
  switch (aProperty._type)
  {
    case PLAPropertyType::Int :
      this->AddInt(aProperty.GetInt());
      break;
    case PLAPropertyType::Float :
      this->AddFloat(aProperty.GetFloat());
      break;
    case PLAPropertyType::Vec2 :
      this->AddVec2(aProperty.GetVec2());
      break;
    case PLAPropertyType::Vec3 :
      this->AddVec3(aProperty.GetVec3());
      break;
    case PLAPropertyType::Vec4 :
      this->AddVec4(aProperty.GetVec4());
      break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      break;
  }
}

void PLAProperty::AddInt(PLAInt aValue)
{
  this->SetInt(this->GetInt() + aValue);
}

void PLAProperty::AddFloat(PLAFloat aValue)
{
  this->SetFloat(this->GetFloat() + aValue);
}

void PLAProperty::AddVec2(const PLAVec2 &aValue)
{
  this->SetVec2(this->GetVec2() + aValue);
}

void PLAProperty::AddVec3(const PLAVec3 &aValue)
{
  this->SetVec3(this->GetVec3() + aValue);
}

void PLAProperty::AddVec4(const PLAVec4 &aValue)
{
  this->SetVec4(this->GetVec4() + aValue);
}
