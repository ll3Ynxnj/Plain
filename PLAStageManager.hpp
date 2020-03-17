#ifndef PLASTAGEMANAGER_HPP
#define PLASTAGEMANAGER_HPP

#include "Grain/GRASize.h"

class PLARectActor;

class PLAStageManager
{
  static PLAStageManager _instance;

  PLARectActor *_stage;

  PLAStageManager();

public:
  static PLAStageManager *GetInstance() { return &_instance; }

  ~PLAStageManager();

  void Init();
  void Reset();

  void Update();
  void Render();

  void SetStageSize(const GRASize aSize);
  void SetupActors();
};

#endif
