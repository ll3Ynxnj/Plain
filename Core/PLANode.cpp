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
  GRA_PRINT("Unbind\n");
  GRABinder<PLANode>::Error error(GRABinder<PLANode>::Error::None);
  PLANode::Manager::Instance()->Unbind(this, &error);
  if (error != GRABinder<PLANode>::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLANode unbinding. ERROR : %02d", error);
  }

  PLAApp::RemoveNode(this);
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
  DBG_PLANode_Update_Indent += "  ";

  //-- Update nodes.
  for (PLANode *node: _subThreads) {
    node->Update();
  }
  if (this->GetObjectName() == "ANHRStage::WalkPlayer::motion"/* ||
      this->GetObjectName() == "ANHRStage::WalkPlayer::thread" ||
      this->GetObjectName() == "ANHRStage::WalkPlayer::tm0" ||
      this->GetObjectName() == "ANHRStage::WalkPlayer::tm1"*/) {
    GRA_PRINT("this->GetObjectName(): %s", this->GetObjectName().c_str());
    GRA_TRACE("");
  }
  if (_current < _thread.size()) { _thread[_current]->Update(); }

  if (_steps >= _length)
  {
    DBG_PLANode_Update_Indent.erase(0, 2);
    return;
  }
  GRA_PRINT("%s| %s : Update(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(), _current, _steps);

  //-- OnStart
  if (_steps == 0) { this->OnStart(); }

  //-- OnUpdate
  if (_steps < _length)
  {
    ++_steps;
    this->OnUpdate();
  }

  //-- OnStop
  if (this->IsFinished())
  {
    if (this->GetObjectName() == "ANHRStage::WalkPlayer::motion")
    {
      GRA_PRINT("this->GetObjectName(): %s", this->GetObjectName().c_str());
      GRA_TRACE("");
    }
    this->OnStop();
    if (_parent) {
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

void PLANode::Add(PLANode *aNode)
{
  if (aNode == this) {
    GRA_TRACE("");
  }
  aNode->_parent = this;
  _thread.push_back(aNode);
}

void PLANode::AddThread(PLANode *aNode)
{
  aNode->_parent = this;
  _subThreads.push_back(aNode);
}

void PLANode::Clear()
{
  GRA_PRINT("%s::Clear()\n", this->GetObjectName().c_str());
  for (PLANode *node: _subThreads) {
    node->Clear();
  }
  _subThreads.clear();
  for (PLANode *node: _thread) {
    PLAObject::Destroy(node);
  }
  _thread.clear();
  GRA_PRINT("  _thread.size(): %s", _thread.size());
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
  if (_current < _thread.size())
  {
    ++_current;
    if (_current == _thread.size())
    {
      this->OnFinishMain();
      if (_parent) { _parent->OnFinishBranch(); }
      this->Clear();
      if (_holder) { _holder->NodeDidFinish(); }
    }
  }
}

void PLANode::OnFinishMain()
{
  GRA_PRINT("%s| %s : OnFinishMain(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current, _steps);
}

void PLANode::OnFinishBranch()
{
  GRA_PRINT("%s| %s : OnFinishBranch(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current, _steps);
}

void PLANode::PrintNode() const
{
  GRA_PRINT("PrintNode");//%12d | %65s\n", this->GetSize(), _path.c_str());
}

bool PLANode::IsFinished() const
{
  if (_steps < _length) { return false; }
  for (const PLANode *thread: _subThreads)
  {
    if (thread->IsFinished()) { return false; }
  }
  return true;
}

const PLANode *PLANode::GetCurrentNode() const
{
  GRA_PRINT("_thread.size(): %d\n", _thread.size());
  if (!_thread.size()) { return nullptr; }
  if (_thread.size() == _current) { return _thread[_current - 1]; }//nullptr; }
  if (_thread.size() < _current || _current < 0)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Current node value %d is invalid.", _current);
  }
  return _thread[_current];
}

const std::vector<PLANode *> &PLANode::GetBranch() const
{
  return _subThreads;
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
  { static_cast<const PLANode *>(item)->PrintNode(); }
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
  PLAApp::AddNode(aNode);
}

void PLANode::Holder::AddNode(PLANode *aNode)
{
  if (!_node) {
    _node = PLANode::Create(aNode->GetNodeType(), this);
    PLAApp::AddNode(_node);
  }

  _node->Add(aNode);
}

void PLANode::Holder::AddNodes(const std::vector<PLANode *> &aNodes)
{
  for (PLANode *node: aNodes) {
    this->AddNode(node);
  }
}

void PLANode::Holder::AddNodeThread(PLANode *aNode)
{
  _node->AddThread(aNode);
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
