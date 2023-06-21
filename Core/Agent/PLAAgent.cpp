//
// Created by Kentaro Kawai on 2023/04/13.
//

#include "PLAAgent.hpp"
#include "Object/PLAObject.hpp"

PLAAgent::PLAAgent() noexcept {

}

PLAAgent::PLAAgent(PLAObject *aOwner) :
  _owner(aOwner)
{
  _owner->RetainAgent();
}

PLAAgent::PLAAgent(const PLAAgent &aAgent) noexcept {
  _owner = aAgent._owner;
  _owner->RetainAgent();
}

PLAAgent::~PLAAgent()
{
  if (_owner)
  {
    _owner->ReleaseAgent();
  }
}

void PLAAgent::Release()
{
  _owner->ReleaseAgent();
  _owner->Unbind();
  _owner = nullptr;
}

PLAId PLAAgent::GetOwnerId() const
{
  return _owner->GetObjectId();
}

PLAObjectType PLAAgent::GetOwnerType() const
{
  return _owner->GetObjectType();
}

const char *PLAAgent::GetOwnerTypeName() const
{
  return _owner->GetObjectTypeName();
}

const PLAString &PLAAgent::GetName()
{
  return _owner->GetObjectName();
}

void PLAAgent::SetName(const PLAString &aName)
{
  _owner->SetObjectName(aName);
}

const PLAObject *PLAAgent::GetOwner() const
{
  return _owner;
}

PLAObject *PLAAgent::RefOwner() const
{
  return _owner;
}
