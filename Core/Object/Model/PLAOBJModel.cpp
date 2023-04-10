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

PLAFloat PLAOBJModel::GetFloat(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetFloat();
}

const PLAVec2 &PLAOBJModel::GetVec2(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec2();
}

const PLAVec3 &PLAOBJModel::GetVec3(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec3();
}

const PLAVec4 &PLAOBJModel::GetVec4(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec4();
}

void PLAOBJModel::SetBool(const PLAString &aName, PLABool aValue)
{
  _properties[aName].SetBool(aValue);
}

void PLAOBJModel::SetInt(const PLAString &aName, PLAInt aValue)
{
  _properties[aName].SetInt(aValue);
}

void PLAOBJModel::SetFloat(const PLAString &aName, PLAFloat aValue)
{
  _properties[aName].SetFloat(aValue);
}

void PLAOBJModel::SetVec2(const PLAString &aName, const PLAVec2 &aValue)
{
  _properties[aName].SetVec2(aValue);
}

void PLAOBJModel::SetVec3(const PLAString &aName, const PLAVec3 &aValue)
{
  _properties[aName].SetVec3(aValue);
}

void PLAOBJModel::SetVec4(const PLAString &aName, const PLAVec4 &aValue)
{
  _properties[aName].SetVec4(aValue);
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
