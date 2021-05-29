//
// Created by Kentaro Kawai on 2021/03/17.
//

#ifndef ANHR_PLARESOURCE_HPP
#define ANHR_PLARESOURCE_HPP

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
  uint8_t *_data = nullptr;
  const std::string _path = "";

protected:
  PLAResource(const std::string &aName, const std::string &aPath);

public:
  static void Bind(PLAResource *aResource);

  virtual ~PLAResource();

  void AllocData();
  void ReleaseData();

  const uint8_t *GetData() const { return _data; }
  virtual size_t GetDataSize() const = 0;

  void PrintResource() const;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRABinder<PLAResource>
  {
    static Manager _instance;

  public:
    static const Manager *GetInstance() { return &_instance; };
    static Manager *RefInstance() { return &_instance; };

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

class PLARSCImage : public PLAResource {
  size_t _width = 0;
  size_t _height = 0;

public:
  static PLARSCImage *Create(const std::string &aName, const std::string &aPath,
                             size_t aWidth, size_t aHeight);

  PLARSCImage(const std::string &aName, const std::string &aPath,
              size_t aWidth, size_t aHeight);
  ~PLARSCImage();

  size_t GetWidth() const { return _width; };
  size_t GetHeight() const { return _height; };

  virtual size_t GetDataSize() const;
};

#endif //ANHR_PLARESOURCE_HPP
