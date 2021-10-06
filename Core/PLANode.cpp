//
// Created by Kentaro Kawai on 2021/08/13.
//

#include "PLANode.hpp"

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
  for (PLANode *node: _branch) {
    node->Update();
  }
  if (_current < _main.size()) { _main[_current]->Update(); }
  if (_steps > _length) { DBG_PLANode_Update_Indent.erase(0, 2); return; }
  GRA_PRINT("%s| %s : Update(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(), _current, _steps);
  if (_steps == 0) { _functor.RunFunction(FunctionCode::OnStart, this); }
  _functor.RunFunction(FunctionCode::OnUpdate, this);
  if (_steps == _length)
  {
    _functor.RunFunction(FunctionCode::OnStop,  this);
    if (_parent) { _parent->OnFinishCurrent(); }
  }
  /*
   * OnPause
   * OnResume
   */
  ++_steps;
  //GRA_PRINT("%f <= %f\n", _length, _steps);
  //if (_length <= _steps) { _steps = _length; }

  // \~en Subtract one step from the magnitude to account for floating point errors and compare.
  // \~ja 浮動小数点誤差を考慮し、大きさから１ステップの半分を引いて比較する
  //GRA_PRINT("(%f - %f) < %f\n", _length, aStep * 0.5, _steps);
  //if ((_length - aStep * 0.5) < _steps) { _steps = _length; }
  DBG_PLANode_Update_Indent.erase(0, 2);
}

void PLANode::AddMain(PLANode *aNode)
{
  aNode->_parent = this;
  _main.push_back(aNode);
}

void PLANode::AddBranch(PLANode *aNode)
{
  aNode->_parent = this;
  _branch.push_back(aNode);
}

void PLANode::OnFinishCurrent()
{
  GRA_PRINT("%s| %s : OnFinishCurrent(), _current: %2d, _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _current, _steps);
  if (_current < _main.size())
  {
    ++_current;
    if (_current == _main.size())
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
  if (!_main.size()) { return nullptr; }
  return _main[_current];
}

const std::vector<PLANode *> &PLANode::GetBranch() const
{
  return _branch;
};
