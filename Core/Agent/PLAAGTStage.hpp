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
  /*
  enum class FunctionCode : PLAFunctionCode
  {
    OnInit,
    OnUpdate,
    OnResize,

    kNumberOfItems,
    None = kPLAFunctionCodeNone,
  };

private:
  std::list<GRAOBJListener<const PLAAGTStage &, FunctionCode> *> _listeners =
    std::list<GRAOBJListener<const PLAAGTStage &, FunctionCode> *>();
  GRAOBJFunctor<const PLAAGTStage &, FunctionCode> _functor =
    GRAOBJFunctor<const PLAAGTStage &, FunctionCode>();
  */

public:
  /// Agent is const method only.
  //static PLAAGTStage *Create(PLAOBJStage *aScene);

  explicit PLAAGTStage(PLAOBJStage *aScene);
  virtual ~PLAAGTStage() noexcept;

  void Init() const;
  void AddActor(const PLAAGTActor &aAgent) const;
  void PrintActors() const;

  void AddListener(GRAOBJListener<PLAAGTStage, PLAOBJStage::FunctionCode> *aListener)
  //{ _listeners.push_back(aListener); };
  {
    auto owner = this->RefStage();
    owner->AddListener(aListener);
  };

  void RemoveListener(GRAOBJListener<PLAAGTStage, PLAOBJStage::FunctionCode> *aListener)
  //{ _listeners.remove(aListener); };
  {
    auto owner = this->RefStage();
    owner->RemoveListener(aListener);
  };

  void SetFunction(PLAOBJStage::FunctionCode aKey,
                   const std::function<void(PLAAGTStage)> &aFunc)
  //{ _functor.SetFunction(aKey, aFunc); };
  {
    auto owner = this->RefStage();
    owner->SetFunction(aKey, aFunc);
  };

  void RunFunction(PLAOBJStage::FunctionCode aKey)
  {
    //_functor.RunFunction(aKey, *this);//this->RefStage());
    auto owner = this->RefStage();
    owner->RunFunction(aKey);//this->RefStage());
  };

  PLAVec3f GetSize() const;

protected:
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
