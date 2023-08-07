//
// Created by Kentaro Kawai on 2023/04/05.
//

#ifndef ANHR_PLAOBJMODEL_HPP
#define ANHR_PLAOBJMODEL_HPP

#include <map>
#include <list>

#include "Object/PLAObject.hpp"
#include "Property/PLAProperty.hpp"

class PLAAGTModel;

class PLAOBJModel :
public PLAObject,
private GRAOBJBinder<PLAOBJModel>::Item
{
  using Binder = GRAOBJBinder<PLAOBJModel>;
  static const std::map<Binder::Error, const char *> kBinderErrorMessages;

  std::map<PLAString, PLAProperty> _properties =
    std::map<PLAString, PLAProperty>();
  std::list<PLAOBJModel *> _models = {};

public:
  using PLAModelItem = GRAOBJBinder<PLAOBJModel>::Item;
  using PLAModelError = GRAOBJBinder<PLAOBJModel>::Error;

  static const char *GetBinderErrorMessage(Binder::Error aError);
  static PLAOBJModel *Create();
  static PLAOBJModel *Create(const PLAString &aName);
  static PLAOBJModel *Object(const PLAString &aName);
  static PLAOBJModel *Object(PLAId aId);
  static PLAOBJModel *ObjectWithTag(PLAId aTag);
  void Bind() override;

protected:
  PLAOBJModel();
  explicit PLAOBJModel(PLAString aName);
  void Unbind() override;

public:
  ~PLAOBJModel();

  void Init();

  PLAAGTModel AssignAgent();
  void AddModel(PLAOBJModel *aModel);

  const PLAProperty &GetProperty(const PLAString &aKey);
  void SetProperty(const PLAString &aKey, const PLAProperty &aProperty);

  const std::list<PLAOBJModel *> *GetModels() const { return &_models; };

  PLABool GetBool(const PLAString &aName) const;
  PLAInt GetInt(const PLAString &aName) const;
  PLAUInt GetUInt(const PLAString &aName) const;
  PLAFloat GetFloat(const PLAString &aName) const;

  const PLAVec2f &GetVec2f(const PLAString &aName) const;
  const PLAVec3f &GetVec3f(const PLAString &aName) const;
  const PLAVec4f &GetVec4f(const PLAString &aName) const;
  const PLAVec2i &GetVec2i(const PLAString &aName) const;
  const PLAVec3i &GetVec3i(const PLAString &aName) const;
  const PLAVec4i &GetVec4i(const PLAString &aName) const;
  const PLAVec2s &GetVec2s(const PLAString &aName) const;
  const PLAVec3s &GetVec3s(const PLAString &aName) const;
  const PLAVec4s &GetVec4s(const PLAString &aName) const;

  void SetBool(const PLAString &aName, PLABool aValue);
  void SetInt(const PLAString &aName, PLAInt aValue);
  void SetUInt(const PLAString &aName, PLAUInt aValue);
  void SetFloat(const PLAString &aName, PLAFloat aValue);

  void SetVec2f(const PLAString &aName, const PLAVec2f &aValue);
  void SetVec3f(const PLAString &aName, const PLAVec3f &aValue);
  void SetVec4f(const PLAString &aName, const PLAVec4f &aValue);
  void SetVec2i(const PLAString &aName, const PLAVec2i &aValue);
  void SetVec3i(const PLAString &aName, const PLAVec3i &aValue);
  void SetVec4i(const PLAString &aName, const PLAVec4i &aValue);
  void SetVec2s(const PLAString &aName, const PLAVec2s &aValue);
  void SetVec3s(const PLAString &aName, const PLAVec3s &aValue);
  void SetVec4s(const PLAString &aName, const PLAVec4s &aValue);

  PLAId GetModelTag() const;
  void SetModelTag(PLAId aTag);

  void PrintModels() const;

  const char *GetModelTypeName() const;

private:
  void ValidateNameIsNotEmpty(const PLAString &aName) const;
  void ValidatePropertyIsExist(const PLAString &aName) const;

  //-- GRAOBJBinder::Item --/////////////////////////////////////////////////////////
private:
  const char *GetBinderItemTypeName() const override;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRAOBJBinder<PLAOBJModel>
  {
    static Manager _instance;

    Manager();

  public:
    static Manager *Instance() { return &_instance; };
    static PLAOBJModel *Model(const PLAString &aKey);

    ~Manager();

    void Init();

    const PLAOBJModel *GetModel(const PLAString &aName) const;
    void PrintModels() const;
  };
};


#endif //ANHR_PLAOBJMODEL_HPP
