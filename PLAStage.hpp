#ifndef PLAIN_PLASTAGE_HPP
#define PLAIN_PLASTAGE_HPP

#include "PLAObj.hpp"

class PLARenderer;
class PLAActor;

class PLAStage : public PLAObj
{
  PLAActor *_context = nullptr;

public:
  PLAStage();
  ~PLAStage();

  void Update();

  const PLAActor *GetContext() const { return _context; }
  void SetupActors();
  void SetSize(const PLAVec3 &aSize);
};

#endif // PLAIN_PLASTAGE_HPP
