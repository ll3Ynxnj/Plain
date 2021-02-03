#include "PLAObject.hpp"
#include "PLAError.hpp"

// PLAObject ///////////////////////////////////////////////////////////////////
void PLAObject::Delete(PLAObject *aObject)
{
  PLAObject::Manager::Ref()->Unbind(aObject);
  PLA_DELETE(aObject);
}

PLAObject::PLAObject(PLAObjectType aType) :
_type(aType)
{

}

PLAObject::PLAObject(PLAObjectType aType, const std::string &aName) :
_type(aType), _name(aName)
{

}

PLAObject::~PLAObject()
{

}

void PLAObject::PrintObject() const
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
  if (_emptyIndices.size())
  {
    size_t id = _emptyIndices.top();
    aObject->SetId(id);
    if (_objects[id] != nullptr)
    { PLA_ERROR_ISSUE(PLAErrorType::Assert, "Overwrite pointer not nullptr."); }
    _objects[id] = aObject;
    _emptyIndices.pop();
  }
  else
  {
    aObject->SetId(_objects.size());
    _objects.push_back(aObject);
  }
}

void PLAObject::Manager::Unbind(PLAObject *aObject)
{
  size_t id = aObject->GetObjectId();
  _objects[id] = nullptr;
}

void PLAObject::Manager::PrintObjects() const
{
  for (const PLAObject *object : _objects) { object->PrintObject(); }
}
