//
// Created by Kentaro Kawai on 2022/04/16.
//

#ifndef ANHR_PLAAGENT_HPP
#define ANHR_PLAAGENT_HPP

#include "../Class/PLAObject.hpp"

class PLAAgent: protected PLAObject
{
  PLAObject *_owner = nullptr;

public:
  using PLAObject::Unbind;

  static PLAAgent *Create(PLAObject *aObject);

  void Release() const;

  PLAId GetOwnerId() const { return _owner->GetObjectId(); }
  PLAObjectType GetOwnerType() const { return _owner->GetObjectType(); }
  const char *GetOwnerTypeName() const { return _owner->GetObjectTypeName(); }

  const PLAString &GetName() { return _owner->GetObjectName(); }

  void SetName(const PLAString &aName) { _owner->SetObjectName(aName); }

protected:
  PLAAgent(PLAObject *aObject);
  virtual ~PLAAgent();

  const PLAObject *GetOwner() const { return _owner; }
  PLAObject *RefOwner() const { return _owner; }
};


#endif //ANHR_PLAAGENT_HPP
