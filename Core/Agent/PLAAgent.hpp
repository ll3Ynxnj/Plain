//
// Created by Kentaro Kawai on 2022/04/16.
//

#ifndef ANHR_PLAAGENT_HPP
#define ANHR_PLAAGENT_HPP

#include "../Class/PLAObject.hpp"

class PLAAgent: public PLAObject
{
  PLAObject *_owner = nullptr;

public:
  static PLAAgent *Create(PLAObject *aObject);

  void Release() const;

  const PLAObject *GetOwner() const { return _owner; }

  PLAId GetOwnerId() const { return _owner->GetObjectId(); }
  PLAObjectType GetOwnerType() const { return _owner->GetObjectType(); }
  const char *GetOwnerTypeName() const { return _owner->GetObjectTypeName(); }

protected:
  PLAAgent(PLAObject *aObject);
  virtual ~PLAAgent();
};


#endif //ANHR_PLAAGENT_HPP
