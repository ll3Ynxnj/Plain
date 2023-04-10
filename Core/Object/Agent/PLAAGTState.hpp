//
// Created by Kentaro Kawai on 2023/04/07.
//

#ifndef ANHR_PLAAGTSTATE_HPP
#define ANHR_PLAAGTSTATE_HPP


#include "PLAOBJAgent.hpp"
#include "Object/PLAOBJState.hpp"

class PLAAGTModel;

class PLAAGTState final : public PLAOBJAgent
{
public:
  /// Agent is const method only.
  static PLAAGTState *Create(PLAOBJState *aScene);

  virtual ~PLAAGTState() noexcept;

  void Init();
  void AddModel(PLAAGTModel *aAgent);
  void PrintModels() const;

protected:
  explicit PLAAGTState(PLAOBJState *aState);

  const PLAOBJState *GetState() const
  { return static_cast<const PLAOBJState *>(this->GetOwner()); }
  PLAOBJState *RefState() const
  { return static_cast<PLAOBJState *>(this->RefOwner()); }

};


#endif //ANHR_PLAAGTSTATE_HPP
