#include "PLAError.hpp"
#include "PLAErrorManager.hpp"

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
    PLAError *error = new PLAError(aType, aMessage);
    _errors.push(error);
    throw error;
  }
  catch (PLAError *aError)
  {
    switch (aError->GetType())
    {
      case PLAErrorType::Assert :
        PLADebug::Assert(aMessage.c_str());
        break;
      case PLAErrorType::Expect :
        break;
      default :
        PLADebug::Assert(aMessage.c_str());
        break;
    }
  }
}
