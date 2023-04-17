#ifndef PLAIN_ENGINE_PLAOBJSTAGE_HPP
#define PLAIN_ENGINE_PLAOBJSTAGE_HPP

#include "PLAObject.hpp"
#include "Object/Input/PLAInputHandler.hpp"
#include "Actor/PLAOBJActor.hpp"

class PLAAGTStage;

class PLAOBJStage final: public PLAObject, public PLAInputHandler
{
public:
  enum class FunctionCode : PLAFunctionCode
  {
    OnInit,
    OnUpdate,
    OnResize,

    kNumberOfItems,
    None = kPLAFunctionCodeNone,
  };

  PLAOBJActor *_context = nullptr;

private:
  std::list<GRAOBJListener<PLAAGTStage, FunctionCode> *> _listeners =
    std::list<GRAOBJListener<PLAAGTStage, FunctionCode> *>();
  GRAOBJFunctor<PLAAGTStage, FunctionCode> _functor =
    GRAOBJFunctor<PLAAGTStage, FunctionCode>();

protected:
  PLAOBJStage();

public:
  static PLAOBJStage *Create();
  static PLAOBJStage *Object(const PLAString &aName);
  static PLAOBJStage *Object(PLAId aId);

  ~PLAOBJStage();

  void Init();
  void Update();

  PLAAGTStage AssignAgent();

  void AddListener(GRAOBJListener<PLAAGTStage, PLAOBJStage::FunctionCode> *aListener);
  void RemoveListener(GRAOBJListener<PLAAGTStage, PLAOBJStage::FunctionCode> *aListener);
  void SetFunction(PLAOBJStage::FunctionCode aKey,
                   const std::function<void(PLAAGTStage)> &aFunc);
  void RunFunction(PLAOBJStage::FunctionCode aKey);

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
