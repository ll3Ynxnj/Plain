#ifndef PLAIN_ENGINE_PLAOBJECT_HPP
#define PLAIN_ENGINE_PLAOBJECT_HPP

#include "PLAType.hpp"
#include <vector>
#include <stack>
#include <string>
#include "PLAObjectType.hpp"

class PLAObject: private GRABinder::Item
{
  PLAObjectType _type = PLAObjectType::None;

protected:
  PLAObject(PLAObjectType aType);
  PLAObject(PLAObjectType aType, const std::string &aName);

public:
  static void Delete(PLAObject *aObject);

  PLAObject() = delete;
  virtual ~PLAObject();

  PLAObjectType GetObjectType() const { return _type; };

  // GRABinder::Item ///////////////////////////////////////////////////////////
  size_t GetObjectId() const { return this->GRABinder::Item::GetId(); };
  std::string GetObjectName() const { return this->GRABinder::Item::GetName(); };

  void SetObjectName(const std::string &aName)
  { this->GRABinder::Item::SetName(aName); };

  void PrintObject() const
  {
    GRA_PRINT(" %2x : ", _type);
    this->GRABinder::Item::Print();
  }

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager
  {
    static Manager _instance;

    GRABinder _binder = GRABinder();

  public:
    static const Manager *GetInstance() { return &_instance; };
    static Manager *RefInstance() { return &_instance; };

    Manager();
    ~Manager();

    void Bind(PLAObject *aObject, GRABinder::Error *aError)
    { _binder.Bind(aObject, aError); };

    void Unbind(PLAObject *aObject, GRABinder::Error *aError)
    { _binder.Unbind(aObject, aError); };

    void PrintObjects() const { _binder.PrintItems(); };
  };

  /*
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
  */
};

#endif // PLAIN_ENGINE_PLAOBJECT_HPP
