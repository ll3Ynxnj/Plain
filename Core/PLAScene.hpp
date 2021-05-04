//
// Created by Kentaro Kawai on 2021/01/28.
//

#ifndef ANHR_PLASCENE_HPP
#define ANHR_PLASCENE_HPP

#include <stack>
#include <list>
#include "PLAObject.hpp"
#include "Grain/GRAFunctor.hpp"
#include "Grain/GRAListener.hpp"

class PLAScene : public PLAObject
{
public:
  enum class FunctionCode : PLACode
  {
    OnInit,
    OnUpdate,
    OnAppear,
    OnDisappear,

    kNumberOfItems,
    None,
  };

private:
  std::list<GRAListener<PLAScene, FunctionCode> *> _listeners = std::list<GRAListener<PLAScene, FunctionCode> *>();
  GRAFunctor<PLAScene, FunctionCode> _functor = GRAFunctor<PLAScene, FunctionCode>();

protected:
  PLAScene();

public:
  static PLAScene *Create();

  virtual ~PLAScene();

  void Init() {
    _functor.RunFunction(FunctionCode::OnInit, this);
    for (GRAListener<PLAScene, FunctionCode> *listener: _listeners)
    { listener->RunListener(FunctionCode::OnInit, this); }
  };

  void Update() {
    _functor.RunFunction(FunctionCode::OnUpdate, this);
    for (GRAListener<PLAScene, FunctionCode> *listener: _listeners)
    { listener->RunListener(FunctionCode::OnUpdate, this); }
  };

  void Appear() {
    _functor.RunFunction(FunctionCode::OnAppear, this);
    for (GRAListener<PLAScene, FunctionCode> *listener: _listeners)
    { listener->RunListener(FunctionCode::OnAppear, this); }
  };

  void Disappear() {
    _functor.RunFunction(FunctionCode::OnDisappear, this);
    for (GRAListener<PLAScene, FunctionCode> *listener: _listeners)
    { listener->RunListener(FunctionCode::OnDisappear, this); }
  };

  void AddListener(GRAListener<PLAScene, FunctionCode> *aListener) {
    _listeners.push_back(aListener);
  };

  void RemoveActor(GRAListener<PLAScene, FunctionCode> *aListener) {
    _listeners.remove(aListener);
  };

  void SetFunctionOfScene(FunctionCode aKey,
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
