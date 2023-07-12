//
// Created by Kentaro Kawai on 2023/05/20.
//

#ifndef ANHR_PLAAGTPHASE_HPP
#define ANHR_PLAAGTPHASE_HPP


#include "PLAAgent.hpp"
#include "PLAFunctionCode.hpp"
#include "Grain/Object/GRAOBJListener.hpp"

class PLAOBJPhase;

class PLAAGTPhase: public PLAAgent
{
public:
  /// Agent is const method only.
  PLAAGTPhase() = delete;
  explicit PLAAGTPhase(PLAOBJPhase *aOwner);
  virtual ~PLAAGTPhase() noexcept;

  void AddListener(GRAOBJListener<PLAAGTPhase, PLAFunctionCode::Phase> *aListener) const;
  void RemoveListener(GRAOBJListener<PLAAGTPhase, PLAFunctionCode::Phase> *aListener) const;
  void SetFunction(PLAFunctionCode::Phase aKey,
                   const std::function<void(PLAAGTPhase)> &aFunc) const;

  PLAId GetPhaseTag() const;
  void SetPhaseTag(PLAId aTag) const;

protected:
  const PLAOBJPhase *GetPhase() const;
  PLAOBJPhase *RefPhase() const;
};


#endif //ANHR_PLAAGTPHASE_HPP
