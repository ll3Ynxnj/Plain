#ifndef PLAIN_ENGINE_PLAOBJSCENE_HPP
#define PLAIN_ENGINE_PLAOBJSCENE_HPP

#include <stack>
#include <list>
#include "PLAObject.hpp"
#include "Object/Input/PLAInput.hpp"
#include "Grain/Object/GRAOBJBinder.hpp"
#include "Grain/Object/GRAOBJListener.hpp"

#include "PLAFunctionCode.hpp"

class PLAOBJActor;
class PLAAGTScene;

class PLAOBJScene final :
  public PLAObject, public GRAOBJBinder<PLAOBJActor>
{
public:
  using Listener = GRAOBJListener<PLAOBJScene *, PLAFunctionCode::Scene>;
  using Functor = GRAOBJFunctor<PLAOBJScene *, PLAFunctionCode::Scene>;

private:
  std::list<Listener *> _listeners = std::list<Listener *>();
  Functor _functor = Functor();

protected:
  PLAOBJScene();

public:
  static PLAOBJScene *Create();
  static PLAOBJScene *Object(const PLAString &aName);
  static PLAOBJScene *Object(PLAId aId);

  virtual ~PLAOBJScene();

  void AddActor(PLAOBJActor *aActor);
  void RemoveActor(PLAOBJActor *aActor);
  const PLAOBJActor *GetActor(const PLAString &aName) const;
  PLAOBJActor *RefActor(const PLAString &aName) const;

  void Init();
  void Update();
  void Appear();
  void Disappear();

  PLAAGTScene AssignAgent();

  void AddListener(GRAOBJListener<PLAOBJScene *, PLAFunctionCode::Scene> *aListener)
  { _listeners.push_back(aListener); };

  void RemoveListener(GRAOBJListener<PLAOBJScene *, PLAFunctionCode::Scene> *aListener)
  { _listeners.remove(aListener); };

  void SetFunction(PLAFunctionCode::Scene aKey,
                   const std::function<void(PLAOBJScene *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

  // Agent /////////////////////////////////////////////////////////////////////

  //const PLAAGTScene *AssignAgent();

  // Manager ///////////////////////////////////////////////////////////////////
public:
  class Manager final {
    static Manager _instance;
    std::stack<PLAOBJScene *>_scenes = std::stack<PLAOBJScene *>();

  public:
    static Manager *Instance() { return &_instance; };

    void Init();

    const PLAOBJScene *GetCurrentScene() const { return _scenes.top(); };
    PLAOBJScene *RefCurrentScene() const { return _scenes.top(); };
    void PushScene(PLAOBJScene *aScene) { _scenes.push(aScene); };
    void PopScene() { _scenes.pop(); }
  };
};

#endif //PLAIN_ENGINE_PLAOBJSCENE_HPP
