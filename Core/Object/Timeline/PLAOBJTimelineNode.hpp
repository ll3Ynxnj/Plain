/**
 * @class PLAOBJTimelineNode
 * @brief
 * \~english Represents a process that is executed in chronological order.
 * \~japanese 時系列で実行される処理を表現します。
 * @author Kentaro Kawai
 * @date 2021/08/13
 */

#ifndef ANHR_PLAOBJTIMELINENODE_HPP
#define ANHR_PLAOBJTIMELINENODE_HPP

#include <vector>
#include "Grain/Object/GRAOBJFunctor.hpp"
#include "Primitive/PLAPRMType.hpp"
#include "Object/PLAObject.hpp"

#include "PLAOBJTimelineNode.hpp"
#include "PLAFunctionCode.hpp"

class PLAOBJTimeline;
class PLAAGTTimelineNode;

class PLAOBJTimelineNode: public PLAObject//, private GRAOBJBinder<PLAOBJTimelineNode>::Item
{
  using Functor = GRAOBJFunctor<PLAAGTTimelineNode, PLAFunctionCode::TimelineNode>;

public:
  enum class Type
  {
    Motion,

    None,
  };

private:
  Functor _functor = Functor();
  Type _type = Type::None;
  PLAInt _steps = 0;
  PLAInt _length = 1;
  PLAOBJTimeline *_timeline = nullptr;

public:
  static PLAOBJTimelineNode *Object(const PLAString &aName);
  static PLAOBJTimelineNode *Object(PLAId aId);
  static PLAOBJTimelineNode *Create(PLAOBJTimelineNode::Type aType);
  static PLAOBJTimelineNode *Create(PLAOBJTimelineNode::Type aType,
                                    PLAInt aLength);
  static PLAOBJTimelineNode *Create(PLAOBJTimelineNode::Type aType,
                                    PLAInt aLength, const PLAString &aName);

  void Bind() override;
  void Unbind() override;

  PLAOBJTimelineNode();
  PLAOBJTimelineNode(PLAOBJTimelineNode::Type aType);
  PLAOBJTimelineNode(PLAOBJTimelineNode::Type aType, PLAInt aLength);
  PLAOBJTimelineNode(PLAOBJTimelineNode::Type aType, PLAInt aLength,
                     const PLAString &aName);
  ~PLAOBJTimelineNode() override;

  void Update();

  PLAAGTTimelineNode AssignAgent();

  PLABool IsFinished() const;
  Type GetNodeType() const { return _type; };
  PLAInt GetSteps() const { return _steps; };
  PLAInt GetLength() const { return _length; };
  PLAFloat GetProgress() const
  { return static_cast<PLAFloat>(_steps) / static_cast<PLAFloat>(_length); };

  void SetThread(PLAOBJTimeline *aThread) { _timeline = aThread; }
  //void SetInfinity(PLABool aInfinity) { _infinity = aInfinity; }
  void SetFunction(PLAFunctionCode::TimelineNode aKey,
                   const std::function<void(PLAAGTTimelineNode)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

private:
  void OnStart();
  void OnUpdate();
  void OnStop();
};

#endif //ANHR_PLAOBJTIMELINENODE_HPP
