//
// Created by Kentaro Kawai on 2022/04/28.
//

#ifndef ANHR_PLAAGTSTAGE_HPP
#define ANHR_PLAAGTSTAGE_HPP

#include "PLAAgent.hpp"
#include "Input/PLAInput.hpp"
#include "Class/PLAStage.hpp"

class PLAAGTActor;

class PLAAGTStage final : public PLAAgent/*, public PLAInputHandler*/
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
  std::list<GRAListener<PLAAGTStage, FunctionCode> *> _listeners =
    std::list<GRAListener<PLAAGTStage, FunctionCode> *>();
  GRAFunctor<PLAAGTStage, FunctionCode> _functor =
    GRAFunctor<PLAAGTStage, FunctionCode>();

public:
  /// Agent is const method only.
  static PLAAGTStage *Create(PLAStage *aScene);

  virtual ~PLAAGTStage() noexcept;

  void Init();
  void AddActor(PLAAGTActor *aAgent);
  void PrintActors() const;

  void AddListener(GRAListener<PLAAGTStage, FunctionCode> *aListener)
  { _listeners.push_back(aListener); };

  void RemoveListener(GRAListener<PLAAGTStage, FunctionCode> *aListener)
  { _listeners.remove(aListener); };

  void SetFunction(FunctionCode aKey,
                   const std::function<void(PLAAGTStage *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

  void RunFunction(FunctionCode aKey)
  {
    _functor.RunFunction(aKey, this);
    for (GRAListener<PLAAGTStage, PLAAGTStage::FunctionCode> *listener: _listeners)
    { listener->RunListener(aKey, this); }
  };

  PLAVec3 GetSize() const;

protected:
  explicit PLAAGTStage(PLAStage *aScene);

  const PLAStage *GetStage() const
  { return static_cast<const PLAStage *>(this->GetOwner()); }
  PLAStage *RefStage() const
  { return static_cast<PLAStage *>(this->RefOwner()); }

// PLAInputHandler /////////////////////////////////////////////////////////////
/*
public:
  virtual PLAInputContext *RefContextWithInput(const PLAInput &aInput) const;
*/
};

#endif //ANHR_PLAAGTSTAGE_HPP
