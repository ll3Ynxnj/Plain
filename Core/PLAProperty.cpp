//
// Created by Kentaro Kawai on 2021/09/07.
//

#include "PLAProperty.hpp"
#include "PLAError.hpp"

PLABool PLAProperty::GetBool() const
{
  if (_type != PLAPropertyType::Bool)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLABool type."); }
  return *static_cast<PLABool *>(_value);
}

PLAInt PLAProperty::GetInt() const
{
  if (_type != PLAPropertyType::Int)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAInt type."); }
  return *static_cast<PLAInt *>(_value);
}

PLAFloat PLAProperty::GetFloat() const
{
  if (_type != PLAPropertyType::Float)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAFloat type."); }
  return *static_cast<PLAFloat *>(_value);
}

const PLAString &PLAProperty::GetString() const
{
  if (_type != PLAPropertyType::String)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAString type."); }
  return *static_cast<PLAString *>(_value);
}

const PLAVec2 &PLAProperty::GetVec2() const
{
  if (_type != PLAPropertyType::Vec2)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec2 type."); }
  return *static_cast<PLAVec2 *>(_value);
}

const PLAVec3 &PLAProperty::GetVec3() const
{
  if (_type != PLAPropertyType::Vec3)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec3 type."); }
  return *static_cast<PLAVec3 *>(_value);
}

const PLAVec4 &PLAProperty::GetVec4() const
{
  if (_type != PLAPropertyType::Vec4)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Value is not PLAVec4 type."); }
  return *static_cast<PLAVec4 *>(_value);
}

void PLAProperty::SetBool(PLABool aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Bool; }
  if (_type != PLAPropertyType::Bool)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLABool type.");
  }
  if (_value == nullptr)
  {
    _value = new PLABool(aValue);
    return;
  }
  *static_cast<PLABool *>(_value) = aValue;
}

void PLAProperty::SetInt(PLAInt aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Int; }
  if (_type != PLAPropertyType::Int)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAInt type.");
  }
  if (_value == nullptr)
  {
    _value = new PLAInt(aValue);
    return;
  }
  *static_cast<PLAInt *>(_value) = aValue;
}

void PLAProperty::SetFloat(PLAFloat aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Float; }
  if (_type != PLAPropertyType::Float)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAFloat type.");
  }
  if (_value == nullptr)
  {
    _value = new PLAFloat(aValue);
    return;
  }
  *static_cast<PLAFloat *>(_value) = aValue;
}

void PLAProperty::SetString(const PLAString &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::String; }
  if (_type != PLAPropertyType::String)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAString type.");
  }
  if (_value == nullptr)
  {
    _value = new PLAString(aValue);
    return;
  }
  *static_cast<PLAString *>(_value) = aValue;
}

void PLAProperty::SetVec2(const PLAVec2 &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec2; }
  if (_type != PLAPropertyType::Vec2)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec2 type.");
  }
  if (_value == nullptr)
  {
    _value = new PLAVec2(aValue);
    return;
  }
  *static_cast<PLAVec2 *>(_value) = aValue;
}

void PLAProperty::SetVec3(const PLAVec3 &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec3; }
  if (_type != PLAPropertyType::Vec3)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec3 type.");
  }
  if (_value == nullptr)
  {
    _value = new PLAVec3(aValue);
    return;
  }
  *static_cast<PLAVec3 *>(_value) = aValue;
}

void PLAProperty::SetVec4(const PLAVec4 &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Vec4; }
  if (_type != PLAPropertyType::Vec4)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAVec4 type.");
  }
  if (_value == nullptr)
  {
    _value = new PLAVec4(aValue);
    return;
  }
  *static_cast<PLAVec4 *>(_value) = aValue;
}
