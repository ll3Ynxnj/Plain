#ifndef PLAIN_ENGINE_PLAOBJECT_HPP
#define PLAIN_ENGINE_PLAOBJECT_HPP

#include "../Plain-Macro.h"
#include "PLAType.hpp"
#include <vector>
#include <stack>
#include <string>
#include "PLAObjectType.hpp"

class PLAObject
{
  size_t _id = kPLASizeUndefined;
  PLAObjectType _type = PLAObjectType::None;
  std::string _name = kPLACharUndefined;

public:
  static void Delete(PLAObject *aObject);

  PLAObject() = delete;
  PLAObject(PLAObjectType aType);
  PLAObject(PLAObjectType aType, const std::string &aName);
  virtual ~PLAObject();

  size_t GetObjectId() const { return _id; }
  PLAObjectType GetObjectType() const { return _type; };
  const std::string &GetObjectName() const { return _name; };

  void SetObjectName(const std::string &aName) { _name = aName; };

  void PrintObject() const;

private:
  void SetId(size_t aId) { _id = aId; };

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager
  {
    static Manager _instance;

    std::vector<PLAObject *> _objects;
    std::stack<size_t> _emptyIndices;

    Manager();

  public:
    static const Manager *Get() { return &_instance; };
    static Manager *Ref() { return &_instance; };

    ~Manager();

    void Init();
    void Bind(PLAObject *aObject);
    void Unbind(PLAObject *aObject);
    void PrintObjects() const;
  };
};

#endif // PLAIN_ENGINE_PLAOBJECT_HPP
