//
// Created by Kentaro Kawai on 2022/02/25.
//

#ifndef ANHR_PLANODETHREAD_HPP
#define ANHR_PLANODETHREAD_HPP

#include "Node/PLANode.hpp";
#include "Node/PLANodeHolder.hpp";

static PLAString DBG_PLANode_Update_Indent = "";

class PLANodeThread: public PLAObject
{
  PLANodeThread *_parent = nullptr;
  std::vector<PLANode *>_nodes = std::vector<PLANode *>(0);
  std::vector<PLANodeThread *>_threads = std::vector<PLANodeThread *>(0);
  PLAUInt _current = 0;
  PLANodeHolder *_holder = nullptr;

public:
  static PLANodeThread *Create(PLANodeThread *aParent);

  PLANodeThread(PLANodeThread *aParent);
  virtual ~PLANodeThread() override;

  void Update();

  void AddNode(PLANode *aNode);
  void AddThread(PLANodeThread *aNode);
  void Clear();

  void OnFinishNode();
  void OnFinishThread();
  //void OnFinishQueue();
  //void OnFinishSubNode();

  bool IsFinished() const;
  virtual const PLANode *GetCurrentNode() const;
  const std::vector<PLANodeThread *> &GetThreads() const { return _threads; }

  //void SetInfinity(PLABool aBool) { _nodes[_current]->SetInfinity(aBool); }
  void SetHolder(PLANodeHolder *aHolder) { _holder = aHolder; };

  void PrintNodes() const;
};




#endif //ANHR_PLANODETHREAD_HPP
