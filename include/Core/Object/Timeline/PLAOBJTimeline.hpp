//
// Created by Kentaro Kawai on 2022/02/25.
//

#ifndef ANHR_PLAOBJTIMELINE_HPP
#define ANHR_PLAOBJTIMELINE_HPP

#include "Core/Object/Timeline/PLAOBJTimelineNode.hpp"
#include "Core/Object/Timeline/PLATimelineHolder.hpp"

//static PLAString DBG_PLAOBJTimeline_Update_Indent = "";

class PLAAGTTimeline;

class PLAOBJTimeline: public PLAObject
{
  using Functor = GRAOBJFunctor<PLAAGTTimeline, PLAFunctionCode::Timeline>;

  PLAOBJTimeline *_parent = nullptr;
  std::vector<PLAOBJTimelineNode *> _nodes = {};
  std::map<PLAId, PLAOBJTimeline *> _threads = {};
  std::vector<PLAId> _finishedThreadKeys = {};
  PLAUInt _current = 0;
  PLAInt _steps = 0;
  PLATimelineHolder *_holder = nullptr;
  Functor _functor = Functor();

public:
  static PLAOBJTimeline *Object(const PLAString &aName);
  static PLAOBJTimeline *Object(PLAId aId);
  static PLAOBJTimeline *Create(PLAOBJTimeline *aParent);
  static PLAOBJTimeline *Create(PLAOBJTimeline *aParent, const PLAString &aName);

  PLAOBJTimeline(PLAObjectType aType);
  PLAOBJTimeline(PLAObjectType aType, const PLAString &aName);
  PLAOBJTimeline(PLAObjectType aType, PLAOBJTimeline *aParent);
  PLAOBJTimeline(PLAObjectType aType, PLAOBJTimeline *aParent, const PLAString &aName);
  virtual ~PLAOBJTimeline() noexcept;

  void Update();

  void AddNode(PLAOBJTimelineNode *aNode);
  void AddThread(PLAOBJTimeline *aThread);
  void Clear();

  PLAAGTTimeline AssignAgent();

  void OnFinishNode();
  void OnFinishThread(const PLAOBJTimeline *aThread);
  //void OnUnbindThread(const PLAOBJTimeline *aThread);

  bool IsFinished() const;
  virtual const PLAOBJTimelineNode *GetCurrentNode() const;
  const std::map<PLAId, PLAOBJTimeline *> &GetThreads() const { return _threads; }

  void SetHolder(PLATimelineHolder *aHolder) { _holder = aHolder; };
  void SetFunction(PLAFunctionCode::Timeline aKey,
                   const std::function<void(PLAAGTTimeline)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

  void PrintNodes() const;

private:
  void OnStart();
  void OnUpdate();
  void OnStop();
};




#endif //ANHR_PLAOBJTIMELINE_HPP
