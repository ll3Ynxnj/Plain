//
// Created by Kentaro Kawai on 2023/04/07.
//

#ifndef ANHR_PLAAGTMODEL_HPP
#define ANHR_PLAAGTMODEL_HPP


#include "PLAAGTState.hpp"
#include "PLAOBJAgent.hpp"

class PLAAGTModel final : public PLAOBJAgent//, public PLAInputContext
{
public:
  /// Agent is const method only.
  static PLAAGTModel *Create(PLAOBJModel *aModel);

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

  void PrintModels() const;

protected:
  explicit PLAAGTModel(PLAOBJModel *aModel);

  const PLAOBJModel *GetModel() const
  { return static_cast<const PLAOBJModel *>(this->GetOwner()); }
  PLAOBJModel *RefModel() const
  { return static_cast<PLAOBJModel *>(this->RefOwner()); }
};

#endif //ANHR_PLAAGTMODEL_HPP
