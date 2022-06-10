#ifndef PLAIN_PLARESOURCE_HPP
#define PLAIN_PLARESOURCE_HPP

#include "PLAObject.hpp"
#include "PLAError.hpp"

class PLAResource : public PLAObject, private GRABinder<PLAResource>::Item
{
public:
  using PLAResourceItem = GRABinder<PLAResource>::Item;
  using PLAResourceError = GRABinder<PLAResource>::Error;

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
  static PLAResource *Create(const PLAString &aName, const PLAString &aPath);
  void Bind() override;

  PLAResource(const PLAString &aName, const PLAString &aPath);
  virtual ~PLAResource() noexcept;

  void AllocData();
  void ReleaseData();

  const char *GetResourceTypeName() const;
  const PLAUInt8 *GetData() const { return _data; };
  PLASize GetSize() const { return _size; };

  void PrintResource() const;

protected:
  void Unbind() override;

// GRABinder::Item /////////////////////////////////////////////////////////////

private:
  const char *GetBinderItemTypeName() const override;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRABinder<PLAResource>
  {
    static Manager _instance;

  public:
    //static const Manager *Instance() { return &_instance; };
    //static Manager *RefInstance() { return &_instance; };
    static Manager *Instance() { return &_instance; };
    static PLAResource *Resource(const PLAString &aKey);

    Manager();
    ~Manager();

    const PLAResource *GetResource(const PLAString &aName) const;
    void PrintResources() const;

  private:
    void LoadResource(const PLAString &aName);
  };
};

#endif //PLAIN_PLARESOURCE_HPP
