//
// Created by Kentaro Kawai on 2023/05/20.
//

#ifndef ANHR_PLAOBJPHASE_HPP
#define ANHR_PLAOBJPHASE_HPP


#include <list>

#include "Object/PLAObject.hpp"

#include "Grain/Object/GRAOBJBinder.hpp"
#include "Grain/Object/GRAOBJListener.hpp"

#include "PLAFunctionCode.hpp"
#include "Grain/Object/GRAOBJListener.hpp"

class PLAAGTPhase;

class PLAOBJPhase : public PLAObject
{
  std::stack<PLAOBJPhase *>_phases = std::stack<PLAOBJPhase *>();
  PLAOBJPhase *_poppedPhase = nullptr;

public:
  using Listener = GRAOBJListener<PLAAGTPhase, PLAFunctionCode::Phase>;
  using Functor = GRAOBJFunctor<PLAAGTPhase, PLAFunctionCode::Phase>;

private:
  std::list<Listener *> _listeners = std::list<Listener *>();
  Functor _functor = Functor();

public:
  static PLAOBJPhase *Create();
  static PLAOBJPhase *Object(const PLAString &aName);
  static PLAOBJPhase *Object(PLAId aId);
  static PLABool IsValidPath(const PLAString &aPath);

  PLAOBJPhase();
  explicit PLAOBJPhase(PLAString aName);
  ~PLAOBJPhase();

  void Init();

  PLAAGTPhase AssignAgent();

  void AddListener(GRAOBJListener<PLAAGTPhase, PLAFunctionCode::Phase> *aListener);
  void RemoveListener(GRAOBJListener<PLAAGTPhase, PLAFunctionCode::Phase> *aListener);
  void SetFunction(PLAFunctionCode::Phase aKey,
                   const std::function<void(PLAAGTPhase)> &aFunc);

  void PushChild(PLAOBJPhase *aPhase);
  //void PushChild(const PLAString &aPath, PLAOBJPhase *aPhase);
  void PopChild();
  //void PopChild(const PLAString &aPath);

  const PLAOBJPhase *GetCurrentPhase() const { return _phases.top(); };
  PLAOBJPhase *RefCurrentPhase() const { return _phases.top(); };

  void PrintPhases() const;

private:
  void RunFunction(PLAFunctionCode::Phase aKey);
};


#endif //ANHR_PLAOBJPHASE_HPP
