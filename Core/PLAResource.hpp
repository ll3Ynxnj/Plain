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
  const std::string _path = "";

public:
  static PLAResource *Create(const std::string &aName, const std::string &aPath);
  static void Bind(PLAResource *aResource);

  PLAResource(const std::string &aName, const std::string &aPath);
  virtual ~PLAResource();

  void AllocData();
  void ReleaseData();

  const PLAUInt8 *GetData() const { return _data; };
  PLASize GetSize() const { return _size; };

  void PrintResource() const;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRABinder<PLAResource>
  {
    static Manager _instance;

  public:
    //static const Manager *Instance() { return &_instance; };
    //static Manager *RefInstance() { return &_instance; };
    static Manager *Instance() { return &_instance; };

    Manager();
    ~Manager();

    const PLAResource *GetResource(const std::string &aName) const
    {
      PLAResourceError error = PLAResourceError::None;
      const PLAResource *resource =
      static_cast<const PLAResource *>(this->GetItem(aName, &error));
      if (error != PLAResourceError::None)
      {
        PLA_ERROR_ISSUE(PLAErrorType::Assert,
                        "Failed to get resource. ERROR : %02d", error);
      }
      return resource;
    };

    void PrintResources() const;

  private:
    void LoadResource(const std::string &aName);
  };
};

#endif //PLAIN_PLARESOURCE_HPP
