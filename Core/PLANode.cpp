//
// Created by Kentaro Kawai on 2021/08/13.
//

#include "PLANode.hpp"
#include "PLAApp.hpp"
#include "PLAError.hpp"

static PLAString DBG_PLANode_Update_Indent = "";

void PLANode::Bind(PLANode *aNode)
{
  GRABinder<PLANode>::Error error(GRABinder<PLANode>::Error::None);
  PLANode::Manager::Instance()->Bind(aNode, &error);
  if (error != GRABinder<PLANode>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLANode binding. ERROR : %02d", error); }
}


PLANode::PLANode():
PLAObject(PLAObjectType::Node)
{

}

PLANode::PLANode(PLAInt aLength):
PLAObject(PLAObjectType::Node),
_length(aLength)
{

}

PLANode::PLANode(PLAInt aLength, const std::string &aName):
PLAObject(PLAObjectType::Node, aName),
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
  if (this->GetObjectName() == "ANHRStage::WalkPlayer::thread" ||
      this->GetObjectName() == "ANHRStage::WalkPlayer::tm0" ||
      this->GetObjectName() == "ANHRStage::WalkPlayer::tm1") {
    GRA_PRINT("this->GetObjectName(): %s", this->GetObjectName().c_str());
    GRA_TRACE("");
  }
  if (_current < _thread.size()) { _thread[_current]->Update(); }

  if (_steps >= _length) { DBG_PLANode_Update_Indent.erase(0, 2); return; }
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
    if (this->GetObjectName() == "ANHRStage::WalkPlayer::thread" ||
        this->GetObjectName() == "ANHRStage::WalkPlayer::tm0" ||
        this->GetObjectName() == "ANHRStage::WalkPlayer::tm1")
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
  aNode->_parent = this;
  _thread.push_back(aNode);
}

void PLANode::AddThread(PLANode *aNode)
{
  aNode->_parent = this;
  _subThreads.push_back(aNode);
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
      if (_parent) { _parent->OnFinishBranch(); };
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

PLANode::Holder::Holder(PLANode *aNode):
_node(aNode)
{
  PLAApp::AddNode(aNode);
}

void PLANode::Holder::AddNode(PLANode *aNode)
{
  _node->Add(aNode);
}

void PLANode::Holder::AddNodes(const std::vector<PLANode *> &aNodes)
{
  for (PLANode *node: aNodes) {
    _node->Add(node);
  }
}

void PLANode::Holder::AddThread(PLANode *aNode)
{
  _node->AddThread(aNode);
}

const PLANode *PLANode::Holder::GetNode() const
{
  return _node;
}
