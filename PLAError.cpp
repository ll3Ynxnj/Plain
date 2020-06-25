#include "PLAError.hpp"

PLAError * PLAError::Create(PLAErrorType aType, const std::string &aMessage)
{
  PLAError *error = new PLAError(aType, aMessage);
  PLAObject::Bind(error);
  return error;
}

void PLAError::Issue(const char *file, const int line, const PLAErrorType type,
                     const char *format, ...)
{
  std::string log = PLADebug::Format("[%s]%s(%d) : %s\n", "ERROR", file, line, format);
  va_list args;
  va_start(args, format);
  vfprintf(stderr, log.c_str(), args);
  va_end(args);
  Manager::GetInstance()->Issue(file, line, type, "");
}

PLAError::PLAError(PLAErrorType aType, const std::string &aMessage) :
  _type(aType), _message(aMessage)
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

void PLAError::Manager::Issue(const char *aFile, const int aLine,
                              PLAErrorType aType, const std::string &aMessage)
{
  PLAError *error = PLAError::Create(aType, aMessage);
  _errors.push(error);
  switch (error->GetType())
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
