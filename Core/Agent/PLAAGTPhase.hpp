//
// Created by Kentaro Kawai on 2023/05/20.
//

#ifndef ANHR_PLAAGTPHASE_HPP
#define ANHR_PLAAGTPHASE_HPP


#include "PLAAgent.hpp"

class PLAOBJPhase;

class PLAAGTPhase: public PLAAgent
{
public:
  /// Agent is const method only.
  PLAAGTPhase() = default;
  explicit PLAAGTPhase(PLAOBJPhase *aPhase);
  virtual ~PLAAGTPhase() noexcept;
};


#endif //ANHR_PLAAGTPHASE_HPP
