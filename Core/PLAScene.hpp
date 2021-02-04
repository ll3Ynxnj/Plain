//
// Created by Kentaro Kawai on 2021/01/28.
//

#ifndef ANHR_PLASCENE_HPP
#define ANHR_PLASCENE_HPP

#include <stack>
#include <list>
#include "PLAObject.hpp"
#include "PLAFunctor.hpp"
#include "PLAListener.hpp"

class PLAScene : public PLAObject
{
  std::list<PLAListener<PLAScene> *> _listeners = std::list<PLAListener<PLAScene> *>();
  PLAFunctor<PLAScene> _functor = PLAFunctor<PLAScene>();

public:
  static PLAScene *Create();

  PLAScene();
  virtual ~PLAScene();

  void Init() {
    _functor.RunFunction("OnInit", this);
    for (PLAListener<PLAScene> *listener: _listeners)
    { listener->RunFunctionOfListener("OnInit", this); }
  };

  void Update() {
    _functor.RunFunction("OnUpdate", this);
    for (PLAListener<PLAScene> *listener: _listeners)
    { listener->RunFunctionOfListener("OnUpdate", this); }
  };

  void Appear() {
    _functor.RunFunction("OnAppear", this);
    for (PLAListener<PLAScene> *listener: _listeners)
    { listener->RunFunctionOfListener("OnAppear", this); }
  };

  void Disappear() {
    _functor.RunFunction("OnDisappear", this);
    for (PLAListener<PLAScene> *listener: _listeners)
    { listener->RunFunctionOfListener("OnDisappear", this); }
  };

  void AddListener(PLAListener<PLAScene> *aListener) {
    _listeners.push_back(aListener);
  };

  void RemoveActor(PLAListener<PLAScene> *aListener) {
    _listeners.remove(aListener);
  }

  void SetFunctionOfScene(const std::string &aKey,
                          const std::function<void(PLAScene*)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

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

};

#endif //ANHR_PLASCENE_HPP
