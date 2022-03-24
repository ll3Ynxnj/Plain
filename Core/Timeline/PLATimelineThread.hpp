//
// Created by Kentaro Kawai on 2022/02/25.
//

#ifndef ANHR_PLATIMELINETHREAD_HPP
#define ANHR_PLATIMELINETHREAD_HPP

#include "Timeline/PLATimelineNode.hpp";
#include "Timeline/PLATimeline.hpp";

static PLAString DBG_PLANode_Update_Indent = "";

class PLATimelineThread: public PLAObject
{
  PLATimelineThread *_parent = nullptr;
  std::vector<PLATimelineNode *>_nodes = std::vector<PLATimelineNode *>(0);
  std::vector<PLATimelineThread *>_threads = std::vector<PLATimelineThread *>(0);
  PLAUInt _current = 0;
  PLATimeline *_holder = nullptr;

public:
  static PLATimelineThread *Create(PLATimelineThread *aParent);

  PLATimelineThread(PLATimelineThread *aParent);
  virtual ~PLATimelineThread() override;

  void Update();

  void AddNode(PLATimelineNode *aNode);
  void AddThread(PLATimelineThread *aNode);
  void Clear();

  void OnFinishNode();
  void OnFinishThread();

  bool IsFinished() const;
  virtual const PLATimelineNode *GetCurrentNode() const;
  const std::vector<PLATimelineThread *> &GetThreads() const { return _threads; }

  void SetHolder(PLATimeline *aHolder) { _holder = aHolder; };

  void PrintNodes() const;
};




#endif //ANHR_PLATIMELINETHREAD_HPP
