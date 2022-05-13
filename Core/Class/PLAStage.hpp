#ifndef PLAIN_ENGINE_PLASTAGE_HPP
#define PLAIN_ENGINE_PLASTAGE_HPP

#include "PLAObject.hpp"
#include "Input/PLAInputHandler.hpp"
#include "Core/Actor/PLAActor.hpp"

class PLAAGTStage;

class PLAStage final : public PLAObject, public PLAInputHandler
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

  PLAActor *_context = nullptr;
  /*
  std::list<GRAListener<PLAAGTStage, FunctionCode> *> _listeners =
    std::list<GRAListener<PLAAGTStage, FunctionCode> *>();
  GRAFunctor<PLAAGTStage, FunctionCode> _functor =
    GRAFunctor<PLAAGTStage, FunctionCode>();
  */

protected:
  PLAStage();

public:
  static PLAStage *Create();

  ~PLAStage();

  void Init();
  void Update();

  /*
  void AddListener(GRAListener<PLAAGTStage, FunctionCode> *aListener)
  { _listeners.push_back(aListener); };

  void RemoveListener(GRAListener<PLAAGTStage, FunctionCode> *aListener)
  { _listeners.remove(aListener); };

  void SetFunction(FunctionCode aKey,
                   const std::function<void(const PLAAGTStage *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };
  */

  void AddActor(PLAActor *aActor);
  void PrintActors() const;

  const PLAActor *GetContext() const { return _context; }
  PLAVec3 GetSize() const { return _context->GetSize(); }

  PLAActor *RefContext() const { return _context; }

  void SetSize(const PLAVec3 &aSize);

// PLAInputHandler /////////////////////////////////////////////////////////////
public:
  virtual PLAInputContext *RefContextWithInput(const PLAInput &aInput) const;
};

#endif // PLAIN_ENGINE_PLASTAGE_HPP
