#include "PLAObject.hpp"

PLAObject::PLAObject()
{

}

PLAObject::~PLAObject()
{

}

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
  //aObject->SetId(_objects.size());
  //_objects.push_back(aObject);
}
