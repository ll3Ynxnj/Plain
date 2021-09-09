//
// Created by Kentaro Kawai on 2021/08/13.
//

#include "PLANode.hpp"

PLANode *PLANode::Create(PLAInt aLength)
{
  PLANode *node = new PLANode(aLength);
  PLAObject::Bind(node);
  return node;
}

PLANode::PLANode(PLAInt aLength):
PLAObject(PLAObjectType::Node),
_length(aLength)
{

}

PLANode::~PLANode()
{

}

void PLANode::Update()
{
  if (_steps > _length) { return; }
  if (_steps == 0) { _functor.RunFunction(FunctionCode::OnStart, this); }
  _functor.RunFunction(FunctionCode::OnUpdate, this);
  if (_steps == _length) { _functor.RunFunction(FunctionCode::OnStop,  this); }
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
}

void PLANode::AddNode(PLANode *aNode)
{
  _node.push_back(aNode);
}
