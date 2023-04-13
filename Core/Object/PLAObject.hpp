#ifndef PLAIN_ENGINE_PLAOBJECT_HPP
#define PLAIN_ENGINE_PLAOBJECT_HPP

#include <vector>
#include <stack>
#include <string>
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
  //std::map<PLAString, PLAProperty> _properties =
  //  std::map<PLAString, PLAProperty>();
  //std::vector<PLAOBJAgent *> _agents;
  PLAAgent *_agent = nullptr;
  PLAInt _agentReferenceCounter = 0;

protected:
  PLAObject(PLAObjectType aType);
  PLAObject(PLAObjectType aType, const PLAString &aName);

public:
  static const char *GetBinderErrorMessage(Binder::Error aError);
  static PLAObject *Object(const PLAString &aName);
  static PLAObject *Object(PLAId aId);

  virtual void Bind();
  virtual void Unbind();

  PLAObject() = delete;
  virtual ~PLAObject();

  virtual void Print();

  virtual PLAAgent *AssignAgent();
  //void ReleaseAgent(const PLAOBJAgent *aAgent);
  void ReleaseAgent();

  GRASize GetObjectId() const { return this->GetId(); }
  const PLAString &GetObjectName() const { return this->GetName(); };
  PLAObjectType GetObjectType() const { return _type; };
  const char *GetObjectTypeName() const;
  PLAString GetObjectDescription() const;

  void SetObjectName(const PLAString &aName);

protected:
  //std::vector<PLAOBJAgent *> GetAgents() { return _agents; }
  const PLAAgent *GetAgent() const { return _agent; }
  PLAAgent *RefAgent() const { return _agent; }

// GRAOBJBinder::Item /////////////////////////////////////////////////////////////
private:
  const char *GetBinderItemTypeName() const override;


// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRAOBJBinder<PLAObject>
  {
    static Manager _instance;
    std::vector<PLAObject *> _unboundObjects;

  public:
    static Manager *Instance() { return &_instance; };

    Manager();
    ~Manager();

    void AddUnboundObject(PLAObject *aObject);
    void DeleteUnboundObjects();
    void PrintObjects() const;
  };
};

#endif // PLAIN_ENGINE_PLAOBJECT_HPP
