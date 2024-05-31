#ifndef PLAIN_ENGINE_PLAOBJSTAGE_HPP
#define PLAIN_ENGINE_PLAOBJSTAGE_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/actor/PLAOBJActor.hpp"

#include "plain/core/object/input/PLAInputHandler.hpp"

class PLAAGTStage;

class PLAOBJStage final: public PLAObject, public PLAInputHandler
{
  PLAOBJActor *_context = nullptr;

public:
  using Listener = GRAOBJListener<PLAAGTStage, PLAFunctionCode::Stage>;
  using Functor = GRAOBJFunctor<PLAAGTStage, PLAFunctionCode::Stage>;

private:
  std::list<Listener *> _listeners = std::list<Listener *>();
  Functor _functor = Functor();

protected:
  PLAOBJStage();
  PLAOBJStage(const PLAString &aName);

public:
  static PLAOBJStage *Create();
  static PLAOBJStage *Create(const PLAString &aName);
  static PLAOBJStage *Object(const PLAString &aName);
  static PLAOBJStage *Object(PLAId aId);

  ~PLAOBJStage();

  void Init();
  void Update();

  PLAAGTStage AssignAgent();

  void AddListener(GRAOBJListener<PLAAGTStage, PLAFunctionCode::Stage> *aListener);
  void RemoveListener(GRAOBJListener<PLAAGTStage, PLAFunctionCode::Stage> *aListener);
  void SetFunction(PLAFunctionCode::Stage aKey,
                   const std::function<void(PLAAGTStage)> &aFunc);
  void RunFunction(PLAFunctionCode::Stage aKey);

  void AddActor(PLAOBJActor *aActor);
  void RemoveActor(PLAOBJActor *aActor);
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
