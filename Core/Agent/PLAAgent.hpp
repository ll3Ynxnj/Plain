/*
 * @class PLAAgent
 * @brief
 * \~english Agent class is a wrapper and an agent for an object. It provides an interface for users. Since it is expected to be used as a value type, there is no Create
 * \~japanese エージェントクラスは、オブジェクトのラッパーであり代理人です。利用者がオブジェクトを操作するためのインターフェースを提供します。値型として利用されることを想定している為、Createメソッドはありません。
 * @author ll3Ynxnj
 */

#ifndef ANHR_PLAAGENT_HPP
#define ANHR_PLAAGENT_HPP


#include "Object/PLAObject.hpp"

class PLAAgent
{
  PLAObject *_owner = nullptr;

public:
  //static PLAAgent *Create(PLAObject *aObject);

  virtual ~PLAAgent();

  void Release();

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
