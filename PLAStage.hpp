#ifndef PLAIN_PLASTAGE_HPP
#define PLAIN_PLASTAGE_HPP

#include "PLAObj.hpp"

class PLARenderer;
class PLAActor;

class PLAStage : public PLAObj
{
  PLAActor *_context;

public:
  PLAStage();
  ~PLAStage();

  void Update();
  void Render(const PLARenderer *aRenderer);

  void SetupActors();
  void SetSize(const PLAVec3 &aSize);
};

#endif // PLAIN_PLASTAGE_HPP
