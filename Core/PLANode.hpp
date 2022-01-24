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

public:
  /// \~english Function to be executed at a specific point in time.
  /// \~japanese 特定の時点で実行される関数
  enum class FunctionCode : PLAFunctionCode
  {
    OnStart,  ///< \~english Runs before first update. \~japanese 初回の更新より前に実行。
    OnUpdate, ///< \~english Runs on every update. \~japanese 毎回の更新時に実行。
    OnStop,   ///< \~english Runs after last update. \~japanese 最後の更新より後に実行。

    kNumberOfItems,
    None = kPLAFunctionCodeNone,
  };

private:
  GRAFunctor<PLANode, FunctionCode> _functor =
    GRAFunctor<PLANode, FunctionCode>();
  PLAInt _steps = 0;
  PLAInt _length = 0;
  PLANode *_parent = nullptr;
  std::vector<PLANode *>_thread = std::vector<PLANode *>();
  std::vector<PLANode *>_subThreads = std::vector<PLANode *>();
  PLAUInt _current = 0;

public:
  static void Bind(PLANode *aNode);

  PLANode();
  PLANode(PLAInt aLength);
  PLANode(PLAInt aLength, const PLAString &aName);
  ~PLANode() override;

  void Update();

  void Add(PLANode *aNode);
  void AddThread(PLANode *aNode);

  PLAInt GetSteps() const { return _steps; };
  PLAInt GetLength() const { return _length; };
  PLAFloat GetProgress() const
  { return static_cast<PLAFloat>(_steps) / static_cast<PLAFloat>(_length); };

  void SetFunction(FunctionCode aKey,
                   const std::function<void(PLANode *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

  void PrintNode() const;

protected:
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

// Holder //////////////////////////////////////////////////////////////////////

public:
  class Holder
  {
    PLANode *_node = nullptr;

  public:
    Holder() = delete;
    Holder(PLANode *aNode);

    void AddNode(PLANode *aNode);
    void AddNodes(const std::vector<PLANode *> &aNodes);
    void AddThread(PLANode *aNode);

    const PLANode *GetNode() const;
  };
};

#endif //ANHR_PLANODE_HPP
