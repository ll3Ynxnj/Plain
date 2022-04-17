#include "PLAObject.hpp"
#include "PLAError.hpp"

// PLAObject ///////////////////////////////////////////////////////////////////
const std::map<PLAObject::Binder::Error, const char *> PLAObject::kBinderErrorMessages =
{
  { Binder::Error::OverwriteItem, "Overwrite item" },
  { Binder::Error::NameConflict, "Item name conflict" },
  { Binder::Error::NameOverride, "Item name has been over written" },
  { Binder::Error::NameConversion, "Item name has been converted to system-generated" },
  { Binder::Error::RegisterExistingKeyToMap, "Register existing key to map" },
  { Binder::Error::NotExistInMap, "Not exist in map" },
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
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "Failed to get object.",
                      PLAObject::GetBinderErrorMessage(error));
  }
  return static_cast<PLAObject *>(item);
}

PLAObject *PLAObject::Object(PLAId aId)
{
  GRABinder<PLAObject>::Error error = GRABinder<PLAObject>::Error::None;
  GRABinder<PLAObject>::Item *item =
    PLAObject::Manager::Instance()->RefItem(aId, &error);
  switch (error) {
    case Binder::Error::None :
      break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "Failed to get object.",
                      PLAObject::GetBinderErrorMessage(error));
  }
  return static_cast<PLAObject *>(item);
}

const char *PLAObject::GetObjectTypeName() const
{
  return kPLAObjectTypeName[static_cast<PLAId>(_type)];
}

void PLAObject::Bind()
{
  Binder::Error error(Binder::Error::None);
  PLAObject::Manager::Instance()->Bind(this, &error);
  if (error != Binder::Error::None) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAObject binding. ERROR : %02d : %s",
                    error, GetBinderErrorMessage(error));
  }
}

void PLAObject::Unbind()
{
  GRA_PRINT("PLAObject::Unbind : %s\n", this->GetObjectName().c_str());
  Binder::Error error(Binder::Error::None);
  PLAObject::Manager::Instance()->Unbind(this, &error);
  if (error != Binder::Error::None) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAObject unbinding. ERROR : %02d : %s",
                    error, GetBinderErrorMessage(error));
  }

  PLAObject::Manager::Instance()->AddUnboundObject(this);
}

void PLAObject::Print()
{
  GRA_PRINT("PLAObject : %8d, %d\n", this->GetId(), this);
}

/*
PLAObject *PLAObject::Manager::Object(const PLAString &aKey)
{
  Binder::Error error(Binder::Error::None);
  return static_cast<PLAObject *>(_instance.RefItem(aKey, &error));
}

PLAObject *PLAObject::Manager::Object(PLASize aId)
{
  Binder::Error error(Binder::Error::None);
  return static_cast<PLAObject *>(_instance.RefItem(aId, &error));
}
 */

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

PLAString PLAObject::GetObjectDescription() const
{
  return grautil::format("PLAObject [ id : %04x, name : %s, type : %d, ]\n",
                         this->GetId(), this->GetName().c_str(), _type);
}

PLABool PLAObject::GetBool(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Property %s does not exist.", aName.c_str()); }
  return _properties.at(aName).GetBool();
}

PLAInt PLAObject::GetInt(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetInt();
}

PLAFloat PLAObject::GetFloat(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetFloat();
}

const PLAVec2 &PLAObject::GetVec2(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec2();
}

const PLAVec3 &PLAObject::GetVec3(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec3();
}

const PLAVec4 &PLAObject::GetVec4(const PLAString &aName) const
{
  if (!_properties.contains(aName))
  { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Property does not exist."); }
  return _properties.at(aName).GetVec4();
}

void PLAObject::SetBool(const PLAString &aName, PLABool aValue)
{
  _properties[aName].SetBool(aValue);
}

void PLAObject::SetInt(const PLAString &aName, PLAInt aValue)
{
  _properties[aName].SetInt(aValue);
}

void PLAObject::SetFloat(const PLAString &aName, PLAFloat aValue)
{
  _properties[aName].SetFloat(aValue);
}

void PLAObject::SetVec2(const PLAString &aName, const PLAVec2 &aValue)
{
  _properties[aName].SetVec2(aValue);
}

void PLAObject::SetVec3(const PLAString &aName, const PLAVec3 &aValue)
{
  _properties[aName].SetVec3(aValue);
}

void PLAObject::SetVec4(const PLAString &aName, const PLAVec4 &aValue)
{
  _properties[aName].SetVec4(aValue);
}

void PLAObject::SetObjectName(const PLAString &aName)
{
  Binder::Error error(Binder::Error::None);
  this->Binder::Item::SetName(aName, &error);
  if (error != Binder::Error::None)
  {
    switch (error) {
      case Binder::Error::NameOverride :
      case Binder::Error::NameConversion :
        PLA_ERROR_ISSUE(PLAErrorType::Expect,
                        "Succeed to set object name with error. ERROR : %02d : %s",
                        error, GetBinderErrorMessage(error));
        break;
      default :
        PLA_ERROR_ISSUE(PLAErrorType::Assert,
                        "Failure to set object name. ERROR : %02d : %s",
                        error, GetBinderErrorMessage(error));
        break;
    }
  }
}

// GRABinder::Item /////////////////////////////////////////////////////////////

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
  GRA_PRINT("//-- PLAObject::Manager::PrintResource -"
            "-///////////////////////////////////////\n");
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