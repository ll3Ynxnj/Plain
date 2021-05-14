//
// Created by Kentaro Kawai on 2021/03/17.
//

#ifndef ANHR_PLARESOURCE_HPP
#define ANHR_PLARESOURCE_HPP

#include "PLAObject.hpp"

class PLAResource : public PLAObject, public GRABinder<PLAResource>::Item
{
  uint8_t *_data = nullptr;
  const std::string _path = "";

protected:
  PLAResource(const std::string &aPath);

public:
  static PLAResource *Create();

  virtual ~PLAResource();

  void AllocData();
  void ReleaseData();

  uint8_t *GetData() { return _data; }
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

    void PrintResources() const {
      for (GRABinder<PLAResource>::Item *item : this->GetItems())
      { static_cast<const PLAResource *>(item)->PrintResource(); }
    };
  };
};

class PLARSCImage : public PLAResource {
  size_t _width = 0;
  size_t _height = 0;

public:
  static PLARSCImage *Create(const std::string &aPath, size_t aWidth, size_t aHeight);

  PLARSCImage(const std::string &aPath, size_t aWidth, size_t aHeight);
  ~PLARSCImage();

  size_t GetWidth() { return _width; };
  size_t GetHeight() { return _height; };

  virtual size_t GetDataSize() const;
};

#endif //ANHR_PLARESOURCE_HPP
