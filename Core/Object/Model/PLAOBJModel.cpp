//
// Created by Kentaro Kawai on 2023/04/05.
//

#include "PLAOBJModel.hpp"
#include "Object/PLAOBJError.hpp"
#include "Agent/PLAAGTModel.hpp"

// 不要なのでは？同じくBinderItemであるPLAOBJResourceには無い。要調査。
// It's not necessary? PLAOBJResource, which is also a BinderItem, does not have it. Need to investigate.
const std::map<PLAOBJModel::Binder::Error, const char *> PLAOBJModel::kBinderErrorMessages =
  {
    { Binder::Error::OverwriteItem, "Overwrite item" },
    { Binder::Error::NameConflict, "Item name conflict" },
    { Binder::Error::NameOverride, "Item name has been over written" },
    { Binder::Error::NameConvertedBySystem, "Item name has been converted to system-generated" },
    { Binder::Error::RegisterExistingKeyToMap, "Register existing key to map" },
    { Binder::Error::NotExistInMap, "Not exist in map" },
    { Binder::Error::OutOfRange, "Out of range" },
  };

// 不要なのでは？同じくBinderItemであるPLAOBJResourceには無い。要調査。
// It's not necessary? PLAOBJResource, which is also a BinderItem, does not have it. Need to investigate.
const char *PLAOBJModel::GetBinderErrorMessage(Binder::Error aError)
{
  return kBinderErrorMessages.at(aError);
}

PLAOBJModel *PLAOBJModel::Create()
{
  PLAOBJModel *model = new PLAOBJModel();
  model->Init();
  model->Bind();
  return model;
}

PLAOBJModel *PLAOBJModel::Create(const PLAString &aName)
{
  PLAOBJModel *model = new PLAOBJModel(aName);
  model->Init();
  model->Bind();
  return model;
}

PLAOBJModel *PLAOBJModel::Object(const PLAString &aName)
{
  auto object = PLAObject::Object(PLAObjectType::Model, aName);
  return static_cast<PLAOBJModel *>(object);
}

PLAOBJModel *PLAOBJModel::Object(PLAId aId)
{
  auto object = PLAObject::Object(PLAObjectType::Model, aId);
  return static_cast<PLAOBJModel *>(object);
}

PLAOBJModel *PLAOBJModel::ObjectWithTag(PLAId aTag)
{
  GRAOBJBinder<PLAOBJModel>::Error error(GRAOBJBinder<PLAOBJModel>::Error::None);
  auto object = Manager::Instance()->RefItemWithTag(aTag, &error);
  if (error != GRAOBJBinder<PLAOBJModel>::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJModel getting. ERROR : %02d", error);
  }
  return static_cast<PLAOBJModel *>(object);
}

void PLAOBJModel::Bind()
{
  this->PLAObject::Bind();

  GRAOBJBinder<PLAOBJModel>::Error error(GRAOBJBinder<PLAOBJModel>::Error::None);
  PLAOBJModel::Manager::Instance()->Bind(this, &error);
  if (error != GRAOBJBinder<PLAOBJModel>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJModel binding. ERROR : %02d", error); }
}

void PLAOBJModel::Unbind()
{
  GRAOBJBinder<PLAOBJModel>::Error error(GRAOBJBinder<PLAOBJModel>::Error::None);
  PLAOBJModel::Manager::Instance()->Unbind(this, &error);
  if (error != GRAOBJBinder<PLAOBJModel>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJModel unbinding. ERROR : %02d", error); }

  PLAObject::Unbind();
}

PLAOBJModel::PLAOBJModel() :
PLAObject(PLAObjectType::Model),
GRAOBJBinder<PLAOBJModel>::Item(Manager::Instance())
{

}

PLAOBJModel::PLAOBJModel(PLAString aName) :
PLAObject(PLAObjectType::Model, aName),
GRAOBJBinder<PLAOBJModel>::Item(Manager::Instance())
{

}

PLAOBJModel::~PLAOBJModel()
{

}

void PLAOBJModel::Init()
{

}

PLAAGTModel PLAOBJModel::AssignAgent()
{
  return PLAAGTModel(this);
}

void PLAOBJModel::AddModel(PLAOBJModel *aModel)
{
  _models.push_back(aModel);
}

const PLAProperty &PLAOBJModel::GetProperty(const PLAString &aName)
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties[aName];
}

void PLAOBJModel::SetProperty(const PLAString &aName, const PLAProperty &aProperty)
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  _properties[aName] = aProperty;
}

PLABool PLAOBJModel::GetBool(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetBool();
}

PLAInt PLAOBJModel::GetInt(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetInt();
}

PLAUInt PLAOBJModel::GetUInt(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetUInt();
}

PLAFloat PLAOBJModel::GetFloat(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetFloat();
}

const PLAVec2f &PLAOBJModel::GetVec2f(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetVec2f();
}

const PLAVec3f &PLAOBJModel::GetVec3f(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetVec3f();
}

const PLAVec4f &PLAOBJModel::GetVec4f(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetVec4f();
}

const PLAVec2i &PLAOBJModel::GetVec2i(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetVec2i();
}

const PLAVec3i &PLAOBJModel::GetVec3i(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetVec3i();
}

const PLAVec4i &PLAOBJModel::GetVec4i(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetVec4i();
}

