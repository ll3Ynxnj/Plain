//
// Created by Kentaro Kawai on 2021/01/28.
//

#ifndef ANHR_PLASCENE_HPP
#define ANHR_PLASCENE_HPP

#include <stack>
#include <list>
#include "PLAObject.hpp"

class PLAScene : public PLAObject
{
  // Manager ///////////////////////////////////////////////////////////////////
public:
  class Manager {
    static Manager _instance;
    std::stack<PLAScene *>_scenes = std::stack<PLAScene *>();

  public:
    static const Manager *Get() { return &_instance; };
    static Manager *Ref() { return &_instance; };

    const PLAScene *GetCurrentScene() const { return _scenes.top(); };
    PLAScene *RefCurrentScene() const { return _scenes.top(); };
    void PushScene(PLAScene *aScene) { _scenes.push(aScene); };
    void PopScene() { _scenes.pop(); }
  };

  // Delegate //////////////////////////////////////////////////////////////////
public:
  class Delegate {
    friend PLAScene;
    PLAScene *_scene = nullptr;

    enum class Functor {
      OnInit,
      OnUpdate,
      OnAppear,
      OnDisappear,
    };
   std::function<void(PLAScene *)> _fOnInitOfScene      = [](PLAScene *){};
    std::function<void(PLAScene *)> _fOnUpdateOfScene    = [](PLAScene *){};
    std::function<void(PLAScene *)> _fOnAppearOfScene    = [](PLAScene *){};
    std::function<void(PLAScene *)> _fOnDisappearOfScene = [](PLAScene *){};

  public:
    Delegate() {};
    ~Delegate() { _scene->RemoveDelegate(this); };

    void SetFunctorOnInitOfScene(const std::function<void(PLAScene *)> &aFunc)
    { _fOnInitOfScene = aFunc; };
    void SetFunctorOnUpdateOfScene(const std::function<void(PLAScene *)> &aFunc)
    { _fOnUpdateOfScene = aFunc; };
    void SetFunctorOnAppearOfScene(const std::function<void(PLAScene *)> &aFunc)
    { _fOnAppearOfScene = aFunc; };
    void SetFunctorOnDisappearOfScene(const std::function<void(PLAScene *)> &aFunc)
    { _fOnDisappearOfScene = aFunc; };
  };

public:
  enum class Functor {
    OnInit,
    OnUpdate,
    OnAppear,
    OnDisappear,
  };

private:
  std::list<Delegate *>_delegates;

  std::function<void(PLAScene *)> _fOnInit      = [](PLAScene *){};
  std::function<void(PLAScene *)> _fOnUpdate    = [](PLAScene *){};
  std::function<void(PLAScene *)> _fOnAppear    = [](PLAScene *){};
  std::function<void(PLAScene *)> _fOnDisappear = [](PLAScene *){};

public:
  static PLAScene *Create();

  PLAScene();
  virtual ~PLAScene();

  void Init() {
    _fOnInit(this);
    for (Delegate *delegate : _delegates)
    { delegate->_fOnInitOfScene(this); }
  };

  void Update() {
    _fOnUpdate(this);
    for (Delegate *delegate : _delegates)
    { delegate->_fOnUpdateOfScene(this); }
  };

  void Appear() {
    _fOnAppear(this);
    for (Delegate *delegate : _delegates)
    { delegate->_fOnAppearOfScene(this); }
  };

  void Disappear() {
    _fOnDisappear(this);
    for (Delegate *delegate : _delegates)
    { delegate->_fOnDisappearOfScene(this); }
  };

  void AddDelegate(Delegate *aDelegate) {
    _delegates.push_back(aDelegate);
  };

  void RemoveDelegate(Delegate *aDelegate) {
    _delegates.remove(aDelegate);
  }

  void SetFunctorOnInit(const std::function<void(PLAScene *)> &aFunc)
  { _fOnInit = aFunc; };
  void SetFunctorOnUpdate(const std::function<void(PLAScene *)> &aFunc)
  { _fOnUpdate = aFunc; };
  void SetFunctorOnAppear(const std::function<void(PLAScene *)> &aFunc)
  { _fOnAppear = aFunc; };
  void SetFunctorOnDisappear(const std::function<void(PLAScene *)> &aFunc)
  { _fOnDisappear = aFunc; };
};

#endif //ANHR_PLASCENE_HPP
