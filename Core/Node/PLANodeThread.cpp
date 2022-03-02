//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "PLANode.hpp"
#include "PLANodeThread.hpp"
#include "PLANodeHolder.hpp"
#include "PLAError.hpp"

PLANodeThread *PLANodeThread::Create(PLANodeThread *aParent) {
  PLANodeThread *thread = new PLANodeThread(aParent);
  thread->Bind();
  return thread;
}

PLANodeThread::PLANodeThread(PLANodeThread *aParent):
  PLAObject(PLAObjectType::NodeThread),
  _parent(aParent)
{

}

PLANodeThread::~PLANodeThread() noexcept
{

}

void PLANodeThread::Update() {

  DBG_PLANode_Update_Indent += "  ";

  //-- Update nodes.
  for (PLANodeThread *thread: _threads) {
    thread->Update();
  }
  if (_current < _nodes.size()) { _nodes[_current]->Update(); }
  /*
  GRA_PRINT("%s| %s : Update(), _current: %2d, _steps: %3d, _length: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(), _current, _steps, _length);

  DBG_PLANode_Update_Indent.erase(0, 2);
  */
}

void PLANodeThread::AddNode(PLANode *aNode)
{
  _nodes.push_back(aNode);
  aNode->SetThread(this);
}

void PLANodeThread::AddThread(PLANodeThread *aThread)
{
  aThread->_parent = this;
  _threads.push_back(aThread);
}

void PLANodeThread::Clear()
{
  GRA_PRINT("%s::Clear()\n", this->GetObjectName().c_str());
  for (PLANodeThread *thread: _threads) {
    thread->Clear();
  }
  _threads.clear();
  for (PLANode *node: _nodes) {
    PLAObject::Destroy(node);
  }
  _nodes.clear();
  GRA_PRINT("  _queue.size(): %s", _nodes.size());
  //PLAObject::Destroy(this);
}

void PLANodeThread::OnFinishNode()
{
  /*
  GRA_PRINT("%s| %s : OnFinishCurrent(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current, _steps);
            */
  if (_current < _nodes.size())
  {
    ++_current;
    if (_current == _nodes.size())
    {
      //this->OnFinishQueue();
      if (_parent) { _parent->OnFinishThread(); }//OnFinishSubNode(); }
      this->Clear();
      if (_holder) { _holder->NodeDidFinish(); }
    }
  }
}

void PLANodeThread::OnFinishThread()
{
  GRA_PRINT("%s| %s : OnFinishQueue(), _current: %2d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current);
}

/*
void PLANodeThread::OnFinishQueue()
{
  GRA_PRINT("%s| %s : OnFinishQueue(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current, _steps);
}

void PLANodeThread::OnFinishSubNode()
{
  GRA_PRINT("%s| %s : OnFinishSubNode(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current, _steps);
}
 */

bool PLANodeThread::IsFinished() const
{
  if (_current < _nodes.size()) { return false; }
  for (const PLANodeThread *thread: _threads)
  {
    if (!thread->IsFinished()) { return false; }
  }

  if (this->GetCurrentNode())
  { return this->GetCurrentNode()->IsFinished(); }

  return true;
}

const PLANode *PLANodeThread::GetCurrentNode() const
{
  GRA_PRINT("_nodes.size(): %d\n", _nodes.size());
  if (!_nodes.size()) { return nullptr; }
  if (_nodes.size() == _current) { return _nodes[_current - 1]; }//nullptr; }
  if (_nodes.size() < _current || _current < 0)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Current node value %d is invalid.", _current);
  }
  return _nodes[_current];
}

/*
const std::vector<PLANode *> &PLANode::GetBranch() const
{
  return _subNodes;
};
 */

void PLANodeThread::PrintNodes() const
{
  static int indentLevel = 0;
  std::string indentSpace = "";
  for (int i = 0; i < indentLevel; i++) {
    indentSpace.append("  ");
  }
  for (const PLANode *node: _nodes) {
    ++indentLevel;
    GRA_PRINT(" %2d : %s%6d / %6d | %7d | %32s |\n",
              indentLevel, indentSpace.c_str(),
              node->GetSteps(), node->GetLength(),
              _current, this->GetObjectName().c_str());
    --indentLevel;
  }
  for (const PLANodeThread *thread: _threads) {
    ++indentLevel;
    thread->PrintNodes();
    --indentLevel;
  }
}

