#include "PLAObject.hpp"

// PLAObject ///////////////////////////////////////////////////////////////////

PLAObject::PLAObject(PLAObjectType aType) :
_type(aType)
{

}

PLAObject::~PLAObject()
{

}

void PLAObject::Print() const
{
  PLA_PRINT("%04x : %2x : %s\n", _id, _type, _name.c_str());
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
  for (const PLAObject *object : _objects) { object->Print(); }
}
