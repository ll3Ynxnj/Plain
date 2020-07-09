#include "PLAObject.hpp"

// PLAObject ///////////////////////////////////////////////////////////////////

PLAObject::PLAObject(PLAObjectType aType) :
_type(aType)
{

}

PLAObject::~PLAObject()
{

}

// PLAObject::Manager //////////////////////////////////////////////////////////

PLAObject::Manager PLAObject::Manager::_instance = PLAObject::Manager();

PLAObject::Manager::Manager()
{

}

PLAObject::Manager::~Manager()
{

}

void PLAObject::Manager::Init()
{

}

void PLAObject::Manager::Bind(PLAObject *aObject)
{
  aObject->SetId(_objects.size());
  _objects.push_back(aObject);
}

void PLAObject::Manager::PrintObjects() const
{
  for (PLAObject *object : _objects)
  {
    PLA_PRINT("%8d : %2d : %s\n", object->GetID(), object->GetType(),
              object->GetName().c_str());
  }
}
