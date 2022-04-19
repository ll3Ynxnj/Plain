//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "PLATimelineNode.hpp"
#include "PLATimeline.hpp"
#include "Core/Class/PLAError.hpp"

PLATimeline *PLATimeline::Create(PLATimeline *aParent) {
  PLATimeline *thread = new PLATimeline(aParent);
  thread->Bind();
  return thread;
}

PLATimeline::PLATimeline(PLATimeline *aParent):
  PLAObject(PLAObjectType::Timeline),
  _parent(aParent)
{

}

PLATimeline::~PLATimeline() noexcept
{

}

void PLATimeline::Update() {
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

void PLATimeline::AddNode(PLATimelineNode *aNode)
{
  _nodes.push_back(aNode);
  aNode->SetThread(this);
}

void PLATimeline::AddThread(PLATimeline *aThread)
{
  aThread->_parent = this;
  _threads[aThread->GetObjectId()] = aThread;
}

void PLATimeline::Clear()
{
  for (auto thread: _threads) {
    thread.second->Clear();
  }
  _threads.clear();
  _finishedThreadKeys.clear();
  for (PLATimelineNode *node: _nodes) {
    node->Unbind();
  }
  _nodes.clear();
}

void PLATimeline::OnFinishNode()
{
  if (_current < _nodes.size()) { ++_current; }
}

void PLATimeline::OnFinishThread(const PLATimeline *aThread)
{
  _finishedThreadKeys.push_back(aThread->GetObjectId());
}

/*
void PLATimeline::OnUnbindThread(const PLATimeline *aThread)
{
  _threads.erase(aThread->GetOwnerId());
}
 */

bool PLATimeline::IsFinished() const
{
  if (_current < _nodes.size()) { return false; }
  for (const auto thread: _threads)
  { if (!thread.second->IsFinished()) { return false; } }

  if (this->GetCurrentNode())
  { return this->GetCurrentNode()->IsFinished(); }

  return true;
}

const PLATimelineNode *PLATimeline::GetCurrentNode() const
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

void PLATimeline::PrintNodes() const
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
