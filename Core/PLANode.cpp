//
// Created by Kentaro Kawai on 2021/08/13.
//

#include "PLANode.hpp"
#include "PLAApp.hpp"
#include "PLAError.hpp"

static PLAString DBG_PLANode_Update_Indent = "";

PLANode *PLANode::Create(PLANode::Type aType)
{
  PLANode *node = nullptr;
  switch (aType) {
    case PLANode::Type::Motion: node = new PLAMotion(); break;
    case PLANode::Type::None: node = new PLANode(); break;
  }
  node->Bind();
  return node;
}

PLANode *PLANode::Create(PLANode::Type aType, PLANode::Holder *aHolder)
{
  PLANode *node = nullptr;
  node = Create(aType);
  node->_holder = aHolder;
  return node;
}

void PLANode::Bind()
{
  this->PLAObject::Bind();

  GRABinder<PLANode>::Error error(GRABinder<PLANode>::Error::None);
  PLANode::Manager::Instance()->Bind(this, &error);
  if (error != GRABinder<PLANode>::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLANode binding. ERROR : %02d", error);
  }
}

void PLANode::Unbind()
{
  GRA_PRINT("PLANode::Unbind : %s\n", this->GetObjectName().c_str());
  GRABinder<PLANode>::Error error(GRABinder<PLANode>::Error::None);
  PLANode::Manager::Instance()->Unbind(this, &error);
  if (error != GRABinder<PLANode>::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLANode unbinding. ERROR : %02d", error);
  }

  PLAApp::Instance()->RemoveNode(this);
  this->PLAObject::Unbind();
}

PLANode::PLANode():
PLAObject(PLAObjectType::Node)
{

}

PLANode::PLANode(PLANode::Type aType):
PLAObject(PLAObjectType::Node),
_type(aType)
{

}

PLANode::PLANode(PLANode::Type aType, PLAInt aLength):
PLAObject(PLAObjectType::Node),
_type(aType),
_length(aLength)
{

}

PLANode::PLANode(PLANode::Type aType, PLAInt aLength, const std::string &aName):
PLAObject(PLAObjectType::Node, aName),
_type(aType),
_length(aLength)
{

}

PLANode::~PLANode()
{

}

