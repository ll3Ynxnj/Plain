//
// Created by Kentaro Kawai on 2023/04/13.
//

#ifndef ANHR_PLAAGENT_HPP
#define ANHR_PLAAGENT_HPP


#include "Object/PLAObject.hpp"

class PLAAgent
{
  PLAObject *_owner = nullptr;

public:
  //static PLAAgent *Create(PLAObject *aObject);

  virtual ~PLAAgent();

  //void Release() const;

  PLAId GetOwnerId() const { return _owner->GetObjectId(); }
  PLAObjectType GetOwnerType() const { return _owner->GetObjectType(); }
  const char *GetOwnerTypeName() const { return _owner->GetObjectTypeName(); }

  const PLAString &GetName() { return _owner->GetObjectName(); }

  void SetName(const PLAString &aName) { _owner->SetObjectName(aName); }

protected:
  PLAAgent() noexcept;
  PLAAgent(const PLAAgent &aAgent) noexcept;
  PLAAgent(PLAObject *aObject);

  const PLAObject *GetOwner() const { return _owner; }
  PLAObject *RefOwner() const { return _owner; }
};


#endif //ANHR_PLAAGENT_HPP
