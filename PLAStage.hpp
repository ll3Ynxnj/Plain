#ifndef PLAIN_PLASTAGE_HPP
#define PLAIN_PLASTAGE_HPP

#include "PLAType.hpp"

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
  void SetSize(const PLAVec3 &aSize);
};

#endif // PLAIN_PLASTAGE_HPP
