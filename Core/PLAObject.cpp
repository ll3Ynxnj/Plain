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

void PLAObject::PrintObject() const
{
  GRA_PRINT("%04x : %32s : %d\n",
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
