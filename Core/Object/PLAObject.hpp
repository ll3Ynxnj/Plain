/*
 * @class PLAObject
 * @brief
 * \~english Object class is an object that is dynamically allocated in the system. Users operate objects through agents.
 * \~japanese オブジェクトクラスは、システム内で動的にメモリを確保して生成されるオブジェクトは全てオブジェクトです。利用者はエージェントを通してオブジェクトを操作します。
 * @version 0.1
 * @author ll3Ynxnj
 */

#ifndef PLAIN_ENGINE_PLAOBJECT_HPP
#define PLAIN_ENGINE_PLAOBJECT_HPP

#include <vector>
#include <stack>
#include <string>
#include <forward_list>
#include "PLAObjectType.hpp"
#include "Property/PLAProperty.hpp"

#include "Grain/Grain.h"
#include "Grain/Object/GRAOBJBinder.hpp"

class PLAAgent;

class PLAObject : private GRAOBJBinder<PLAObject>::Item
{
  using Binder = GRAOBJBinder<PLAObject>;
  static const std::map<Binder::Error, const char *> kBinderErrorMessages;

  PLAObjectType _type = PLAObjectType::None;
  PLAInt _agentReferenceCounter = 0;

protected:
  PLAObject(PLAObjectType aType);
  PLAObject(PLAObjectType aType, const PLAString &aName);

public:
  static const char *GetBinderErrorMessage(Binder::Error aError);
  static PLAObject *Object(PLAObjectType aType, const PLAString &aName);
  static PLAObject *Object(PLAObjectType aType, PLAId aId);

  virtual void Bind();
  virtual void Unbind();

  PLAObject() = delete;
  virtual ~PLAObject();

  virtual void Print();

  void RetainAgent();
  void ReleaseAgent();

  GRASize GetObjectId() const { return this->GetId(); }
  const PLAString &GetObjectName() const { return this->GetName(); };
  PLAObjectType GetObjectType() const { return _type; };
  const char *GetObjectTypeName() const;
  PLAString GetObjectDescription() const;

  void SetObjectName(const PLAString &aName);
  void SetObjectTag(PLAId aTag);

protected:

// GRAOBJBinder::Item /////////////////////////////////////////////////////////////
private:
  const char *GetBinderItemTypeName() const override;


// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRAOBJBinder<PLAObject>
  {
    static Manager _instance;
    std::vector<PLAObject *> _unboundObjects;

    Manager();

  public:
    static Manager *Instance() { return &_instance; };

    ~Manager();

    void AddUnboundObject(PLAObject *aObject);
    void DeleteUnboundObjects();
    void PrintObjects() const;
  };
};

#endif // PLAIN_ENGINE_PLAOBJECT_HPP
