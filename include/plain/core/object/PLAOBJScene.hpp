#ifndef PLAIN_ENGINE_PLAOBJSCENE_HPP
#define PLAIN_ENGINE_PLAOBJSCENE_HPP

#include <stack>
#include <list>

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/phase/PLAOBJPhase.hpp"
#include "plain/core/PLAFunctionCode.hpp"

#include "grain/object/GRAOBJBinder.hpp"
#include "grain/object/GRAOBJListener.hpp"

class PLAAGTScene;

class PLAOBJScene final : public PLAObject
{
  PLAOBJPhase *_context = nullptr;

public:
  using Listener = GRAOBJListener<PLAAGTScene, PLAFunctionCode::Scene>;
  using Functor = GRAOBJFunctor<PLAAGTScene, PLAFunctionCode::Scene>;

private:
  std::list<Listener *> _listeners = std::list<Listener *>();
  Functor _functor = Functor();

protected:
  PLAOBJScene();
  PLAOBJScene(const PLAString &aName);

public:
  static PLAOBJScene *Create();
  static PLAOBJScene *Create(const PLAString &aName);
  static PLAOBJScene *Object(const PLAString &aName);
  static PLAOBJScene *Object(PLAId aId);

  ~PLAOBJScene();

  void Init();
  void Update();

  PLAAGTScene AssignAgent();

  void AddListener(GRAOBJListener<PLAAGTScene, PLAFunctionCode::Scene> *aListener);
  void RemoveListener(GRAOBJListener<PLAAGTScene, PLAFunctionCode::Scene> *aListener);
  void SetFunction(PLAFunctionCode::Scene aKey,
                   const std::function<void(PLAAGTScene)> &aFunc);

  void PushPhase(PLAOBJPhase *aPhase);
  //void PushPhase(const PLAString &aPath, PLAOBJPhase *aPhase);
  void PopPhase();
  //void PopPhase(const PLAString &aPath);

  const PLAOBJPhase *GetContext() const { return _context; }

  const PLAOBJPhase *GetCurrentPhase() const { return _context->GetCurrentPhase(); };
  PLAOBJPhase *RefCurrentPhase() const { return _context->RefCurrentPhase(); };

  void PrintPhases() const;

private:
  void RunFunction(PLAFunctionCode::Scene aKey);
};

#endif //PLAIN_ENGINE_PLAOBJSCENE_HPP
