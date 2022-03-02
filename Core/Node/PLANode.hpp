/**
 * @class PLANode
 * @brief
 * \~english Represents a process that is executed in chronological order.
 * \~japanese 時系列で実行される処理を表現します。
 * @author Kentaro Kawai
 * @date 2021/08/13
 */

#ifndef ANHR_PLANODE_HPP
#define ANHR_PLANODE_HPP

#include <vector>
#include "Grain/GRAFunctor.hpp"
#include "Type/PLAType.hpp"
#include "PLAObject.hpp"

class PLANodeThread;

class PLANode: public PLAObject, private GRABinder<PLANode>::Item
{
  using Item = GRABinder<PLANode>::Item;
  using Error = GRABinder<PLANode>::Error;

// PLANode /////////////////////////////////////////////////////////////////////
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
  GRAFunctor<PLANode, FunctionCode> _functor =
    GRAFunctor<PLANode, FunctionCode>();
  Type _type = Type::None;
  PLAInt _steps = 0;
  PLAInt _length = 1;
  PLABool _infinity = false;
  PLANodeThread *_thread = nullptr;

public:
  static PLANode *Create(PLANode::Type aType);
  //static PLANode *Create(PLANode::Type aType, Holder *aHolder);

  void Bind() override;

  PLANode();
  PLANode(PLANode::Type aType);
  PLANode(PLANode::Type aType, PLAInt aLength);
  PLANode(PLANode::Type aType, PLAInt aLength, const PLAString &aName);
  ~PLANode() override;

  void Update();

  PLABool IsFinished() const;
  Type GetNodeType() const { return _type; };
  PLAInt GetSteps() const { return _steps; };
  PLAInt GetLength() const { return _length; };
  PLAFloat GetProgress() const
  { return static_cast<PLAFloat>(_steps) / static_cast<PLAFloat>(_length); };

  void SetThread(PLANodeThread *aThread) { _thread = aThread; }
  void SetInfinity(PLABool aInfinity) { _infinity = aInfinity; }
  void SetFunction(FunctionCode aKey,
                   const std::function<void(PLANode *)> &aFunc)
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
  class Manager: public GRABinder<PLANode>
  {
    static Manager _instance;

  public:
    static Manager *Instance() { return &_instance; };
    static PLANode *Node(const std::string &aKey);

    Manager();
    ~Manager();

    const PLANode *GetNode(const std::string &aName) const;
    void PrintNodes() const;
  };
  */
};

#endif //ANHR_PLANODE_HPP
