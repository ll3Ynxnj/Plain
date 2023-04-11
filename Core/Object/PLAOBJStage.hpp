#ifndef PLAIN_ENGINE_PLAOBJSTAGE_HPP
#define PLAIN_ENGINE_PLAOBJSTAGE_HPP

#include "PLAObject.hpp"
#include "Object/Input/PLAInputHandler.hpp"
#include "Actor/PLAOBJActor.hpp"

class PLAAGTStage;

class PLAOBJStage final: public PLAObject, public PLAInputHandler
{
  PLAOBJActor *_context = nullptr;

protected:
  PLAOBJStage();

public:
  static PLAOBJStage *Create();

  ~PLAOBJStage();

  void Init();
  void Update();

  void AddActor(PLAOBJActor *aActor);
  void PrintActors() const;

  const PLAOBJActor *GetContext() const { return _context; }
  PLAVec3f GetSize() const { return _context->GetSize(); }

  PLAOBJActor *RefContext() const { return _context; }

  void SetSize(const PLAVec3f &aSize);

// PLAInputHandler /////////////////////////////////////////////////////////////
public:
  virtual PLAInputContext *RefContextWithInput(const PLAInput &aInput) const;
};

#endif // PLAIN_ENGINE_PLAOBJSTAGE_HPP
