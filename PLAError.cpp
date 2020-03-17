#include "PLAError.hpp"

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
