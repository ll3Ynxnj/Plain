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

void PLAProperty::Set(const PLAProperty &aProperty)
{
  switch (aProperty._type)
  {
    case PLAPropertyType::Bool :
      SetBool(*static_cast<PLABool *>(aProperty._value));
      break;
    case PLAPropertyType::Int :
      SetInt(*static_cast<PLAInt *>(aProperty._value));
      break;
    case PLAPropertyType::Float :
      SetFloat(*static_cast<PLAFloat *>(aProperty._value));
      break;
    case PLAPropertyType::Color :
      SetColor(*static_cast<PLAColor *>(aProperty._value));
      break;
    case PLAPropertyType::String :
      SetString(*static_cast<PLAString *>(aProperty._value));
      break;
    case PLAPropertyType::Vec2 :
      SetVec2(*static_cast<PLAVec2 *>(aProperty._value));
      break;
    case PLAPropertyType::Vec3 :
      SetVec3(*static_cast<PLAVec3 *>(aProperty._value));
      break;
    case PLAPropertyType::Vec4 :
      SetVec4(*static_cast<PLAVec4 *>(aProperty._value));
      break;
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

void PLAProperty::SetColor(const PLAColor &aValue)
{
  if (_type == PLAPropertyType::None) { _type = PLAPropertyType::Color; }
  if (_type != PLAPropertyType::Color)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Cannot be set except for PLAColor type.");
  }
  if (_value == nullptr)
  {
    _value = new PLAColor(aValue);
    return;
  }
  *static_cast<PLAColor *>(_value) = aValue;
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

void PLAProperty::Add(const PLAProperty &aProperty)
{
  switch (aProperty._type)
  {
    /*
    case PLAPropertyType::Bool :
      this->AddBool(*static_cast<PLABool *>(aProperty._value));
      break;
    */
    case PLAPropertyType::Int :
      this->AddInt(*static_cast<PLAInt *>(aProperty._value));
      break;
    case PLAPropertyType::Float :
      this->AddFloat(*static_cast<PLAFloat *>(aProperty._value));
      break;
    /*
    case PLAPropertyType::Color :
      this->AddColor(*static_cast<PLAColor *>(aProperty._value));
      break;
    */
    case PLAPropertyType::String :
      this->AddString(*static_cast<PLAString *>(aProperty._value));
      break;
    case PLAPropertyType::Vec2 :
      this->AddVec2(*static_cast<PLAVec2 *>(aProperty._value));
      break;
    case PLAPropertyType::Vec3 :
      this->AddVec3(*static_cast<PLAVec3 *>(aProperty._value));
      break;
    case PLAPropertyType::Vec4 :
      this->AddVec4(*static_cast<PLAVec4 *>(aProperty._value));
      break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "No compatible type.");
      break;
  }
}

/*
void PLAProperty::AddBool(PLABool aValue)
{
  this->SetBool(this->GetBool() + aValue);
}
*/

void PLAProperty::AddInt(PLAInt aValue)
{
  this->SetInt(this->GetInt() + aValue);
}

void PLAProperty::AddFloat(PLAFloat aValue)
{
  this->SetFloat(this->GetFloat() + aValue);
}

/*
void PLAProperty::AddColor(const PLAColor &aValue)
{
  this->SetColor(this->GetColor() + aValue);
}
*/

void PLAProperty::AddString(const PLAString &aValue)
{
  this->SetString(this->GetString() + aValue);
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
