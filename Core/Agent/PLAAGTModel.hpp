//
// Created by Kentaro Kawai on 2023/04/07.
//

#ifndef ANHR_PLAAGTMODEL_HPP
#define ANHR_PLAAGTMODEL_HPP


#include "PLAAgent.hpp"

class PLAOBJModel;

class PLAAGTModel final : public PLAAgent
{
public:
  /// Agent is const method only.
  PLAAGTModel() = default;
  explicit PLAAGTModel(PLAOBJModel *aOwner);
  virtual ~PLAAGTModel() noexcept;

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

  void SetBool(const PLAString &aName, PLABool aValue) const;
  void SetInt(const PLAString &aName, PLAInt aValue) const;
  void SetUInt(const PLAString &aName, PLAUInt aValue) const;
  void SetFloat(const PLAString &aName, PLAFloat aValue) const;

  void SetVec2f(const PLAString &aName, const PLAVec2f &aValue) const;
  void SetVec3f(const PLAString &aName, const PLAVec3f &aValue) const;
  void SetVec4f(const PLAString &aName, const PLAVec4f &aValue) const;
  void SetVec2i(const PLAString &aName, const PLAVec2i &aValue) const;
  void SetVec3i(const PLAString &aName, const PLAVec3i &aValue) const;
  void SetVec4i(const PLAString &aName, const PLAVec4i &aValue) const;
  void SetVec2s(const PLAString &aName, const PLAVec2s &aValue) const;
  void SetVec3s(const PLAString &aName, const PLAVec3s &aValue) const;
  void SetVec4s(const PLAString &aName, const PLAVec4s &aValue) const;

  void PrintModels() const;

//protected:
  const PLAOBJModel *GetModel() const;
  PLAOBJModel *RefModel() const;
};

#endif //ANHR_PLAAGTMODEL_HPP
