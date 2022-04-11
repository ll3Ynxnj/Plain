#ifndef PLAIN_ENGINE_PLAOBJECT_HPP
#define PLAIN_ENGINE_PLAOBJECT_HPP

#include <vector>
#include <stack>
#include <string>
#include "PLAObjectType.hpp"
#include "PLAProperty.hpp"

#include "Grain/Grain.h"
#include "Grain/Class/GRABinder.hpp"

class PLAObject : private GRABinder<PLAObject>::Item
{
  using Binder = GRABinder<PLAObject>;
  static const std::map<Binder::Error, const char *> kBinderErrorMessages;

  PLAObjectType _type = PLAObjectType::None;
  std::map<PLAString, PLAProperty> _properties =
    std::map<PLAString, PLAProperty>();

protected:
  PLAObject(PLAObjectType aType);
  PLAObject(PLAObjectType aType, const std::string &aName);

public:
  static const char *GetBinderErrorMessage(Binder::Error aError);

  virtual void Bind();
  virtual void Unbind();

  PLAObject() = delete;
  virtual ~PLAObject();

  virtual void Print();

  GRASize GetObjectId() const { return this->GetId(); }
  const std::string &GetObjectName() const { return this->GetName(); };
  PLAObjectType GetObjectType() const { return _type; };

  PLABool GetBool(const PLAString &aName) const;
  PLAInt GetInt(const PLAString &aName) const;
  PLAFloat GetFloat(const PLAString &aName) const;
  PLAColor GetColor(const PLAColor &aName) const;
  const PLAString &GetString(const PLAString &aName) const;
  const PLAVec2 &GetVec2(const PLAString &aName) const;
  const PLAVec3 &GetVec3(const PLAString &aName) const;
  const PLAVec4 &GetVec4(const PLAString &aName) const;

  void SetObjectName(const std::string &aName);

  void SetBool(const PLAString &aName, PLABool aValue);
  void SetInt(const PLAString &aName, PLAInt aValue);
  void SetFloat(const PLAString &aName, PLAFloat aValue);
  void SetColor(const PLAString &aName, const PLAColor &aValue);
  void SetString(const PLAString &aName, const PLAString &aValue);
  void SetVec2(const PLAString &aName, const PLAVec2 &aValue);
  void SetVec3(const PLAString &aName, const PLAVec3 &aValue);
  void SetVec4(const PLAString &aName, const PLAVec4 &aValue);

  std::string GetObjectDescription() const;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRABinder<PLAObject>
  {
    static Manager _instance;
    std::vector<PLAObject *> _unboundObjects;

  public:
    static Manager *Instance() { return &_instance; };
    static PLAObject *Object(const std::string &aKey);

    Manager();
    ~Manager();

    void AddUnboundObject(PLAObject *aObject);
    void DeleteUnboundObjects();
    void PrintObjects() const;
  };
};




#endif // PLAIN_ENGINE_PLAOBJECT_HPP
