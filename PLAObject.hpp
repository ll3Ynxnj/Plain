#ifndef PLAIN_PLAOBJECT_HPP
#define PLAIN_PLAOBJECT_HPP

#include "Plain.hpp"
#include <vector>
#include "PLAObjectType.hpp"

class PLAObject
{
  size_t _id = kPLASizeUndefined;
  PLAObjectType _type = PLAObjectType::None;
  std::string _name = kPLACharUndefined;

public:
  explicit PLAObject(PLAObjectType aType);
  virtual ~PLAObject();

  size_t GetID() const { return _id; }
  PLAObjectType GetType() const { return _type; };
  const std::string &GetName() const { return _name; };

private:
  void SetId(size_t aId) { _id = aId; };

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager
  {
    static Manager _instance;

    std::vector<PLAObject *> _objects;

    Manager();

  public:
    static Manager *GetInstance() { return &_instance; };

    ~Manager();

    void Init();
    void Bind(PLAObject *aObject);
    void PrintObjects() const;
  };
};

#endif // PLAIN_PLAOBJECT_HPP
