//
// Created by Kentaro Kawai on 2023/04/05.
//

#include "PLAOBJModel.hpp"
#include "Object/PLAOBJError.hpp"

PLAOBJModel *PLAOBJModel::Create()
{
  PLAOBJModel *model = new PLAOBJModel();
  model->Bind();
  return model;
}

PLAOBJModel::PLAOBJModel() :
PLAObject(PLAObjectType::Model)
{

}

PLAOBJModel::PLAOBJModel(PLAString aName) :
PLAObject(PLAObjectType::Model, aName)
{

}

PLAOBJModel::~PLAOBJModel()
{

}

void PLAOBJModel::Init()
{

}

void PLAOBJModel::AddModel(PLAOBJModel *aModel)
{
  _models.push_back(aModel);
}

const PLAProperty &PLAOBJModel::GetProperty(const PLAString &aKey)
{
  return _properties[aKey];
}

void PLAOBJModel::SetProperty(const PLAString &aKey, const PLAProperty &aProperty)
{
  _properties[aKey] = aProperty;
}

PLABool PLAOBJModel::GetBool(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                    "Property %s does not exist.", aName.c_str()); }
  return _properties.at(aName).GetBool();
}

PLAInt PLAOBJModel::GetInt(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetInt();
}

PLAUInt PLAOBJModel::GetUInt(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetUInt();
}

PLAFloat PLAOBJModel::GetFloat(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetFloat();
}

const PLAVec2f &PLAOBJModel::GetVec2f(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec2f();
}

const PLAVec3f &PLAOBJModel::GetVec3f(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec3f();
}

const PLAVec4f &PLAOBJModel::GetVec4f(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec4f();
}

const PLAVec2i &PLAOBJModel::GetVec2i(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec2i();
}

const PLAVec3i &PLAOBJModel::GetVec3i(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec3i();
}

const PLAVec4i &PLAOBJModel::GetVec4i(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec4i();
}

const PLAVec2s &PLAOBJModel::GetVec2s(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec2s();
}

const PLAVec3s &PLAOBJModel::GetVec3s(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec3s();
}

const PLAVec4s &PLAOBJModel::GetVec4s(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec4s();
}

void PLAOBJModel::SetBool(const PLAString &aName, PLABool aValue)
{
  _properties[aName].SetBool(aValue);
}

void PLAOBJModel::SetInt(const PLAString &aName, PLAInt aValue)
{
  _properties[aName].SetInt(aValue);
}

void PLAOBJModel::SetUInt(const PLAString &aName, PLAUInt aValue)
{
  _properties[aName].SetUInt(aValue);
}

void PLAOBJModel::SetFloat(const PLAString &aName, PLAFloat aValue)
{
  _properties[aName].SetFloat(aValue);
}

void PLAOBJModel::SetVec2f(const PLAString &aName, const PLAVec2f &aValue)
{
  _properties[aName].SetVec2f(aValue);
}

void PLAOBJModel::SetVec3f(const PLAString &aName, const PLAVec3f &aValue)
{
  _properties[aName].SetVec3f(aValue);
}

void PLAOBJModel::SetVec4f(const PLAString &aName, const PLAVec4f &aValue)
{
  _properties[aName].SetVec4f(aValue);
}

void PLAOBJModel::SetVec2i(const PLAString &aName, const PLAVec2i &aValue)
{
  _properties[aName].SetVec2i(aValue);
}

void PLAOBJModel::SetVec3i(const PLAString &aName, const PLAVec3i &aValue)
{
  _properties[aName].SetVec3i(aValue);
}

void PLAOBJModel::SetVec4i(const PLAString &aName, const PLAVec4i &aValue)
{
  _properties[aName].SetVec4i(aValue);
}

void PLAOBJModel::SetVec2s(const PLAString &aName, const PLAVec2s &aValue)
{
  _properties[aName].SetVec2s(aValue);
}

void PLAOBJModel::SetVec3s(const PLAString &aName, const PLAVec3s &aValue)
{
  _properties[aName].SetVec3s(aValue);
}

void PLAOBJModel::SetVec4s(const PLAString &aName, const PLAVec4s &aValue)
{
  _properties[aName].SetVec4s(aValue);
}

/*
void PLAOBJModel::PrintModels() const
{
  static int indentLevel = 0;
  GRA_PRINT(this->GetObjectDescription().c_str());
  ++indentLevel;
  GRA_PRINT("0: _models.size() = %d\n", _models.size());
  for (const PLAOBJModel *model : _models)
  {
    GRA_PRINT("1: _models.size() = %d\n", _models.size());
    for (int i = 0; i < indentLevel; i++) { GRA_PRINT("  "); }
    model->PrintModels();
  }
  --indentLevel;
}
 */

void PLAOBJModel::PrintModels() const
{
  static int indentLevel = 0;
  GRA_PRINT(this->GetObjectDescription().c_str());
  ++indentLevel;
  GRA_PRINT("0: _models.size() = %d\n", _models.size());
  int loop_counter = 0;
  for (const PLAOBJModel *model : _models)
  {
    loop_counter++;
    GRA_PRINT("1: _models.size() = %d, loop_counter = %d\n", _models.size(), loop_counter);
    for (int i = 0; i < indentLevel; i++) { GRA_PRINT("  "); }
    model->PrintModels();
  }
  --indentLevel;
}
