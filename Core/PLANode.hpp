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

class PLANode: public PLAObject, private GRABinder<PLANode>::Item
{
  using Item = GRABinder<PLANode>::Item;
  using Error = GRABinder<PLANode>::Error;

// PLANode::Holder /////////////////////////////////////////////////////////////
public:
  class Holder
  {
    PLANode *_node = nullptr;

  public:
    Holder();
    //Holder() = delete;
    Holder(PLANode *aNode);

    void AddNode(PLANode *aNode);
    void AddNodes(const std::vector<PLANode *> &aNodes);
    void AddNodeThread(PLANode *aNode);

    void ClearNode();

    const PLANode *GetNode() const;

    virtual void NodeDidFinish();
  };

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
  PLAInt _length = 0;
  PLANode *_parent = nullptr;
  std::vector<PLANode *>_queue = std::vector<PLANode *>(0);
  std::vector<PLANode *>_subNodes = std::vector<PLANode *>(0);
  PLAUInt _current = 0;
  Holder *_holder = nullptr;

public:
  static PLANode *Create(PLANode::Type aType);
  static PLANode *Create(PLANode::Type aType, Holder *aHolder);

  void Bind() override;

  PLANode();
  PLANode(PLANode::Type aType);
  PLANode(PLANode::Type aType, PLAInt aLength);
  PLANode(PLANode::Type aType, PLAInt aLength, const PLAString &aName);
  ~PLANode() override;

  void Update();

  void AddQueue(PLANode *aNode);
  void AddSubNode(PLANode *aNode);

  void Clear();

  Type GetNodeType() const { return _type; };
  PLAInt GetSteps() const { return _steps; };
  PLAInt GetLength() const { return _length; };
  PLAFloat GetProgress() const
  { return static_cast<PLAFloat>(_steps) / static_cast<PLAFloat>(_length); };

  void SetFunction(FunctionCode aKey,
                   const std::function<void(PLANode *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

  void PrintNode() const;

protected:
  void Unbind() override;

  virtual const PLANode *GetCurrentNode() const;
  const std::vector<PLANode *> &GetBranch() const;

private:
  void OnStart();
  void OnUpdate();
  void OnStop();
  void OnFinishCurrent();
  void OnFinishMain();
  void OnFinishBranch();

  bool IsFinished() const;

// Manager /////////////////////////////////////////////////////////////////////
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
};

#endif //ANHR_PLANODE_HPP
