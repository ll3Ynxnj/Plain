#ifndef PLAIN_ENGINE_PLAOBJRESOURCE_HPP
#define PLAIN_ENGINE_PLAOBJRESOURCE_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include "plain/core/PLAImageType.hpp"

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
  std::vector<PLAUInt8> _data = std::vector<PLAUInt8>(0);
  PLASize _size               = 0;
  const PLAString _path       = "";
  PLAImageType _imageType     = PLAImageType::None;
  PLASize _imageWidth         = 0;
  PLASize _imageHeight        = 0;

public:
  static PLAOBJResource *Create(const PLAString &aName, const PLAString &aPath);
  static PLAOBJResource *CreateFromMemory(const PLAString &aName, const PLAUInt8 *aData, PLASize aSize);
  void Bind() override;

protected:
  void Unbind() override;

public:
  PLAOBJResource(const PLAString &aName, const PLAString &aPath);
  virtual ~PLAOBJResource() noexcept;

  void AllocData();
  void ReleaseData();

  const char *GetResourceTypeName() const;
  const PLAUInt8 *GetData() const { return _data.data(); };
  PLASize GetSize() const { return _size; };
  PLAImageType GetImageType() const { return _imageType; };
  PLASize GetImageWidth() const { return _imageWidth; };
  PLASize GetImageHeight() const { return _imageHeight; };

  void UpdateData(const PLAUInt8 *aData, PLASize aSize);

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
