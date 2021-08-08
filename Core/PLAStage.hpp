#ifndef PLAIN_ENGINE_PLASTAGE_HPP
#define PLAIN_ENGINE_PLASTAGE_HPP

#include "PLAObject.hpp"
#include "Core/Input/PLAInput.hpp"
#include "Core/Actor/PLAActor.hpp"

class PLAStage final : public PLAObject, public PLAInputHandler
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

private:
  PLAActor *_context = nullptr;
  std::list<GRAListener<PLAStage, FunctionCode> *> _listeners =
    std::list<GRAListener<PLAStage, FunctionCode> *>();
  GRAFunctor<PLAStage, FunctionCode> _functor =
    GRAFunctor<PLAStage, FunctionCode>();

protected:
  PLAStage();

public:
  static PLAStage *Create();

  ~PLAStage();

  void Init();
  void Update();

  void AddListener(GRAListener<PLAStage, FunctionCode> *aListener)
  { _listeners.push_back(aListener); };

  void RemoveListener(GRAListener<PLAStage, FunctionCode> *aListener)
  { _listeners.remove(aListener); };

  void SetFunction(FunctionCode aKey,
                   const std::function<void(PLAStage *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

  void AddActor(PLAActor *aActor);
  void PrintActors() const;

  const PLAActor *GetContext() const { return _context; };
  PLAVec3 GetSize() const { return _context->GetSize(); }

  void SetSize(const PLAVec3 &aSize);

// PLAInputHandler /////////////////////////////////////////////////////////////
public:
  virtual PLAInputContext *RefContextWithInput(const PLAInput &aInput) const;
};

#endif // PLAIN_ENGINE_PLASTAGE_HPP
