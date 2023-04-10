//
// Created by Kentaro Kawai on 2023/04/05.
//

#ifndef ANHR_PLAOBJMODEL_HPP
#define ANHR_PLAOBJMODEL_HPP

#include <map>
#include <list>

#include "Object/PLAObject.hpp"
#include "Property/PLAProperty.hpp"

class PLAOBJModel :
public PLAObject
{
  std::map<PLAString, PLAProperty> _properties =
    std::map<PLAString, PLAProperty>();
  std::list<PLAOBJModel *> _models = {};

public:
  static PLAOBJModel *Create();

  PLAOBJModel();
  ~PLAOBJModel();

  void Init();

  void AddModel(PLAOBJModel *aModel);

  const PLAProperty &GetProperty(const PLAString &aKey);
  void SetProperty(const PLAString &aKey, const PLAProperty &aProperty);

  const std::list<PLAOBJModel *> *GetModels() const { return &_models; };

  PLABool GetBool(const PLAString &aName) const;
  PLAInt GetInt(const PLAString &aName) const;
  PLAFloat GetFloat(const PLAString &aName) const;
  PLAColor GetColor(const PLAColor &aName) const;
  const PLAString &GetString(const PLAString &aName) const;
  const PLAVec2 &GetVec2(const PLAString &aName) const;
  const PLAVec3 &GetVec3(const PLAString &aName) const;
  const PLAVec4 &GetVec4(const PLAString &aName) const;

  void SetBool(const PLAString &aName, PLABool aValue);
  void SetInt(const PLAString &aName, PLAInt aValue);
  void SetFloat(const PLAString &aName, PLAFloat aValue);
  void SetColor(const PLAString &aName, const PLAColor &aValue);
  void SetString(const PLAString &aName, const PLAString &aValue);
  void SetVec2(const PLAString &aName, const PLAVec2 &aValue);
  void SetVec3(const PLAString &aName, const PLAVec3 &aValue);
  void SetVec4(const PLAString &aName, const PLAVec4 &aValue);

  void PrintModels() const;
};


#endif //ANHR_PLAOBJMODEL_HPP
