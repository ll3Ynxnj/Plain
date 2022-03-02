//
// Created by Kentaro Kawai on 2021/08/13.
//

#include "PLANode.hpp"
#include "PLAApp.hpp"
#include "PLAError.hpp"

// PLANode /////////////////////////////////////////////////////////////////////

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

/*
PLANode *PLANode::Create(PLANode::Type aType, PLANode::Holder *aHolder)
{
  PLANode *node = nullptr;
  node = Create(aType);
  node->_holder = aHolder;
  return node;
}
 */

void PLANode::Bind()
{
  this->PLAObject::Bind();

  GRABinder<PLANode>::Error error(GRABinder<PLANode>::Error::None);
  /*
  PLANode::Manager::Instance()->Bind(this, &error);
  if (error != GRABinder<PLANode>::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLANode binding. ERROR : %02d", error);
  }
   */
}

void PLANode::Unbind()
{
  GRA_PRINT("PLANode::Unbind : %s\n", this->GetObjectName().c_str());
  GRABinder<PLANode>::Error error(GRABinder<PLANode>::Error::None);
  //PLANode::Manager::Instance()->Unbind(this, &error);
  if (error != GRABinder<PLANode>::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLANode unbinding. ERROR : %02d", error);
  }

  //PLAApp::Instance()->RemoveNode(this);
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

void PLANode::OnStart()
{
  GRA_PRINT("%s| %s : OnStart(), _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _steps);
  _functor.RunFunction(FunctionCode::OnStart, this);
}

void PLANode::OnUpdate()
{
  GRA_PRINT("%s| %s : OnUpdate(), _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _steps);
  _functor.RunFunction(FunctionCode::OnUpdate, this);
}

void PLANode::OnStop()
{
  GRA_PRINT("%s| %s : OnStop(), _steps: %3d\n",
            DBG_PLANode_Update_Indent.c_str(), this->GetObjectName().c_str(),
            _steps);
  _functor.RunFunction(FunctionCode::OnStop,  this);
}


bool PLANode::IsFinished() const
{
  return _length <= _steps;
}

// PLANode::Manager ////////////////////////////////////////////////////////
/*
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
 */

