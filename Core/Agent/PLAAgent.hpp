/*
 * @class PLAAgent
 * @brief
 * \~english Agent class is a wrapper and an agent for an object. It provides an interface for users. Since it is expected to be used as a value type, there is no Create
 * \~japanese エージェントクラスは、オブジェクトのラッパーであり代理人です。利用者がオブジェクトを操作するためのインターフェースを提供します。値型として利用されることを想定している為、Createメソッドはありません。
 * @author ll3Ynxnj
 */

#ifndef ANHR_PLAAGENT_HPP
#define ANHR_PLAAGENT_HPP


#include "PLAObjectType.hpp"
#include "Primitive/PLAPRMType.hpp"

class PLAObject;

class PLAAgent
{
  PLAObject *_owner = nullptr;

public:
  //static PLAAgent *Create(PLAObject *aObject);

  virtual ~PLAAgent();

  void Release();

  PLAId GetOwnerId() const;
  PLAObjectType GetOwnerType() const;
  const char *GetOwnerTypeName() const;

  const PLAString &GetName() const;

  void SetName(const PLAString &aName) const;

protected:
  PLAAgent() noexcept;
  explicit PLAAgent(const PLAAgent &aAgent) noexcept;
  explicit PLAAgent(PLAObject *aOwner);

  const PLAObject *GetOwner() const;
  PLAObject *RefOwner() const;
};


#endif //ANHR_PLAAGENT_HPP
