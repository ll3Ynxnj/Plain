/**
 * @class PLATimelineNode
 * @brief
 * \~english Represents a process that is executed in chronological order.
 * \~japanese 時系列で実行される処理を表現します。
 * @author Kentaro Kawai
 * @date 2021/08/13
 */

#ifndef ANHR_PLATIMELINENODE_HPP
#define ANHR_PLATIMELINENODE_HPP

#include <vector>
#include "Grain/GRAFunctor.hpp"
#include "Type/PLAType.hpp"
#include "PLAObject.hpp"

class PLATimelineThread;

class PLATimelineNode: public PLAObject, private GRABinder<PLATimelineNode>::Item
{
  using Item = GRABinder<PLATimelineNode>::Item;
  using Error = GRABinder<PLATimelineNode>::Error;

// PLATimelineNode /////////////////////////////////////////////////////////////////////
public:
  /// \~english Function to be executed at a specific point in time.
  /// \~japanese 特定の時点で実行される関数
  enum class FunctionCode: PLAFunctionCode
  {
    OnStart,  ///< \~english Runs before first update. \~japanese 初回の更新より前に実行。
    OnUpdate, ///< \~english Runs on every update. \~japanese 毎回の更新時に実行。
    OnStop,   ///< \~english Runs after last update. \~japanese 最後の更新より後に実行。

    kNumberOfItems,
    None = kPLAFunctionCodeNone,
  };

  enum class Type
  {
    Motion,

    None,
  };

private:
  GRAFunctor<PLATimelineNode, FunctionCode> _functor =
    GRAFunctor<PLATimelineNode, FunctionCode>();
  Type _type = Type::None;
  PLAInt _steps = 0;
  PLAInt _length = 1;
  PLABool _infinity = false;
  PLATimelineThread *_thread = nullptr;

public:
  static PLATimelineNode *Create(PLATimelineNode::Type aType);
  //static PLATimelineNode *Create(PLATimelineNode::Type aType, Holder *aHolder);

  void Bind() override;

  PLATimelineNode();
  PLATimelineNode(PLATimelineNode::Type aType);
  PLATimelineNode(PLATimelineNode::Type aType, PLAInt aLength);
  PLATimelineNode(PLATimelineNode::Type aType, PLAInt aLength, const PLAString &aName);
  ~PLATimelineNode() override;

  void Update();

  PLABool IsFinished() const;
  Type GetNodeType() const { return _type; };
  PLAInt GetSteps() const { return _steps; };
  PLAInt GetLength() const { return _length; };
  PLAFloat GetProgress() const
  { return static_cast<PLAFloat>(_steps) / static_cast<PLAFloat>(_length); };

  void SetThread(PLATimelineThread *aThread) { _thread = aThread; }
  void SetInfinity(PLABool aInfinity) { _infinity = aInfinity; }
  void SetFunction(FunctionCode aKey,
                   const std::function<void(PLATimelineNode *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

protected:
  void Unbind() override;

private:
  void OnStart();
  void OnUpdate();
  void OnStop();

// Manager /////////////////////////////////////////////////////////////////////
  /*
public:
  class Manager: public GRABinder<PLATimelineNode>
  {
    static Manager _instance;

  public:
    static Manager *Instance() { return &_instance; };
    static PLATimelineNode *Timeline(const std::string &aKey);

    Manager();
    ~Manager();

    const PLATimelineNode *GetNode(const std::string &aName) const;
    void PrintNodes() const;
  };
  */
};

#endif //ANHR_PLATIMELINENODE_HPP
