#ifndef PLAIN_ENGINE_PLASTAGE_HPP
#define PLAIN_ENGINE_PLASTAGE_HPP

#include "PLAObject.hpp"
#include "PLAInput.hpp"
#include "PLAActor.hpp"

class PLAStage final : public PLAObject, public PLAInputHandler
{
  PLAActor *_context = nullptr;

public:
  static PLAStage *Create();

  PLAStage();
  ~PLAStage();

  void Update();
  void AddActor(PLAActor *aActor);
  void PrintActors() const;

  const PLAActor *GetContext() const { return _context; };
  void SetSize(const PLAVec3 &aSize);

// PLAInputHandler /////////////////////////////////////////////////////////////
public:
  virtual PLAInputContext *RefContextWithInput(const PLAInput &aInput) const;
};

#endif // PLAIN_ENGINE_PLASTAGE_HPP
