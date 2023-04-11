#include "PLAObject.hpp"
#include "../Object/Agent/PLAOBJAgent.hpp"
#include "PLAOBJError.hpp"

// PLAObject ///////////////////////////////////////////////////////////////////
const std::map<PLAObject::Binder::Error, const char *> PLAObject::kBinderErrorMessages =
{
  { Binder::Error::OverwriteItem, "Overwrite item" },
  { Binder::Error::NameConflict, "Item name conflict" },
  { Binder::Error::NameOverride, "Item name has been over written" },
  { Binder::Error::NameConvertedBySystem, "Item name has been converted to system-generated" },
  { Binder::Error::RegisterExistingKeyToMap, "Register existing key to map" },
  { Binder::Error::NotExistInMap, "Not exist in map" },
  { Binder::Error::OutOfRange, "Out of range" },
};

const char *PLAObject::GetBinderErrorMessage(Binder::Error aError)
{
  return kBinderErrorMessages.at(aError);
}

PLAObject *PLAObject::Object(const PLAString &aName)
{
  Binder::Error error = Binder::Error::None;
  Binder::Item *item = PLAObject::Manager::Instance()->RefItem(aName, &error);
  switch (error) {
    case Binder::Error::None :
      break;
    default :
      return nullptr;
      //PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Failed to get object.",
      //                PLAObject::GetBinderErrorMessage(error));
  }
  return static_cast<PLAObject *>(item);
}

PLAObject *PLAObject::Object(PLAId aId)
{
  GRAOBJBinder<PLAObject>::Error error = GRAOBJBinder<PLAObject>::Error::None;
  GRAOBJBinder<PLAObject>::Item *item =
    PLAObject::Manager::Instance()->RefItem(aId, &error);
  switch (error) {
    case Binder::Error::None :
      break;
    default :
      PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Failed to get object.",
                      PLAObject::GetBinderErrorMessage(error));
  }
  return static_cast<PLAObject *>(item);
}

void PLAObject::Bind()
{
  GRA_PRINT("PLAObject::Bind : %s\n", this->GetObjectName().c_str());
  Binder::Error error(Binder::Error::None);
  PLAObject::Manager::Instance()->Bind(this, &error);
  if (error != Binder::Error::None) {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                    "Failed PLAObject binding. ERROR : %02d : %s",
                    error, GetBinderErrorMessage(error));
  }

  PLAObject::Manager::Instance()->PrintObjects();
}

void PLAObject::Unbind()
{
  GRA_PRINT("PLAObject::Unbind : %s\n", this->GetObjectName().c_str());
  if (0 < _agentReferenceCounter)
  {
    GRA_PRINT("PLAObject::Unbind : == CANCELED == : %s\n",
              this->GetObjectName().c_str());
    PLA_ERROR_ISSUE(PLAOBJErrorType::Expect, "Agent referenced form somewhere.");
    return;
  }
  Binder::Error error(Binder::Error::None);
  PLAObject::Manager::Instance()->Unbind(this, &error);
  if (error != Binder::Error::None) {
    PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                    "Failed PLAObject unbinding. ERROR : %02d : %s",
                    error, GetBinderErrorMessage(error));
  }

  PLAObject::Manager::Instance()->AddUnboundObject(this);

  PLAObject::Manager::Instance()->PrintObjects();
}

PLAObject::PLAObject(PLAObjectType aType) :
Binder::Item(kPLAStrUndefined, Manager::Instance()),
_type(aType)
{

}

PLAObject::PLAObject(PLAObjectType aType, const PLAString &aName) :
Binder::Item(aName, Manager::Instance()),
_type(aType)
{

}

PLAObject::~PLAObject()
{

}

void PLAObject::Print()
{
  GRA_PRINT("PLAObject : %8d, %d\n", this->GetId(), this);
}

PLAOBJAgent *PLAObject::AssignAgent()
{
  if (!_agent) {
    _agent = PLAOBJAgent::Create(this);
  }
  ++_agentReferenceCounter;
  return _agent;

  /*
  PLAOBJAgent *agent = PLAOBJAgent::Create(this);
  _agents.push_back(agent);
  return agent;
   */
}

void PLAObject::ReleaseAgent()/*const PLAOBJAgent *aAgent)*/
{
  --_agentReferenceCounter;
  if (_agentReferenceCounter == 0)
  {
    //PLAObject::Object(aAgent->GetObjectId())->Unbind();
    _agent->Unbind();
  }
  /*
  PLAObject::Object(aAgent->GetObjectId())->Unbind();
  std::erase(_agents, aAgent);
   */
}

const char *PLAObject::GetObjectTypeName() const
{
  return kPLAObjectTypeName[static_cast<PLAId>(_type)];
}

PLAString PLAObject::GetObjectDescription() const
{
  return grautil::format("PLAObject [ id : %04x, name : %s, type : %d, ]\n",
                         this->GetId(), this->GetName().c_str(), _type);
}

void PLAObject::SetObjectName(const PLAString &aName)
{
  Binder::Error error(Binder::Error::None);
  this->Binder::Item::SetName(aName, &error);
  if (error != Binder::Error::None)
  {
    switch (error) {
      case Binder::Error::NameOverride :
      case Binder::Error::NameConvertedBySystem:
        PLA_ERROR_ISSUE(PLAOBJErrorType::Expect,
                        "Succeed to set object name with error. ERROR : %02d : %s",
                        error, GetBinderErrorMessage(error));
        break;
      default :
        PLA_ERROR_ISSUE(PLAOBJErrorType::Assert,
                        "Failure to set object name. ERROR : %02d : %s",
                        error, GetBinderErrorMessage(error));
        break;
    }
  }
}

// GRAOBJBinder::Item /////////////////////////////////////////////////////////////

const char *PLAObject::GetBinderItemTypeName() const
{
  return PLAObject::GetObjectTypeName();
}

// PLAObject::Manager //////////////////////////////////////////////////////////

PLAObject::Manager PLAObject::Manager::_instance = PLAObject::Manager();

PLAObject::Manager::Manager():
Binder()
{

}

PLAObject::Manager::~Manager()
{

}

void PLAObject::Manager::AddUnboundObject(PLAObject *aObject)
{
  _unboundObjects.push_back(aObject);
}

void PLAObject::Manager::DeleteUnboundObjects()
{
  for (PLAObject *object: _unboundObjects) {
    GRA_DELETE(object);
  }
  _unboundObjects.clear();
}

void PLAObject::Manager::PrintObjects() const
{
  GRA_PRINT("//-- PLAObject::Manager::PrintResource --"
            "///////////////////////////////////////\n");
  GRA_PRINT("INDEX |   ID |                             NAME "
            "| TYPE |                                \n");
  GRA_PRINT("------|------|----------------------------------"
            "|------|------------------------\n");
  for (size_t i = 0; Binder::Item *item : this->GetItems())
  {
    if (item) {
      const PLAObject *object = static_cast<const PLAObject *>(item);
      PLAObjectType type = object->GetObjectType();
      GRA_PRINT(" %4d | %4d | %32s | %4d | %22s\n",
                i, object->GetId(), object->GetName().c_str(),
                type,
                kPLAObjectTypeName[static_cast<PLAId>(type)]);
    } else {
      GRA_PRINT(" %4d | %s | %s | %s | %22s\n",
                i, "----", "------------------------ NULL --", "----",
                "----------------------");
    }
    ++i;
  }
  GRA_PRINT("////////////////////////////////////////"
            "////////////////////////////////////////\n");
}