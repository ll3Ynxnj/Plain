// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/core/object/PLAOBJPerformance.hpp"
#include "plain/core/agent/PLAAGTPerformance.hpp"

PLAOBJPerformance PLAOBJPerformance::_instance = PLAOBJPerformance();

PLAOBJPerformance::PLAOBJPerformance() :
  PLAObject(PLAObjectType::Performance, "PLAOBJPerformance")
{
}

PLAOBJPerformance::~PLAOBJPerformance()
{
}

PLAAGTPerformance PLAOBJPerformance::AssignAgent()
{
  return PLAAGTPerformance(this);
}

void PLAOBJPerformance::Update()
{
  auto now = std::chrono::high_resolution_clock::now();

  if (!_initialized) {
    _lastTime = now;
    _initialized = true;
    return;
  }

  auto elapsed = std::chrono::duration<double>(now - _lastTime).count();

  if (elapsed >= 1.0) {
    _currentFPS = static_cast<PLAFloat>(_frameCount) / elapsed;
    _frameCount = 0;
    _lastTime = now;
  }

  ++_frameCount;
}
