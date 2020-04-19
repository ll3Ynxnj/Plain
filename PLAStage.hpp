#ifndef PLASTAGE_HPP
#define PLASTAGE_HPP

#include "Grain/GRASize.hpp"

class PLARectActor;

class PLAStage
{
  PLARectActor *_context;

public:
  PLAStage();
  ~PLAStage();

  void Update();
  void Render();

  void SetupActors();
  void SetSize(const GRASize &aSize);
};

#endif
