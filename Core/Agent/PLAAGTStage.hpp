//
// Created by Kentaro Kawai on 2022/04/28.
//

#ifndef ANHR_PLAAGTSTAGE_HPP
#define ANHR_PLAAGTSTAGE_HPP

#include "PLAAgent.hpp"
#include "Object/Input/PLAInput.hpp"
#include "Object/PLAOBJStage.hpp"

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
  std::list<GRAOBJListener<PLAAGTStage, FunctionCode> *> _listeners =
    std::list<GRAOBJListener<PLAAGTStage, FunctionCode> *>();
  GRAOBJFunctor<PLAAGTStage, FunctionCode> _functor =
    GRAOBJFunctor<PLAAGTStage, FunctionCode>();

public:
  /// Agent is const method only.
  static PLAAGTStage *Create(PLAOBJStage *aScene);

  virtual ~PLAAGTStage() noexcept;

  void Init();
  void AddActor(PLAAGTActor *aAgent);
  void PrintActors() const;

  void AddListener(GRAOBJListener<PLAAGTStage, FunctionCode> *aListener)
  { _listeners.push_back(aListener); };

  void RemoveListener(GRAOBJListener<PLAAGTStage, FunctionCode> *aListener)
  { _listeners.remove(aListener); };

  void SetFunction(FunctionCode aKey,
                   const std::function<void(PLAAGTStage *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

  void RunFunction(FunctionCode aKey)
  {
    _functor.RunFunction(aKey, this);
    for (GRAOBJListener<PLAAGTStage, PLAAGTStage::FunctionCode> *listener: _listeners)
    { listener->RunListener(aKey, this); }
  };

  PLAVec3f GetSize() const;

protected:
  explicit PLAAGTStage(PLAOBJStage *aScene);

  const PLAOBJStage *GetStage() const
  { return static_cast<const PLAOBJStage *>(this->GetOwner()); }
  PLAOBJStage *RefStage() const
  { return static_cast<PLAOBJStage *>(this->RefOwner()); }

// PLAInputHandler /////////////////////////////////////////////////////////////
/*
public:
  virtual PLAInputContext *RefContextWithInput(const PLAInput &aInput) const;
*/
};


#endif //ANHR_PLAAGTSTAGE_HPP
