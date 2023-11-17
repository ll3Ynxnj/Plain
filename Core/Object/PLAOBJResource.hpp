#ifndef PLAIN_ENGINE_PLAOBJRESOURCE_HPP
#define PLAIN_ENGINE_PLAOBJRESOURCE_HPP

#include "PLAObject.hpp"
#include "PLAOBJError.hpp"

class PLAOBJResource : public PLAObject, private GRAOBJBinder<PLAOBJResource>::Item
{
public:
  using PLAResourceItem = GRAOBJBinder<PLAOBJResource>::Item;
  using PLAResourceError = GRAOBJBinder<PLAOBJResource>::Error;

  /*
  enum class State
  {
    Loading,
    Ready,

    kNumberOfItems,
    None,

  };
   */

private:
  PLAUInt8 *_data = nullptr;
  PLASize _size = 1024 * 1024 * 4;
  const PLAString _path = "";

public:
  static PLAOBJResource *Create(const PLAString &aName, const PLAString &aPath);
  void Bind() override;

protected:
  void Unbind() override;

public:
  PLAOBJResource(const PLAString &aName, const PLAString &aPath);
  virtual ~PLAOBJResource() noexcept;

  void AllocData();
  void ReleaseData();

  const char *GetResourceTypeName() const;
  const PLAUInt8 *GetData() const { return _data; };
  PLASize GetSize() const { return _size; };

  void PrintResource() const;

// GRAOBJBinder::Item /////////////////////////////////////////////////////////////

private:
  const char *GetBinderItemTypeName() const override;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRAOBJBinder<PLAOBJResource>
  {
    static Manager _instance;

    Manager();

  public:
    //static const Manager *Instance() { return &_instance; };
    //static Manager *RefInstance() { return &_instance; };
    static Manager *Instance() { return &_instance; };
    static PLAOBJResource *Resource(const PLAString &aKey);

    ~Manager();

    void Init();

    const PLAOBJResource *GetResource(const PLAString &aName) const;
    void PrintResources() const;

  private:
    void Load();
    void LoadResource(const PLAString &aName);
  };
};

#endif //PLAIN_ENGINE_PLAOBJRESOURCE_HPP
