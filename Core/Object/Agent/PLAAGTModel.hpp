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

protected:
  explicit PLAAGTModel(PLAOBJModel *aModel);

  const PLAOBJModel *GetModel() const
  { return static_cast<const PLAOBJModel *>(this->GetOwner()); }
  PLAOBJModel *RefModel() const
  { return static_cast<PLAOBJModel *>(this->RefOwner()); }
};

#endif //ANHR_PLAAGTMODEL_HPP
