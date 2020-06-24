#include "PLAError.hpp"

PLAError * PLAError::Create(PLAErrorType aType, const std::string &aMessage)
{
  PLAError *error = new PLAError(aType, aMessage);
  PLAObject::Bind(error);
  return error;
}

PLAError::PLAError(PLAErrorType aType, const std::string &aMessage) :
  _type(aType),
  _message(aMessage)
{

}

PLAError::~PLAError()
{

}

PLAErrorType PLAError::GetType()
{
  return _type;
}

const std::string &PLAError::GetMessage()
{
  return _message;
}

PLAError::Manager PLAError::Manager::_instance = PLAError::Manager();

PLAError::Manager::Manager()
{

}

PLAError::Manager::~Manager()
{

}

void PLAError::Manager::Init()
{

}

void PLAError::Manager::Reset()
{
  _instance = PLAError::Manager();
}

void PLAError::Manager::Throw(PLAErrorType aType, const std::string &aMessage)
{
  try
  {
    PLAError *error = PLAError::Create(aType, aMessage);
    _errors.push(error);
    throw error;
  }
  catch (PLAError *aError)
  {
    switch (aError->GetType())
    {
      case PLAErrorType::Assert :
      PLA_ASSERT(aMessage.c_str());
        break;
      case PLAErrorType::Expect :
        break;
      default :
      PLA_ASSERT(aMessage.c_str());
        break;
    }
  }
}
