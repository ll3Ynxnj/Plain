#include "PLAObject.hpp"
#include "PLAError.hpp"

// PLAObject ///////////////////////////////////////////////////////////////////
void PLAObject::Delete(PLAObject *aObject)
{
  GRABinder<PLAObject>::Error error(GRABinder<PLAObject>::Error::None);
  PLAObject::Manager::RefInstance()->Unbind(aObject, &error);
  if (error != GRABinder<PLAObject>::Error::None) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert, "Failed to delete. ERROR : %02d", error);
  }
  GRA_DELETE(aObject);
}

PLAObject::PLAObject(PLAObjectType aType) :
GRABinder<PLAObject>::Item(),
_type(aType)
{

}

PLAObject::PLAObject(PLAObjectType aType, const std::string &aName) :
GRABinder<PLAObject>::Item(aName),
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

// PLAObject::Manager //////////////////////////////////////////////////////////

PLAObject::Manager PLAObject::Manager::_instance = PLAObject::Manager();

PLAObject::Manager::Manager():
GRABinder<PLAObject>()
{

}

PLAObject::Manager::~Manager()
{

}

void PLAObject::Manager::PrintObjects() const
{
  GRA_PRINT("//-- PLAObject::Manager::PrintResource -"
            "-///////////////////////////////////////\n");
  GRA_PRINT("  ID |                             NAME "
            "| TYPE |                                \n");
  GRA_PRINT("-----|----------------------------------"
            "|------|--------------------------------\n");
  for (GRABinder<PLAObject>::Item *item : this->GetItems())
  {
    const PLAObject *object = static_cast<const PLAObject *>(item);
    GRA_PRINT("%04x | %32s | %4d |                               \n",
              object->GetId(), object->GetName().c_str(),
              object->GetObjectType());
  }
  GRA_PRINT("////////////////////////////////////////"
            "////////////////////////////////////////\n");
}