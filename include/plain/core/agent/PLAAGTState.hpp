//
// Created by Kentaro Kawai on 2023/04/07.
//

#ifndef ANHR_PLAAGTSTATE_HPP
#define ANHR_PLAAGTSTATE_HPP


#include "plain/core/agent/PLAAgent.hpp"

class PLAAGTModel;
class PLAOBJState;

class PLAAGTState final : public PLAAgent
{
public:
  /// Agent is const method only.
  explicit PLAAGTState(PLAOBJState *aOwner);

  virtual ~PLAAGTState() noexcept;

  void Init() const;
  void AddModel(const PLAAGTModel &aAgent) const;
  void PrintModels() const;

protected:
  const PLAOBJState *GetState() const;
  PLAOBJState *RefState() const;

};


#endif //ANHR_PLAAGTSTATE_HPP
