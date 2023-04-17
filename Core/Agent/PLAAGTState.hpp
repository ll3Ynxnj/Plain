//
// Created by Kentaro Kawai on 2023/04/07.
//

#ifndef ANHR_PLAAGTSTATE_HPP
#define ANHR_PLAAGTSTATE_HPP


#include "PLAAgent.hpp"
#include "Object/PLAOBJState.hpp"

class PLAAGTModel;

class PLAAGTState final : public PLAAgent
{
public:
  /// Agent is const method only.
  //static PLAAGTState *Create(PLAOBJState *aScene);
  explicit PLAAGTState(PLAOBJState *aState);

  virtual ~PLAAGTState() noexcept;

  void Init() const;
  void AddModel(const PLAAGTModel &aAgent) const;
  void PrintModels() const;

protected:
  const PLAOBJState *GetState() const
  { return static_cast<const PLAOBJState *>(this->GetOwner()); }
  PLAOBJState *RefState() const
  { return static_cast<PLAOBJState *>(this->RefOwner()); }

};


#endif //ANHR_PLAAGTSTATE_HPP
