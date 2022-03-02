//
// Created by Kentaro Kawai on 2022/02/25.
//

#ifndef ANHR_PLANODEHOLDER_HPP
#define ANHR_PLANODEHOLDER_HPP

class PLANode;
class PLANodeThread;

class PLANodeHolder
{
  PLANodeThread *_thread = nullptr;

public:
  PLANodeHolder();
  PLANodeHolder(PLANodeThread *aThread);
  virtual ~PLANodeHolder();

  //void AddNode(PLANode *aNode);
  //void AddNodes(const std::vector<PLANode *> &aNodes);
  void AddThread(PLANodeThread *aThread);

  void ClearNode();

  const PLANodeThread *GetNodeThread() const { return _thread; }

  /*virtual*/ void NodeDidFinish();
};

#endif //ANHR_PLANODEHOLDER_HPP
