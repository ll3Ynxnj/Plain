#ifndef PLAIN_ENGINE_PLAOBJSTAGE_HPP
#define PLAIN_ENGINE_PLAOBJSTAGE_HPP

#include "PLAObject.hpp"
#include "Object/Input/PLAInputHandler.hpp"
#include "Actor/PLAOBJActor.hpp"

class PLAAGTStage;

class PLAOBJStage final : public PLAObject, public PLAInputHandler
{
public:
  /*
  enum class FunctionCode : PLAFunctionCode
  {
    OnInit,
    OnUpdate,
    OnResize,

    kNumberOfItems,
    None = kPLAFunctionCodeNone,
  };
  */

private:

  PLAOBJActor *_context = nullptr;
  /*
  std::list<GRAOBJListener<PLAAGTStage, FunctionCode> *> _listeners =
    std::list<GRAOBJListener<PLAAGTStage, FunctionCode> *>();
  GRAOBJFunctor<PLAAGTStage, FunctionCode> _functor =
    GRAOBJFunctor<PLAAGTStage, FunctionCode>();
  */

protected:
  PLAOBJStage();

public:
  static PLAOBJStage *Create();

  ~PLAOBJStage();

  void Init();
  void Update();

  /*
  void AddListener(GRAOBJListener<PLAAGTStage, FunctionCode> *aListener)
  { _listeners.push_back(aListener); };

  void RemoveListener(GRAOBJListener<PLAAGTStage, FunctionCode> *aListener)
  { _listeners.remove(aListener); };

  void SetFunction(FunctionCode aKey,
                   const std::function<void(const PLAAGTStage *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };
  */

  void AddActor(PLAOBJActor *aActor);
  void PrintActors() const;

  const PLAOBJActor *GetContext() const { return _context; }
  PLAVec3 GetSize() const { return _context->GetSize(); }

  PLAOBJActor *RefContext() const { return _context; }

  void SetSize(const PLAVec3 &aSize);

// PLAInputHandler /////////////////////////////////////////////////////////////
public:
  virtual PLAInputContext *RefContextWithInput(const PLAInput &aInput) const;
};

#endif // PLAIN_ENGINE_PLAOBJSTAGE_HPP
