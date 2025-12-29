// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAAGTPERFORMANCE_HPP
#define PLAIN_ENGINE_PLAAGTPERFORMANCE_HPP

#include "plain/core/agent/PLAAgent.hpp"

class PLAOBJPerformance;

class PLAAGTPerformance final : public PLAAgent
{
public:
  PLAAGTPerformance() = delete;
  explicit PLAAGTPerformance(PLAOBJPerformance *aOwner);
  virtual ~PLAAGTPerformance() noexcept;

  PLAFloat GetFPS() const;

private:
  const PLAOBJPerformance *GetPerformance() const;
};

#endif // PLAIN_ENGINE_PLAAGTPERFORMANCE_HPP
