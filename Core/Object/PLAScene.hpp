#ifndef PLAIN_PLASCENE_HPP
#define PLAIN_PLASCENE_HPP

#include <stack>
#include <list>
#include "PLAObject.hpp"
#include "Object/Input/PLAInput.hpp"
#include "Grain/Object/GRABinder.hpp"
#include "Grain/Object/GRAListener.hpp"

class PLAActor;
class PLAAGTScene;

class PLAScene final :
  public PLAObject, public GRABinder<PLAActor>
{
public:
  enum class FunctionCode : PLAFunctionCode
  {
    OnInit,
    OnUpdate,
    OnAppear,
    OnDisappear,

    kNumberOfItems,
    None = kPLAFunctionCodeNone,
  };

private:
  std::list<GRAListener<PLAScene, FunctionCode> *> _listeners =
    std::list<GRAListener<PLAScene, FunctionCode> *>();
  GRAFunctor<PLAScene, FunctionCode> _functor =
    GRAFunctor<PLAScene, FunctionCode>();

protected:
  PLAScene();

public:
  static PLAScene *Create();
  static PLAScene *Scene(const PLAString &aName);
  static PLAScene *Scene(PLAId aId);

  virtual ~PLAScene();

  void AddActor(PLAActor *aActor);
  void RemoveActor(PLAActor *aActor);
  const PLAActor *GetActor(const PLAString &aName) const;
  PLAActor *RefActor(const PLAString &aName) const;

  void Init();
  void Update();
  void Appear();
  void Disappear();

  void AddListener(GRAListener<PLAScene, FunctionCode> *aListener)
  { _listeners.push_back(aListener); };

  void RemoveListener(GRAListener<PLAScene, FunctionCode> *aListener)
  { _listeners.remove(aListener); };

  void SetFunction(FunctionCode aKey,
                   const std::function<void(PLAScene *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

  // Agent /////////////////////////////////////////////////////////////////////

  //const PLAAGTScene *AssignAgent();

  // Manager ///////////////////////////////////////////////////////////////////
public:
  class Manager final {
    static Manager _instance;
    std::stack<PLAScene *>_scenes = std::stack<PLAScene *>();

  public:
    static Manager *Instance() { return &_instance; };

    void Init();

    const PLAScene *GetCurrentScene() const { return _scenes.top(); };
    PLAScene *RefCurrentScene() const { return _scenes.top(); };
    void PushScene(PLAScene *aScene) { _scenes.push(aScene); };
    void PopScene() { _scenes.pop(); }
  };
};

#endif //PLAIN_PLASCENE_HPP
