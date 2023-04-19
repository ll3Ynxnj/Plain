//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "PLAOBJTimelineNode.hpp"
#include "PLAOBJTimeline.hpp"
#include "Object/PLAOBJError.hpp"

PLAOBJTimeline *PLAOBJTimeline::Create(PLAOBJTimeline *aParent) {
  PLAOBJTimeline *thread = new PLAOBJTimeline(aParent);
  thread->Bind();
  return thread;
}

PLAOBJTimeline::PLAOBJTimeline(PLAOBJTimeline *aParent):
  PLAObject(PLAObjectType::Timeline),
  _parent(aParent)
{

}

PLAOBJTimeline::~PLAOBJTimeline() noexcept
{

}

void PLAOBJTimeline::Update() {
  DBG_PLANode_Update_Indent += "  ";

  //-- Update threads.
  for (auto thread: _threads) {
    thread.second->Update();
  }

  //-- Erase finished threads.
  for (auto key: _finishedThreadKeys) {
    _threads[key]->Unbind();
    _threads.erase(key);
  }
  _finishedThreadKeys.clear();

  //-- Update nodes.
  if (_current < _nodes.size()) { _nodes[_current]->Update(); }

  //-- Destruct
  if (this->IsFinished())//_current == _nodes.size())
  {
    if (_parent) { _parent->OnFinishThread(this); }
    this->Clear();
    if (_holder) { _holder->OnFinishThread(); }
  }
}

void PLAOBJTimeline::AddNode(PLAOBJTimelineNode *aNode)
{
  _nodes.push_back(aNode);
  aNode->SetThread(this);
}

void PLAOBJTimeline::AddThread(PLAOBJTimeline *aThread)
{
  aThread->_parent = this;
  _threads[aThread->GetObjectId()] = aThread;
}

void PLAOBJTimeline::Clear()
{
  for (auto thread: _threads) {
    thread.second->Clear();
  }
  _threads.clear();
  _finishedThreadKeys.clear();
  for (PLAOBJTimelineNode *node: _nodes) {
    node->Unbind();
  }
  _nodes.clear();
}

void PLAOBJTimeline::OnFinishNode()
{
  if (_current < _nodes.size()) { ++_current; }
}

void PLAOBJTimeline::OnFinishThread(const PLAOBJTimeline *aThread)
{
  _finishedThreadKeys.push_back(aThread->GetObjectId());
}

/*
void PLAOBJTimeline::OnUnbindThread(const PLAOBJTimeline *aThread)
{
  _threads.erase(aThread->GetOwnerId());
}
 */

bool PLAOBJTimeline::IsFinished() const
{
  if (_current < _nodes.size()) { return false; }
  for (const auto thread: _threads)
  { if (!thread.second->IsFinished()) { return false; } }

  if (this->GetCurrentNode())
  { return this->GetCurrentNode()->IsFinished(); }

  return true;
}

const PLAOBJTimelineNode *PLAOBJTimeline::GetCurrentNode() const
{
  if (!_nodes.size()) { return nullptr; }
  if (_nodes.size() == _current) { return _nodes[_current - 1]; }
  if (_nodes.size() < _current || _current < 0)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Current node value %d is invalid.", _current);
  }
  return _nodes[_current];
}

void PLAOBJTimeline::PrintNodes() const
{
  static int indentLevel = 0;
  std::string indentSpace = "";
  for (int i = 0; i < indentLevel; i++) {
    indentSpace.append("  ");
  }
  GRA_PRINT("%s::%s::_nodes.size(): %d\n", _parent ?
            _parent->GetObjectName().c_str() : "-- NULL --",
            this->GetObjectName().c_str(), _nodes.size());
  for (const PLAOBJTimelineNode *node: _nodes) {
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
