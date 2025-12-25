// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAOBJPERFORMANCE_HPP
#define PLAIN_ENGINE_PLAOBJPERFORMANCE_HPP

#include "plain/core/object/PLAObject.hpp"
#include <chrono>

class PLAAGTPerformance;

class PLAOBJPerformance final : public PLAObject
{
  static PLAOBJPerformance _instance;

  std::chrono::high_resolution_clock::time_point _lastTime;
  PLAUInt _frameCount = 0;
  PLAFloat _currentFPS = 0.0f;
  bool _initialized = false;

  PLAOBJPerformance();

public:
  static PLAOBJPerformance *Instance() { return &_instance; }

  ~PLAOBJPerformance();

  PLAAGTPerformance AssignAgent();

  void Update();
  PLAFloat GetFPS() const { return _currentFPS; }
};

#endif // PLAIN_ENGINE_PLAOBJPERFORMANCE_HPP
