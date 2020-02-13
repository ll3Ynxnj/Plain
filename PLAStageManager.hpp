#ifndef PLASTAGEMANAGER_HPP
#define PLASTAGEMANAGER_HPP

#include "PLARectActor.hpp"

class PLAStageManager
{
  PLARectActor *_stage;

  PLAStageManager();

public:
  static PLAStageManager *GetInstance()
  { static PLAStageManager instance; return &instance; }

  ~PLAStageManager();

  void Initialize();

  void Update();
  void Render();

  void SetStageSize(const GRASize aSize);
  void SetupActors();
};

#endif
