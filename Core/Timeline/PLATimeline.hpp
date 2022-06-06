//
// Created by Kentaro Kawai on 2022/02/25.
//

#ifndef ANHR_PLATIMELINE_HPP
#define ANHR_PLATIMELINE_HPP

#include "Timeline/PLATimelineNode.hpp"
#include "Timeline/PLATimelineHolder.hpp"

static PLAString DBG_PLANode_Update_Indent = "";

class PLATimeline: public PLAObject
{
  PLATimeline *_parent = nullptr;
  std::vector<PLATimelineNode *> _nodes = {};
  std::map<PLAId, PLATimeline *> _threads = {};
  std::vector<PLAId> _finishedThreadKeys = {};
  PLAUInt _current = 0;
  PLATimelineHolder *_holder = nullptr;

public:
  static PLATimeline *Create(PLATimeline *aParent);

  PLATimeline(PLATimeline *aParent);
  virtual ~PLATimeline() noexcept;

  void Update();

  void AddNode(PLATimelineNode *aNode);
  void AddThread(PLATimeline *aNode);
  void Clear();

  void OnFinishNode();
  void OnFinishThread(const PLATimeline *aThread);
  //void OnUnbindThread(const PLATimeline *aThread);

  bool IsFinished() const;
  virtual const PLATimelineNode *GetCurrentNode() const;
  const std::map<PLAId, PLATimeline *> &GetThreads() const { return _threads; }

  void SetHolder(PLATimelineHolder *aHolder) { _holder = aHolder; };

  void PrintNodes() const;
};




#endif //ANHR_PLATIMELINE_HPP