const PLAVec2s &PLAOBJModel::GetVec2s(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetVec2s();
}

const PLAVec3s &PLAOBJModel::GetVec3s(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetVec3s();
}

const PLAVec4s &PLAOBJModel::GetVec4s(const PLAString &aName) const
{
  this->ValidateNameIsNotEmpty(aName);
  this->ValidatePropertyIsExist(aName);
  return _properties.at(aName).GetVec4s();
}

void PLAOBJModel::SetBool(const PLAString &aName, PLABool aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  _properties[aName].SetBool(aValue);
}

void PLAOBJModel::SetInt(const PLAString &aName, PLAInt aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  auto property = _properties.find(aName);
  if (property == _properties.end())
  {
    auto property = PLAProperty(aValue);
    _properties.emplace(aName, property);
  }
  else
  { _properties[aName].SetInt(aValue); }
}

void PLAOBJModel::SetUInt(const PLAString &aName, PLAUInt aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  _properties[aName].SetUInt(aValue);
}

void PLAOBJModel::SetFloat(const PLAString &aName, PLAFloat aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  _properties[aName].SetFloat(aValue);
}

void PLAOBJModel::SetVec2f(const PLAString &aName, const PLAVec2f &aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  _properties[aName].SetVec2f(aValue);
}

void PLAOBJModel::SetVec3f(const PLAString &aName, const PLAVec3f &aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  _properties[aName].SetVec3f(aValue);
}

void PLAOBJModel::SetVec4f(const PLAString &aName, const PLAVec4f &aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  _properties[aName].SetVec4f(aValue);
}

void PLAOBJModel::SetVec2i(const PLAString &aName, const PLAVec2i &aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  _properties[aName].SetVec2i(aValue);
}

void PLAOBJModel::SetVec3i(const PLAString &aName, const PLAVec3i &aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  _properties[aName].SetVec3i(aValue);
}

void PLAOBJModel::SetVec4i(const PLAString &aName, const PLAVec4i &aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  _properties[aName].SetVec4i(aValue);
}

void PLAOBJModel::SetVec2s(const PLAString &aName, const PLAVec2s &aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  _properties[aName].SetVec2s(aValue);
}

void PLAOBJModel::SetVec3s(const PLAString &aName, const PLAVec3s &aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  _properties[aName].SetVec3s(aValue);
}

void PLAOBJModel::SetVec4s(const PLAString &aName, const PLAVec4s &aValue)
{
  this->ValidateNameIsNotEmpty(aName);
  _properties[aName].SetVec4s(aValue);
}

PLAId PLAOBJModel::GetModelTag() const {
  return this->GRAOBJBinder<PLAOBJModel>::Item::GetTag();
}

void PLAOBJModel::SetModelTag(PLAId aTag)
{
  Binder::Error error(Binder::Error::None);
  this->Binder::Item::SetTag(aTag, &error);
  if (error != Binder::Error::None)
  {
    switch (error) {
      case GRAOBJBinder<PLAOBJModel>::Error::TagOverride :
        PLA_ERROR_ISSUE(PLAErrorType::Expect,
                        "Succeed to set model tag with error. ERROR : %02d : %s",
                        error, PLAOBJModel::GetBinderErrorMessage(error));
        break;
      default :
        PLA_ERROR_ISSUE(PLAErrorType::Assert,
                        "Failure to set model tag. ERROR : %02d : %s",
                        error, PLAOBJModel::GetBinderErrorMessage(error));
        break;
    }
  }
}

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

const char *PLAOBJModel::GetModelTypeName() const
{
  static const char *kName = "(STUB: ModelType)";//"== STUB ==";
  return kName;
}

void PLAOBJModel::ValidateNameIsNotEmpty(const PLAString &aName) const
{
  if (aName.empty())
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Property name is empty."); }
}

void PLAOBJModel::ValidatePropertyIsExist(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Property `%s` does not exist.", aName.c_str()); }
}

//-- GRAOBJBinder::Item --/////////////////////////////////////////////////////////

const char *PLAOBJModel::GetBinderItemTypeName() const
{
  return this->GetModelTypeName();
}

// PLAOBJModel::Manager ////////////////////////////////////////////////////////

PLAOBJModel::Manager PLAOBJModel::Manager::_instance = PLAOBJModel::Manager();

PLAOBJModel::Manager::Manager() : GRAOBJBinder<PLAOBJModel>()
{

}

PLAOBJModel::Manager::~Manager()
{

}

void PLAOBJModel::Manager::Init()
{
  GRAOBJBinder<PLAOBJModel>::Init();
}

PLAOBJModel *PLAOBJModel::Manager::Model(const PLAString &aKey)
{
  GRAOBJBinder<PLAOBJModel>::Error error(GRAOBJBinder<PLAOBJModel>::Error::None);
  return static_cast<PLAOBJModel *>(_instance.RefItemWithName(aKey, &error));
}

void PLAOBJModel::Manager::PrintModels() const
{

};

const PLAOBJModel *PLAOBJModel::Manager::GetModel(const PLAString &aName) const
{
  PLAModelError error = PLAModelError::None;
  const PLAOBJModel *resource =
    static_cast<const PLAOBJModel *>(this->GetItemWithName(aName, &error));
  if (error != PLAModelError::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to get resource. ERROR : %02d", error);
  }
  return resource;
};
