//
// Created by Kentaro Kawai on 2021/08/13.
//

#include "PLATimelineNode.hpp"
#include "Core/Class/PLAApp.hpp"
#include "Core/Class/PLAError.hpp"

// PLATimelineNode /////////////////////////////////////////////////////////////

PLATimelineNode *PLATimelineNode::Create(PLATimelineNode::Type aType)
{
  PLATimelineNode *node = nullptr;
  switch (aType) {
    case PLATimelineNode::Type::Motion: node = new PLAMotionNode(); break;
    case PLATimelineNode::Type::None: node = new PLATimelineNode(); break;
  }
  node->Bind();
  return node;
}

void PLATimelineNode::Bind()
{
  this->PLAObject::Bind();
}

void PLATimelineNode::Unbind()
{
  GRA_PRINT("PLATimelineNode::Unbind : %s\n", this->GetObjectName().c_str());
  GRABinder<PLATimelineNode>::Error error(GRABinder<PLATimelineNode>::Error::None);
  if (error != GRABinder<PLATimelineNode>::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLATimelineNode unbinding. ERROR : %02d", error);
  }
  this->PLAObject::Unbind();
}

PLATimelineNode::PLATimelineNode():
PLAObject(PLAObjectType::Node)
{

}

PLATimelineNode::PLATimelineNode(PLATimelineNode::Type aType):
PLAObject(PLAObjectType::Node),
_type(aType)
{

}

PLATimelineNode::PLATimelineNode(PLATimelineNode::Type aType, PLAInt aLength):
PLAObject(PLAObjectType::Node),
_type(aType),
_length(aLength)
{

}

PLATimelineNode::PLATimelineNode(PLATimelineNode::Type aType, PLAInt aLength, const std::string &aName):
PLAObject(PLAObjectType::Node, aName),
_type(aType),
_length(aLength)
{

}

PLATimelineNode::~PLATimelineNode()
{

}

void PLATimelineNode::Update()
{
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
    this->OnStop();
    if (_thread) {
      GRA_PRINT("Object '%s' will call function OnFinishCurrent().",
                this->GetObjectName().c_str());
      _thread->OnFinishNode();
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
}

void PLATimelineNode::OnStart()
{
  GRA_PRINT("%s| %s : OnStart(), _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _steps);
  _functor.RunFunction(FunctionCode::OnStart, this);
}

void PLATimelineNode::OnUpdate()
{
  GRA_PRINT("%s| %s : OnUpdate(), _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _steps);
  _functor.RunFunction(FunctionCode::OnUpdate, this);
}

void PLATimelineNode::OnStop()
{
  GRA_PRINT("%s| %s : OnStop(), _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _steps);
  _functor.RunFunction(FunctionCode::OnStop,  this);
}


bool PLATimelineNode::IsFinished() const
{
  return _length <= _steps;
}
