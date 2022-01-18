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

class PLANode: public PLAObject
{
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
  std::vector<PLANode *>_main = std::vector<PLANode *>();
  std::vector<PLANode *>_branch = std::vector<PLANode *>();
  //std::vector<PLANode *>::iterator _current = _main.begin();
  PLAUInt _current = 0;

public:
  static PLANode *Create(PLAInt aLength);
  static PLANode *Create(PLAInt aLength, const PLAString &aName);

  PLANode();
  PLANode(PLAInt aLength);
  PLANode(PLAInt aLength, const PLAString &aName);
  ~PLANode();

  virtual void Update();

  void AddMain(PLANode *aNode);
  void AddBranch(PLANode *aNode);

  PLAInt GetSteps() const { return _steps; };
  PLAInt GetLength() const { return _length; };
  PLAFloat GetProgress() const
  { return static_cast<PLAFloat>(_steps) / static_cast<PLAFloat>(_length); };

  void SetFunction(FunctionCode aKey,
                   const std::function<void(PLANode *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

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
};

#endif //ANHR_PLANODE_HPP
