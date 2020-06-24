#ifndef PLAIN_PLAOBJ_HPP
#define PLAIN_PLAOBJ_HPP

#include "Plain.hpp"
#include <vector>
#include "PLAObjectType.hpp"

class PLAObject
{
  size_t _id;
  PLAObjectType _type;

public:
  static void Bind(PLAObject *aObject)
  { Manager::GetInstance()->Bind(aObject); };

  PLAObject();
  virtual ~PLAObject();

private:
  void SetId(size_t aId) { _id = aId; };

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
  };
};

#endif // PLAIN_PLAOBJ_HPP
