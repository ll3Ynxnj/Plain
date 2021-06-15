#ifndef PLAIN_ENGINE_PLAOBJECT_HPP
#define PLAIN_ENGINE_PLAOBJECT_HPP

#include <vector>
#include <stack>
#include <string>
#include "PLAObjectType.hpp"
#include "Grain/GRABinder.hpp"

class PLAObject : private GRABinder<PLAObject>::Item
{
  PLAObjectType _type = PLAObjectType::None;

protected:
  PLAObject(PLAObjectType aType);
  PLAObject(PLAObjectType aType, const std::string &aName);

public:
  static void Bind(PLAObject *aObject);
  static void Delete(PLAObject *aObject);

  PLAObject() = delete;
  virtual ~PLAObject();

  GRASize GetObjectId() const { return this->GetId(); }
  const std::string &GetObjectName() const { return this->GetName(); };
  PLAObjectType GetObjectType() const { return _type; };

  void SetObjectName(const std::string &aName);

  std::string GetObjectDescription() const;


// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRABinder<PLAObject>
  {
    static Manager _instance;

  public:
    static const Manager *GetInstance() { return &_instance; };
    static Manager *RefInstance() { return &_instance; };

    Manager();
    ~Manager();

    void PrintObjects() const;
  };
};

#endif // PLAIN_ENGINE_PLAOBJECT_HPP
