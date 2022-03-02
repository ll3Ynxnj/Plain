//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "PLANodeHolder.hpp"
#include "PLANodeThread.hpp"
#include "PLAApp.hpp"

// PLANode::Holder /////////////////////////////////////////////////////////////

PLANodeHolder::PLANodeHolder()
{

}

PLANodeHolder::PLANodeHolder(PLANodeThread *aThread):
  _thread(aThread)
{
  PLAApp::Instance()->AddNodeThread(aThread);
}

PLANodeHolder::~PLANodeHolder() noexcept
{

}

/*
void PLANodeHolder::AddNode(PLANode *aNode)
{
  if (!_thread) {
    _thread = PLANodeThread::Create(nullptr);
    _thread->SetHolder(this);
    PLAApp::Instance()->AddNodeThread(_thread);
  }
  _thread->AddNode(aNode);
}

void PLANodeHolder::AddNodes(const std::vector<PLANode *> &aNodes)
{
  for (PLANode *node: aNodes) {
    this->AddNode(node);
  }
}
*/

void PLANodeHolder::AddThread(PLANodeThread *aThread)
{
  if (!_thread) {
    _thread = PLANodeThread::Create(nullptr);
    _thread->SetHolder(this);
    PLAApp::Instance()->AddNodeThread(_thread);
  }
  _thread->AddThread(aThread);
}

void PLANodeHolder::ClearNode()
{
  _thread->Clear();
}

/*
const PLANodeThread *PLANodeHolder::GetThread() const
{
  return _thread;
}
 */

void PLANodeHolder::NodeDidFinish()
{
  PLAObject::Destroy(_thread);
  _thread = nullptr;
}
