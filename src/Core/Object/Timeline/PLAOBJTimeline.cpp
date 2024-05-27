//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "Core/Object/Timeline/PLAOBJTimelineNode.hpp"
#include "Core/Object/Timeline/PLAOBJTimeline.hpp"
#include "Core/Object/PLAOBJError.hpp"
#include "Core/Agent/PLAAGTTimeline.hpp"

PLAOBJTimeline *PLAOBJTimeline::Object(const PLAString &aName)
{
  if (aName == "") {
    GRA_TRACE("PLAOBJTimeline::Object() : aName is empty.");
  }
  auto object = PLAObject::Object(PLAObjectType::Timeline, aName);
  return static_cast<PLAOBJTimeline *>(object);
}

PLAOBJTimeline *PLAOBJTimeline::Object(PLAId aId)
{
  auto object = PLAObject::Object(PLAObjectType::Timeline, aId);
  return static_cast<PLAOBJTimeline *>(object);
}

PLAOBJTimeline *PLAOBJTimeline::Create(PLAOBJTimeline *aParent) {
  PLAOBJTimeline *thread = new PLAOBJTimeline(PLAObjectType::Timeline, aParent);
  thread->Bind();
  return thread;
}

PLAOBJTimeline *PLAOBJTimeline::Create(PLAOBJTimeline *aParent,
                                       const PLAString &aName) {
  if (aName == "") {
    GRA_TRACE("PLAOBJTimeline::Object() : aName is empty.");
  }
  PLAOBJTimeline *thread = new PLAOBJTimeline(PLAObjectType::Timeline, aParent,
                                              aName);
  thread->Bind();
  return thread;
}

PLAOBJTimeline::PLAOBJTimeline(PLAObjectType aType):
  PLAObject(aType),
  _parent(nullptr)
{

}

PLAOBJTimeline::PLAOBJTimeline(PLAObjectType aType, const PLAString &aName):
  PLAObject(aType, aName),
  _parent(nullptr)
{

}

PLAOBJTimeline::PLAOBJTimeline(PLAObjectType aType, PLAOBJTimeline *aParent):
  PLAObject(aType),
  _parent(aParent)
{

}

PLAOBJTimeline::PLAOBJTimeline(PLAObjectType aType, PLAOBJTimeline *aParent,
                               const PLAString &aName):
  PLAObject(aType, aName),
  _parent(aParent)
{

}

PLAOBJTimeline::~PLAOBJTimeline() noexcept
{
  _functor.RunFunction(PLAFunctionCode::Timeline::OnDestroy,
                       PLAAGTTimeline(this));
}

void PLAOBJTimeline::Update() {
  //DBG_PLAOBJTimeline_Update_Indent += "  ";

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
  if (_current < _nodes.size()) {
    //-- OnStart
    if (_steps == 0) { this->OnStart(); }

    //-- OnUpdate
    ++_steps;
    this->OnUpdate();

    _nodes[_current]->Update();
  }

  //-- Destruct
  if (this->IsFinished())//_current == _nodes.size())
  {
    //-- OnUpdate
    this->OnStop();

    if (_parent) { _parent->OnFinishThread(this); }
    this->Clear();
    if (_holder) { _holder->OnFinishTimeline(); }
  }

  //DBG_PLAOBJTimeline_Update_Indent.resize(
  //  DBG_PLAOBJTimeline_Update_Indent.size() - 2);
}

void PLAOBJTimeline::AddNode(PLAOBJTimelineNode *aNode)
{
  _nodes.push_back(aNode);
  aNode->SetThread(this);
}

void PLAOBJTimeline::AddThread(PLAOBJTimeline *aThread)
{
  if (aThread->_parent) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "The thread is already added to another thread.");
  }
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

PLAAGTTimeline PLAOBJTimeline::AssignAgent()
{
  return PLAAGTTimeline(this);
}

void PLAOBJTimeline::OnFinishNode()
{
  if (_current < _nodes.size()) {
    ++_current;
  }
}

void PLAOBJTimeline::OnFinishThread(const PLAOBJTimeline *aThread)
{
  _finishedThreadKeys.push_back(aThread->GetObjectId());
}

/*
void PLAOBJTimeline::OnUnbindThread(const PLAOBJTimeline *aThread)
{
  _threads.erase(aThread->GetObjectId());
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

void PLAOBJTimeline::OnStart()
{
  //GRA_PRINT("%s| %s : Timeline::OnStart(), _steps: %3d\n",
  //          "  ", //DBG_PLAOBJTimeline_Update_Indent.c_str(),
  //          this->GetObjectName().c_str(), _steps);
  _functor.RunFunction(PLAFunctionCode::Timeline::OnStart,
                       PLAAGTTimeline(this));
}

void PLAOBJTimeline::OnUpdate()
{
  //GRA_PRINT("%s| %s : Timeline::OnUpdate(), _steps: %3d\n",
  //          "  ", //DBG_PLAOBJTimeline_Update_Indent.c_str(),
  //          this->GetObjectName().c_str(), _steps);
  _functor.RunFunction(PLAFunctionCode::Timeline::OnUpdate,
                       PLAAGTTimeline(this));
}

void PLAOBJTimeline::OnStop()
{
  //GRA_PRINT("%s : Timeline::OnStop(), _steps: %3d\n",
  //          "  ", //DBG_PLAOBJTimeline_Update_Indent.c_str(),
  //          this->GetObjectName().c_str(), _steps);
  _functor.RunFunction(PLAFunctionCode::Timeline::OnStop,
                       PLAAGTTimeline(this));
}
