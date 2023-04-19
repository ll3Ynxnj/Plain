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

class PLAOBJTimelineNode: public PLAObject//, private GRAOBJBinder<PLAOBJTimelineNode>::Item
{
  //using Item = GRAOBJBinder<PLAOBJTimelineNode>::Item;
  //using Error = GRAOBJBinder<PLAOBJTimelineNode>::Error;

public:
  /// \~english Function to be executed at a specific point in time.
  /// \~japanese 特定の時点で実行される関数
  /*
  enum class FunctionCode: PLAFunctionCode
  {
    OnStart,  ///< \~english Runs before first update. \~japanese 初回の更新より前に実行。
    OnUpdate, ///< \~english Runs on every update. \~japanese 毎回の更新時に実行。
    OnStop,   ///< \~english Runs after last update. \~japanese 最後の更新より後に実行。

    kNumberOfItems,
    None = kPLAFunctionCodeNone,
  };
  */

  enum class Type
  {
    Motion,

    None,
  };

private:
  GRAOBJFunctor<PLAOBJTimelineNode *, PLAFunctionCode::TimelineNode> _functor =
    GRAOBJFunctor<PLAOBJTimelineNode *, PLAFunctionCode::TimelineNode>();
  Type _type = Type::None;
  PLAInt _steps = 0;
  PLAInt _length = 1;
  PLAOBJTimeline *_timeline = nullptr;

public:
  static PLAOBJTimelineNode *Create(PLAOBJTimelineNode::Type aType);

  void Bind() override;
  void Unbind() override;

  PLAOBJTimelineNode();
  PLAOBJTimelineNode(PLAOBJTimelineNode::Type aType);
  PLAOBJTimelineNode(PLAOBJTimelineNode::Type aType, PLAInt aLength);
  PLAOBJTimelineNode(PLAOBJTimelineNode::Type aType, PLAInt aLength, const PLAString &aName);
  ~PLAOBJTimelineNode() override;

  void Update();

  PLABool IsFinished() const;
  Type GetNodeType() const { return _type; };
  PLAInt GetSteps() const { return _steps; };
  PLAInt GetLength() const { return _length; };
  PLAFloat GetProgress() const
  { return static_cast<PLAFloat>(_steps) / static_cast<PLAFloat>(_length); };

  void SetThread(PLAOBJTimeline *aThread) { _timeline = aThread; }
  //void SetInfinity(PLABool aInfinity) { _infinity = aInfinity; }
  void SetFunction(PLAFunctionCode::TimelineNode aKey,
                   const std::function<void(PLAOBJTimelineNode *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

private:
  void OnStart();
  void OnUpdate();
  void OnStop();
};

#endif //ANHR_PLAOBJTIMELINENODE_HPP
