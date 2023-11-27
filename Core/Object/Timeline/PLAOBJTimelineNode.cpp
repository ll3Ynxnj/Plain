//
// Created by Kentaro Kawai on 2021/08/13.
//

#include "PLAOBJTimelineNode.hpp"
#include "Core/App/PLAApp.hpp"
#include "Object/PLAOBJError.hpp"
#include "Agent/PLAAGTTimelineNode.hpp"

// PLAOBJTimelineNode /////////////////////////////////////////////////////////////

PLAOBJTimelineNode *PLAOBJTimelineNode::Object(const PLAString &aName)
{
  auto object = PLAObject::Object(PLAObjectType::TimelineNode, aName);
  return static_cast<PLAOBJTimelineNode *>(object);
}

PLAOBJTimelineNode *PLAOBJTimelineNode::Object(PLAId aId)
{
  auto object = PLAObject::Object(PLAObjectType::TimelineNode, aId);
  return static_cast<PLAOBJTimelineNode *>(object);
}

PLAOBJTimelineNode *PLAOBJTimelineNode::Create(PLAOBJTimelineNode::Type aType)
{
  PLAOBJTimelineNode *node = nullptr;
  switch (aType) {
    case PLAOBJTimelineNode::Type::Motion: node = new PLATMLMotionNode(); break;
    case PLAOBJTimelineNode::Type::None: node = new PLAOBJTimelineNode(); break;
  }
  node->Bind();
  return node;
}

void PLAOBJTimelineNode::Bind()
{
  this->PLAObject::Bind();
}

void PLAOBJTimelineNode::Unbind()
{
  //GRA_PRINT("PLAOBJTimelineNode::Unbind : %s\n", this->GetObjectName().c_str());
  GRAOBJBinder<PLAOBJTimelineNode>::Error error(GRAOBJBinder<PLAOBJTimelineNode>::Error::None);
  if (error != GRAOBJBinder<PLAOBJTimelineNode>::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJTimelineNode unbinding. ERROR : %02d", error);
  }
  this->PLAObject::Unbind();
}

PLAOBJTimelineNode::PLAOBJTimelineNode():
PLAObject(PLAObjectType::TimelineNode)
{

}

PLAOBJTimelineNode::PLAOBJTimelineNode(PLAOBJTimelineNode::Type aType):
PLAObject(PLAObjectType::TimelineNode),
_type(aType)
{

}

PLAOBJTimelineNode::PLAOBJTimelineNode(PLAOBJTimelineNode::Type aType,
                                       PLAInt aLength):
PLAObject(PLAObjectType::TimelineNode),
_type(aType),
_length(aLength)
{

}

PLAOBJTimelineNode::PLAOBJTimelineNode(PLAOBJTimelineNode::Type aType,
                                       PLAInt aLength,
                                       const std::string &aName):
PLAObject(PLAObjectType::TimelineNode, aName),
_type(aType),
_length(aLength)
{

}

PLAOBJTimelineNode::~PLAOBJTimelineNode()
{

}

void PLAOBJTimelineNode::Update()
{
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
    this->OnStop();
    if (_timeline) {
      _timeline->OnFinishNode();
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

PLAAGTTimelineNode PLAOBJTimelineNode::AssignAgent()
{
  return PLAAGTTimelineNode(this);
}

void PLAOBJTimelineNode::OnStart()
{
  //GRA_PRINT("%s| %s : TimelineNode::OnStart(), _steps: %3d\n",
  //          "  ", //DBG_PLAOBJTimeline_Update_Indent.c_str(),
  //          this->GetObjectName().c_str(), _steps);
  _functor.RunFunction(PLAFunctionCode::TimelineNode::OnStart,
                       PLAAGTTimelineNode(this));
}

void PLAOBJTimelineNode::OnUpdate()
{
  //GRA_PRINT("%s| %s : TimelineNode::OnUpdate(), _steps: %3d\n",
  //          "  ", //DBG_PLAOBJTimeline_Update_Indent.c_str(),
  //          this->GetObjectName().c_str(), _steps);
  _functor.RunFunction(PLAFunctionCode::TimelineNode::OnUpdate,
                       PLAAGTTimelineNode(this));
}

void PLAOBJTimelineNode::OnStop()
{
  //GRA_PRINT("%s| %s : TimelineNode::OnStop(), _steps: %3d\n",
  //          "  ", //DBG_PLAOBJTimeline_Update_Indent.c_str(),
  //          this->GetObjectName().c_str(), _steps);
  _functor.RunFunction(PLAFunctionCode::TimelineNode::OnStop,
                       PLAAGTTimelineNode(this));
}


bool PLAOBJTimelineNode::IsFinished() const
{
  return _length <= _steps;
}
