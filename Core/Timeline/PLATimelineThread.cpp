//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "PLATimelineNode.hpp"
#include "PLATimelineThread.hpp"
#include "Core/Class/PLAError.hpp"

PLATimelineThread *PLATimelineThread::Create(PLATimelineThread *aParent) {
  PLATimelineThread *thread = new PLATimelineThread(aParent);
  thread->Bind();
  return thread;
}

PLATimelineThread::PLATimelineThread(PLATimelineThread *aParent):
  PLAObject(PLAObjectType::NodeThread),
  _parent(aParent)
{

}

PLATimelineThread::~PLATimelineThread() noexcept
{

}

void PLATimelineThread::Update() {
  DBG_PLANode_Update_Indent += "  ";

  //-- Update threads.
  for (auto thread: _threads) {
    thread.second->Update();
  }

  //-- Erase finished threads.
  for (auto key: _finishedThreadKeys) {
    if (_threads[key]->GetObjectName() == "ANHRStage::WalkPlayer::t0") {
      GRA_TRACE("");
    }
    PLAObject::Destroy(_threads[key]);
    _threads.erase(key);
  }
  _finishedThreadKeys.clear();

  //-- Update nodes.
  if (_current < _nodes.size()) { _nodes[_current]->Update(); }
}

void PLATimelineThread::AddNode(PLATimelineNode *aNode)
{
  _nodes.push_back(aNode);
  aNode->SetThread(this);
}

void PLATimelineThread::AddThread(PLATimelineThread *aThread)
{
  aThread->_parent = this;
  _threads[aThread->GetObjectId()] = aThread;
}

void PLATimelineThread::Clear()
{
  GRA_PRINT("%s::Clear()\n", this->GetObjectName().c_str());
  for (auto thread: _threads) {
    thread.second->Clear();
  }
  _threads.clear();
  _finishedThreadKeys.clear();
  for (PLATimelineNode *node: _nodes) {
    PLAObject::Destroy(node);
  }
  _nodes.clear();
  GRA_PRINT("  _queue.size(): %s", _nodes.size());
  //PLAObject::Destroy(this);
}

void PLATimelineThread::OnFinishNode()
{
  if (_current < _nodes.size())
  {
    ++_current;
  }

  if (_current == _nodes.size())
  {
    if (_parent) { _parent->OnFinishThread(this); }
    this->Clear();
    if (_holder) { _holder->OnFinishThread(); }
  }
}

void PLATimelineThread::OnFinishThread(const PLATimelineThread *aThread)
{
  GRA_PRINT("%s| %s : OnFinishQueue(), _current: %2d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current);
  _finishedThreadKeys.push_back(aThread->GetObjectId());
  //this->AdvanceNode();
  if (aThread->GetObjectName() == "ANHRStage::WalkPlayer::t0") {
    GRA_TRACE("");
  }
}

/*
void PLATimelineThread::OnUnbindThread(const PLATimelineThread *aThread)
{
  _threads.erase(aThread->GetObjectId());
}
 */

bool PLATimelineThread::IsFinished() const
{
  if (_current < _nodes.size()) { return false; }
  for (const auto thread: _threads)
  {
    if (!thread.second->IsFinished()) { return false; }
  }

  if (this->GetCurrentNode())
  { return this->GetCurrentNode()->IsFinished(); }

  return true;
}

const PLATimelineNode *PLATimelineThread::GetCurrentNode() const
{
  GRA_PRINT("%s::_nodes.size(): %d\n", this->GetObjectName().c_str(), _nodes.size());
  if (!_nodes.size()) { return nullptr; }
  if (_nodes.size() == _current) { return _nodes[_current - 1]; }
  if (_nodes.size() < _current || _current < 0)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Current node value %d is invalid.", _current);
  }
  return _nodes[_current];
}

void PLATimelineThread::PrintNodes() const
{
  static int indentLevel = 0;
  std::string indentSpace = "";
  for (int i = 0; i < indentLevel; i++) {
    indentSpace.append("  ");
  }
  GRA_PRINT("%s::%s::_nodes.size(): %d\n", _parent ?
            _parent->GetObjectName().c_str() : "-- NULL --",
            this->GetObjectName().c_str(), _nodes.size());
  for (const PLATimelineNode *node: _nodes) {
    ++indentLevel;
    GRA_PRINT(" %2d : %s%6d / %6d | %7d | %32s |\n",
              indentLevel, indentSpace.c_str(),
              node->GetSteps(), node->GetLength(),
              _current, this->GetObjectName().c_str());
    --indentLevel;
  }
  for (const auto thread: _threads) {
    ++indentLevel;
    thread.second->PrintNodes();
    --indentLevel;
  }
}
