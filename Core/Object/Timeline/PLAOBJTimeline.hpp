//
// Created by Kentaro Kawai on 2022/02/25.
//

#ifndef ANHR_PLAOBJTIMELINE_HPP
#define ANHR_PLAOBJTIMELINE_HPP

#include "PLAOBJTimelineNode.hpp"
#include "PLATimelineHolder.hpp"

static PLAString DBG_PLANode_Update_Indent = "";

class PLAOBJTimeline: public PLAObject
{
  PLAOBJTimeline *_parent = nullptr;
  std::vector<PLAOBJTimelineNode *> _nodes = {};
  std::map<PLAId, PLAOBJTimeline *> _threads = {};
  std::vector<PLAId> _finishedThreadKeys = {};
  PLAUInt _current = 0;
  PLATimelineHolder *_holder = nullptr;

public:
  static PLAOBJTimeline *Create(PLAOBJTimeline *aParent);

  PLAOBJTimeline(PLAOBJTimeline *aParent);
  virtual ~PLAOBJTimeline() noexcept;

  void Update();

  void AddNode(PLAOBJTimelineNode *aNode);
  void AddThread(PLAOBJTimeline *aThread);
  void Clear();

  void OnFinishNode();
  void OnFinishThread(const PLAOBJTimeline *aThread);
  //void OnUnbindThread(const PLAOBJTimeline *aThread);

  bool IsFinished() const;
  virtual const PLAOBJTimelineNode *GetCurrentNode() const;
  const std::map<PLAId, PLAOBJTimeline *> &GetThreads() const { return _threads; }

  void SetHolder(PLATimelineHolder *aHolder) { _holder = aHolder; };

  void PrintNodes() const;
};




#endif //ANHR_PLAOBJTIMELINE_HPP
