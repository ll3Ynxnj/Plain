// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/core/agent/PLAAGTPerformance.hpp"
#include "plain/core/object/PLAOBJPerformance.hpp"

PLAAGTPerformance::PLAAGTPerformance(PLAOBJPerformance *aOwner) :
  PLAAgent(aOwner)
{
}

PLAAGTPerformance::~PLAAGTPerformance() noexcept
{
}

PLAFloat PLAAGTPerformance::GetFPS() const
{
  return GetPerformance()->GetFPS();
}

const PLAOBJPerformance *PLAAGTPerformance::GetPerformance() const
{
  return static_cast<const PLAOBJPerformance *>(GetOwner());
}
