//
// Created by Kentaro Kawai on 2023/05/20.
//

#ifndef ANHR_PLAOBJPHASE_HPP
#define ANHR_PLAOBJPHASE_HPP


#include <list>

#include "Object/PLAObject.hpp"

#include "PLAFunctionCode.hpp"
#include "Grain/Object/GRAOBJListener.hpp"

class PLAAGTPhase;

class PLAOBJPhase : public PLAObject
{
  std::stack<PLAOBJPhase *>_phases = std::stack<PLAOBJPhase *>();

public:
  using Listener = GRAOBJListener<PLAOBJPhase *, PLAFunctionCode::Phase>;
  using Functor = GRAOBJFunctor<PLAOBJPhase *, PLAFunctionCode::Phase>;

private:
  std::list<Listener *> _listeners = std::list<Listener *>();
  Functor _functor = Functor();

public:
  static PLAOBJPhase *Create();
  static PLAOBJPhase *Object(const PLAString &aName);
  static PLAOBJPhase *Object(PLAId aId);

  PLAOBJPhase();
  explicit PLAOBJPhase(PLAString aName);
  ~PLAOBJPhase();

  void Init();

  PLAAGTPhase AssignAgent();

  const PLAOBJPhase *GetCurrentPhase() const { return _phases.top(); };
  PLAOBJPhase *RefCurrentPhase() const { return _phases.top(); };
  void PushPhase(PLAOBJPhase *aPhase) { _phases.push(aPhase); };
  void PopPhase() { _phases.pop(); }

  void PrintPhases() const;

protected:
  void AddListener(GRAOBJListener<PLAOBJPhase *, PLAFunctionCode::Phase> *aListener)
  { _listeners.push_back(aListener); };

  void RemoveListener(GRAOBJListener<PLAOBJPhase *, PLAFunctionCode::Phase> *aListener)
  { _listeners.remove(aListener); };

  void SetFunction(PLAFunctionCode::Phase aKey,
                   const std::function<void(PLAOBJPhase *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };
};


#endif //ANHR_PLAOBJPHASE_HPP
