//
// Created by Kentaro Kawai on 2021/08/13.
//

#include "PLANode.hpp"
#include "PLAError.hpp"

static PLAString DBG_PLANode_Update_Indent = "";

PLANode *PLANode::Create(PLAInt aLength)
{
  PLANode *node = new PLANode(aLength);
  PLAObject::Bind(node);
  return node;
}

PLANode *PLANode::Create(PLAInt aLength, const PLAString &aName)
{
  PLANode *node = new PLANode(aLength, aName);
  PLAObject::Bind(node);
  return node;
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
  if (this->GetObjectName() == "ANHRStage::WalkPlayer::m0" ||
      this->GetObjectName() == "ANHRStage::WalkPlayer::m1" ||
      this->GetObjectName() == "ANHRStage::WalkPlayer::m2") {
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
  if (_steps == _length)
  {
    if (this->GetObjectName() == "ANHRStage::WalkPlayer::m0" ||
        this->GetObjectName() == "ANHRStage::WalkPlayer::m1" ||
        this->GetObjectName() == "ANHRStage::WalkPlayer::m2")
    {
      GRA_PRINT("this->GetObjectName(): %s", this->GetObjectName().c_str());
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
