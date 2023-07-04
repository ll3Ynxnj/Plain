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

class PLAOBJPhase : public PLAObject, private GRAOBJBinder<PLAOBJPhase>::Item
{
  using Binder = GRAOBJBinder<PLAOBJPhase>;
  static const std::map<Binder::Error, const char *> kBinderErrorMessages;

  std::stack<PLAOBJPhase *>_phases = std::stack<PLAOBJPhase *>();
  PLAOBJPhase *_poppedPhase = nullptr;

public:
  using PLAPhaseItem = GRAOBJBinder<PLAOBJPhase>::Item;
  using PLAPhaseError = GRAOBJBinder<PLAOBJPhase>::Error;
  using Listener = GRAOBJListener<PLAAGTPhase, PLAFunctionCode::Phase>;
  using Functor = GRAOBJFunctor<PLAAGTPhase, PLAFunctionCode::Phase>;

private:
  std::list<Listener *> _listeners = std::list<Listener *>();
  Functor _functor = Functor();

public:
  static const char *GetBinderErrorMessage(Binder::Error aError);
  static PLAOBJPhase *Create();
  static PLAOBJPhase *CreateWithTag(PLAId aTag);
  static PLAOBJPhase *Object(const PLAString &aName);
  static PLAOBJPhase *Object(PLAId aId);
  static PLAOBJPhase *ObjectWithTag(PLAId aTag);
  static PLABool IsValidPath(const PLAString &aPath);
  void Bind() override;

protected:
  void Unbind() override;

public:
  PLAOBJPhase();
  explicit PLAOBJPhase(PLAId aTag);
  PLAOBJPhase(PLAId aTag, PLAString aName);
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

  const char *GetPhaseTypeName() const;

  PLAId GetPhaseTag() const;
  void SetPhaseTag(PLAId aTag);

private:
  void RunFunction(PLAFunctionCode::Phase aKey);

  //-- GRAOBJBinder::Item --/////////////////////////////////////////////////////////
private:
  const char *GetBinderItemTypeName() const override;

  // Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRAOBJBinder<PLAOBJPhase>
  {
    static Manager _instance;

    Manager();

  public:
    static Manager *Instance() { return &_instance; };
    static PLAOBJPhase *Phase(const PLAString &aKey);

    ~Manager();

    void Init();

    const PLAOBJPhase *GetPhase(const PLAString &aName) const;
    void PrintPhases() const;
  };
};


#endif //ANHR_PLAOBJPHASE_HPP