void PLANode::Update()
{
  if (this->GetObjectName() == "ANHRStage::WalkPlayer::t0")
  {
    GRA_PRINT("this->GetObjectName(): %s", this->GetObjectName().c_str());
    GRA_TRACE("");
  }

  DBG_PLANode_Update_Indent += "  ";

  //-- Update nodes.
  for (PLANode *node: _subNodes) {
    node->Update();
  }
  if (this->GetObjectName() == "ANHRStage::WalkPlayer::motion"/* ||
      this->GetObjectName() == "ANHRStage::WalkPlayer::thread" ||
      this->GetObjectName() == "ANHRStage::WalkPlayer::tm0" ||
      this->GetObjectName() == "ANHRStage::WalkPlayer::tm1"*/) {
    //GRA_PRINT("this->GetObjectName(): %s", this->GetObjectName().c_str());
    //GRA_TRACE("");
  }
  if (_current < _queue.size()) { _queue[_current]->Update(); }

  //-- Infinity
  /*
  if (_length == 0) {
    GRA_PRINT("Infinity : %s : _current: %2d, _steps: %3d, _length: %3d\n",
              this->GetObjectName().c_str(), _current, _steps, _length);
    DBG_PLANode_Update_Indent.erase(0, 2);
    this->OnUpdate();
    return;
  }
   */

  /*
  if (_steps >= _length)
  {
    GRA_PRINT("%s| %s : Update(), _current: %2d, _steps: %3d, _length: %3d\n",
              DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(), _current, _steps, _length);
    DBG_PLANode_Update_Indent.erase(0, 2);
    return;
  }
   */
  GRA_PRINT("%s| %s : Update(), _current: %2d, _steps: %3d, _length: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(), _current, _steps, _length);

  //-- OnStart
  if (_steps == 0) { this->OnStart(); }

  //-- OnUpdate
  if (_steps < _length)
  {
    if (!_infinity) { ++_steps; };
    this->OnUpdate();
  }

  //-- OnStop
  if (this->IsFinished())
  {
    if (this->GetObjectName() == "ANHRStage::WalkPlayer::t0")
    {
      GRA_PRINT("this->GetObjectName(): %s", this->GetObjectName().c_str());
      GRA_TRACE("");
    }
    this->OnStop();
    if (_parent) {
      GRA_PRINT("Object '%s' will call function OnFinishCurrent().",
                this->GetObjectName().c_str());
      _parent->OnFinishCurrent();
    }
  }

  /*
   * OnPause
   * OnResume
   */
  //GRA_PRINT("%f <= %f\n", _length, _steps);
  //if (_length <= _steps) { _steps = _length; }

  // \~en Subtract one step from the magnitude to account for floating point errors and compare.
  // \~ja 浮動小数点誤差を考慮し、大きさから１ステップの半分を引いて比較する
  //GRA_PRINT("(%f - %f) < %f\n", _length, aStep * 0.5, _steps);
  //if ((_length - aStep * 0.5) < _steps) { _steps = _length; }

  DBG_PLANode_Update_Indent.erase(0, 2);
}

void PLANode::AddQueue(PLANode *aNode)
{
  if (aNode == this) {
    GRA_TRACE("");
  }
  aNode->_parent = this;
  _queue.push_back(aNode);
}

void PLANode::AddSubNode(PLANode *aNode)
{
  aNode->_parent = this;
  _subNodes.push_back(aNode);
}

void PLANode::Clear()
{
  GRA_PRINT("%s::Clear()\n", this->GetObjectName().c_str());
  for (PLANode *node: _subNodes) {
    node->Clear();
  }
  _subNodes.clear();
  for (PLANode *node: _queue) {
    PLAObject::Destroy(node);
  }
  _queue.clear();
  GRA_PRINT("  _queue.size(): %s", _queue.size());
  //PLAObject::Destroy(this);
}

void PLANode::OnStart()
{
  GRA_PRINT("%s| %s : OnStart(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current, _steps);
  _functor.RunFunction(FunctionCode::OnStart, this);
}

void PLANode::OnUpdate()
{
  GRA_PRINT("%s| %s : OnUpdate(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current, _steps);
  _functor.RunFunction(FunctionCode::OnUpdate, this);
}

void PLANode::OnStop()
{
  GRA_PRINT("%s| %s : OnStop(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current, _steps);
  _functor.RunFunction(FunctionCode::OnStop,  this);
}

void PLANode::OnFinishCurrent()
{
  GRA_PRINT("%s| %s : OnFinishCurrent(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current, _steps);
  if (_current < _queue.size())
  {
    ++_current;
    if (_current == _queue.size())
    {
      this->OnFinishQueue();
      if (_parent) { _parent->OnFinishSubNode(); }
      this->Clear();
      if (_holder) { _holder->NodeDidFinish(); }
    }
  }
}

void PLANode::OnFinishQueue()
{
  GRA_PRINT("%s| %s : OnFinishQueue(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current, _steps);
}

void PLANode::OnFinishSubNode()
{
  GRA_PRINT("%s| %s : OnFinishSubNode(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current, _steps);
}

void PLANode::PrintNodes() const
{
  static int indentLevel = 0;
  std::string indentSpace = "";
  for (int i = 0; i < indentLevel; i++) {
    indentSpace.append("  ");
  }
  GRA_PRINT(" %2d : %s%6d / %6d | %7d | %32s |\n", indentLevel, indentSpace.c_str(),
            _steps, _length, _current, this->GetObjectName().c_str());
  for (const PLANode *node: _queue) {
    ++indentLevel;
    node->PrintNodes();
    --indentLevel;
  }
  for (const PLANode *subNode: _subNodes) {
    ++indentLevel;
    subNode->PrintNodes();
    --indentLevel;
  }
}

bool PLANode::IsFinished() const
{
  if (_steps < _length) { return false; }
  if (_current < _queue.size()) { return false; }
  for (const PLANode *subNode: _subNodes)
  {
    if (!subNode->IsFinished()) { return false; }
  }

  if (this->GetCurrentNode())
  { return this->GetCurrentNode()->IsFinished(); }

  return true;
}

const PLANode *PLANode::GetCurrentNode() const
{
  GRA_PRINT("_queue.size(): %d\n", _queue.size());
  if (!_queue.size()) { return nullptr; }
  if (_queue.size() == _current) { return _queue[_current - 1]; }//nullptr; }
  if (_queue.size() < _current || _current < 0)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Current node value %d is invalid.", _current);
  }
  return _queue[_current];
}

const std::vector<PLANode *> &PLANode::GetBranch() const
{
  return _subNodes;
};

// PLANode::Manager ////////////////////////////////////////////////////////

PLANode::Manager PLANode::Manager::_instance = PLANode::Manager();

PLANode::Manager::Manager() :
GRABinder<PLANode>()
{

}

PLANode::Manager::~Manager()
{

}

PLANode *PLANode::Manager::Node(const std::string &aKey)
{
  GRABinder<PLANode>::Error error(GRABinder<PLANode>::Error::None);
  return static_cast<PLANode *>(_instance.RefItem(aKey, &error));
}

void PLANode::Manager::PrintNodes() const
{
  GRA_PRINT("//-- PLANode::Manager::PrintNode"
            "s --////////////////////////////////////\n");
  GRA_PRINT("        SIZE |                          "
            "                                    PATH\n");
  GRA_PRINT("-------------|--------------------------"
            "----------------------------------------\n");
  for (PLANode::Item *item : this->GetItems())
  { static_cast<const PLANode *>(item)->PrintNodes(); }
  GRA_PRINT("////////////////////////////////////////"
            "////////////////////////////////////////\n");
};

const PLANode *PLANode::Manager::GetNode(const std::string &aName) const
{
  PLANode::Error error = PLANode::Error::None;
  const PLANode *resource =
    static_cast<const PLANode *>(this->GetItem(aName, &error));
  if (error != PLANode::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to get resource. ERROR : %02d", error);
  }
  return resource;
};

// PLANode::Holder /////////////////////////////////////////////////////////////

PLANode::Holder::Holder()
{

}

PLANode::Holder::Holder(PLANode *aNode):
_node(aNode)
{
  PLAApp::Instance()->AddNode(aNode);
}

void PLANode::Holder::AddQueue(PLANode *aNode)
{
  if (!_node) {
    _node = PLANode::Create(aNode->GetNodeType(), this);
    PLAApp::Instance()->AddNode(_node);
  }
  _node->AddQueue(aNode);
}

void PLANode::Holder::AddQueues(const std::vector<PLANode *> &aQueues)
{
  for (PLANode *node: aQueues) {
    this->AddQueue(node);
  }
}

void PLANode::Holder::AddSubNode(PLANode *aSubNode)
{
  if (!_node) {
    _node = PLANode::Create(aSubNode->GetNodeType(), this);
    PLAApp::Instance()->AddNode(_node);
  }
  _node->AddSubNode(aSubNode);
}

const PLANode *PLANode::Holder::GetNode() const
{
  return _node;
}

void PLANode::Holder::NodeDidFinish()
{
  PLAObject::Destroy(_node);
  _node = nullptr;
}
