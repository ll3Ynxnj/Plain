#include "PLAObject.hpp"
#include "PLAError.hpp"

// PLAObject ///////////////////////////////////////////////////////////////////
const std::map<PLAObject::Binder::Error, const char *> PLAObject::kBinderErrorMessages =
{
  { Binder::Error::OverwriteItem, "Overwrite item" },
  { Binder::Error::RegisterExistingKeyToMap, "Register existing key to map" },
  { Binder::Error::NotExistInMap, "Not exist in map" },
};

const char *PLAObject::GetBinderErrorMessage(Binder::Error aError)
{
  return kBinderErrorMessages.at(aError);
}

void PLAObject::Bind(PLAObject *aObject)
{
  Binder::Error error(Binder::Error::None);
  PLAObject::Manager::Instance()->Bind(aObject, &error);
  if (error != Binder::Error::None) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAObject binding. ERROR : %02d : %s",
                    error, GetBinderErrorMessage(error));
  }
}

void PLAObject::Delete(PLAObject *aObject)
{
  Binder::Error error(Binder::Error::None);
  PLAObject::Manager::Instance()->Unbind(aObject, &error);
  if (error != Binder::Error::None) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to delete. ERROR : %02d : %s",
                    error, GetBinderErrorMessage(error));
  }
  GRA_DELETE(aObject);
}

PLAObject *PLAObject::Manager::Object(const std::string &aKey)
{
  Binder::Error error(Binder::Error::None);
  return static_cast<PLAObject *>(_instance.RefItem(aKey, &error));
}

PLAObject::PLAObject(PLAObjectType aType) :
Binder::Item(kPLAStrUndefined, Manager::Instance()),
_type(aType)
{

}

PLAObject::PLAObject(PLAObjectType aType, const std::string &aName) :
Binder::Item(aName, Manager::Instance()),
_type(aType)
{

}

PLAObject::~PLAObject()
{

}

std::string PLAObject::GetObjectDescription() const
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

// PLAObject::Manager //////////////////////////////////////////////////////////

PLAObject::Manager PLAObject::Manager::_instance = PLAObject::Manager();

PLAObject::Manager::Manager():
Binder()
{

}

PLAObject::Manager::~Manager()
{

}

void PLAObject::SetObjectName(const std::string &aName)
{
  Binder::Error error(Binder::Error::None);
  this->Binder::Item::SetName(aName, &error);
  if (error != Binder::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failure to set object name. ERROR : %02d : %s",
                    error, GetBinderErrorMessage(error));
  }
}

void PLAObject::Manager::PrintObjects() const
{
  GRA_PRINT("//-- PLAObject::Manager::PrintResource -"
            "-///////////////////////////////////////\n");
  GRA_PRINT("  ID |                             NAME "
            "| TYPE |                                \n");
  GRA_PRINT("-----|----------------------------------"
            "|------|--------------------------------\n");
  for (Binder::Item *item : this->GetItems())
  {
    const PLAObject *object = static_cast<const PLAObject *>(item);
    GRA_PRINT("%04x | %32s | %4d |                               \n",
              object->GetId(), object->GetName().c_str(),
              object->GetObjectType());
  }
  GRA_PRINT("////////////////////////////////////////"
            "////////////////////////////////////////\n");
}