//
// Created by Kentaro Kawai on 2021/08/13.
//

#ifndef ANHR_PLANODE_HPP
#define ANHR_PLANODE_HPP

#include <vector>
#include "Grain/GRAFunctor.hpp"
#include "Type/PLAType.hpp"
#include "PLAObject.hpp"

class PLANode: public PLAObject
{
public:
  enum class FunctionCode : PLAFunctionCode
  {
    OnStart,
    OnUpdate,
    OnStop,

    kNumberOfItems,
    None = kPLAFunctionCodeNone,
  };

private:
  GRAFunctor<PLANode, FunctionCode> _functor =
    GRAFunctor<PLANode, FunctionCode>();
  PLAInt _steps = 0;
  PLAInt _length = 0;
  PLANode *_parent = nullptr;
  std::vector<PLANode *>_main = std::vector<PLANode *>();
  std::vector<PLANode *>_branch = std::vector<PLANode *>();
  std::vector<PLANode *>::iterator _current = _main.begin();

public:
  static PLANode *Create(PLAInt aLength);

  PLANode();
  PLANode(PLAInt aLength);
  ~PLANode();

  virtual void Update();

  void AddMain(PLANode *aNode);
  void AddBranch(PLANode *aNode);

  PLAInt GetSteps() const { return _steps; };
  PLAInt GetLength() const { return _length; };
  PLAFloat GetProgress() const
  { return static_cast<PLAFloat>(_steps) / static_cast<PLAFloat>(_length); };

  void SetFunction(FunctionCode aKey,
                   const std::function<void(PLANode *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

private:
  void OnFinishCurrent();
  void OnFinishMain();
  void OnFinishBranch();
};

#endif //ANHR_PLANODE_HPP
