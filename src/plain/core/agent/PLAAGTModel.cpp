//
// Created by Kentaro Kawai on 2023/04/07.
//

#include "plain/core/agent/PLAAGTModel.hpp"
#include "plain/core/object/model/PLAOBJModel.hpp"

PLAAGTModel::PLAAGTModel(PLAOBJModel *aOwner) :
  PLAAgent(aOwner)
{

}

PLAAGTModel::~PLAAGTModel() noexcept
{

}

PLABool PLAAGTModel::GetBool(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetBool(aName);
}

PLAInt PLAAGTModel::GetInt(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetInt(aName);
}

PLAUInt PLAAGTModel::GetUInt(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetUInt(aName);
}

PLAFloat PLAAGTModel::GetFloat(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetFloat(aName);
}

const std::string &PLAAGTModel::GetString(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetString(aName);
}

const PLAVec2f &PLAAGTModel::GetVec2f(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetVec2f(aName);
}

const PLAVec3f &PLAAGTModel::GetVec3f(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetVec3f(aName);
}

const PLAVec4f &PLAAGTModel::GetVec4f(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetVec4f(aName);
}

const PLAVec2i &PLAAGTModel::GetVec2i(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetVec2i(aName);
}

const PLAVec3i &PLAAGTModel::GetVec3i(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetVec3i(aName);
}

const PLAVec4i &PLAAGTModel::GetVec4i(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetVec4i(aName);
}

const PLAVec2s &PLAAGTModel::GetVec2s(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetVec2s(aName);
}

const PLAVec3s &PLAAGTModel::GetVec3s(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetVec3s(aName);
}

const PLAVec4s &PLAAGTModel::GetVec4s(const PLAString &aName) const
{
  auto model = this->GetModel();
  return model->GetVec4s(aName);
}

void PLAAGTModel::SetBool(const PLAString &aName, PLABool aValue) const
{
  auto model = this->RefModel();
  model->SetBool(aName, aValue);
}

void PLAAGTModel::SetInt(const PLAString &aName, PLAInt aValue) const
{
  auto model = this->RefModel();
  model->SetInt(aName, aValue);
}

void PLAAGTModel::SetUInt(const PLAString &aName, PLAUInt aValue) const
{
  auto model = this->RefModel();
  model->SetUInt(aName, aValue);
}

void PLAAGTModel::SetFloat(const PLAString &aName, PLAFloat aValue) const
{
  auto model = this->RefModel();
  model->SetFloat(aName, aValue);
}

void PLAAGTModel::SetString(const PLAString &aName, const std::string &aValue) const
{
  auto model = this->RefModel();
  model->SetString(aName, aValue);
}

void PLAAGTModel::SetVec2f(const PLAString &aName, const PLAVec2f &aValue) const
{
  auto model = this->RefModel();
  model->SetVec2f(aName, aValue);
}

void PLAAGTModel::SetVec3f(const PLAString &aName, const PLAVec3f &aValue) const
{
  auto model = this->RefModel();
  model->SetVec3f(aName, aValue);
}

void PLAAGTModel::SetVec4f(const PLAString &aName, const PLAVec4f &aValue) const
{
  auto model = this->RefModel();
  model->SetVec4f(aName, aValue);
}

void PLAAGTModel::SetVec2i(const PLAString &aName, const PLAVec2i &aValue) const
{
  auto model = this->RefModel();
  model->SetVec2i(aName, aValue);
}

void PLAAGTModel::SetVec3i(const PLAString &aName, const PLAVec3i &aValue) const
{
  auto model = this->RefModel();
  model->SetVec3i(aName, aValue);
}

void PLAAGTModel::SetVec4i(const PLAString &aName, const PLAVec4i &aValue) const
{
  auto model = this->RefModel();
  model->SetVec4i(aName, aValue);
}

void PLAAGTModel::SetVec2s(const PLAString &aName, const PLAVec2s &aValue) const
{
  auto model = this->RefModel();
  model->SetVec2s(aName, aValue);
}

void PLAAGTModel::SetVec3s(const PLAString &aName, const PLAVec3s &aValue) const
{
  auto model = this->RefModel();
  model->SetVec3s(aName, aValue);
}

void PLAAGTModel::SetVec4s(const PLAString &aName, const PLAVec4s &aValue) const
{
  auto model = this->RefModel();
  model->SetVec4s(aName, aValue);
}

void PLAAGTModel::SetProperty(const PLAString &aName, const PLAProperty &aProperty) const
{
  auto model = this->RefModel();
  model->SetProperty(aName, aProperty);
}

PLAId PLAAGTModel::GetModelTag() const
{
  auto model = this->GetModel();
  return model->GetModelTag();
}

void PLAAGTModel::SetModelTag(PLAId aTag) const
{
  auto model = this->RefModel();
  model->SetModelTag(aTag);
}

void PLAAGTModel::AddListener(
  GRAOBJListener<PLAAGTModel, PLAFunctionCode::Model> *aListener) const
{
  auto model = this->RefModel();
  model->AddListener(aListener);
}

void PLAAGTModel::RemoveListener(
  GRAOBJListener<PLAAGTModel, PLAFunctionCode::Model> *aListener) const
{
  auto model = this->RefModel();
  model->RemoveListener(aListener);
}

void PLAAGTModel::SetFunction(PLAFunctionCode::Model aKey,
                              const std::function<void(PLAAGTModel)> &aFunc) const
{
  auto model = this->RefModel();
  model->SetFunction(aKey, aFunc);
}

void PLAAGTModel::SetFunctionForProperty(
  const PLAString &aPropertyName,
  const std::function<void(PLAAGTModel, const PLAPropertyChange &)> &aFunc) const
{
  auto model = this->RefModel();
  model->SetFunctionForProperty(aPropertyName, aFunc);
}

void PLAAGTModel::PrintModels() const {
  auto model = this->GetModel();
  model->PrintModels();
}

const PLAOBJModel *PLAAGTModel::GetModel() const
{
  return static_cast<const PLAOBJModel *>(this->GetOwner());
}

PLAOBJModel *PLAAGTModel::RefModel() const
{
  return static_cast<PLAOBJModel *>(this->RefOwner());
}
