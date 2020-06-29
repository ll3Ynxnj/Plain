#include "PLAError.hpp"

PLAError * PLAError::Create(PLAErrorType aType, const std::string &aFile,
                            int aLine, const std::string &aMessage)
{
  PLAError *error = new PLAError(aType, aFile, aLine, aMessage);
  PLAObject::Bind(error);
  return error;
}

void PLAError::Issue(const char *file, const int line, const PLAErrorType type,
                     const char *format, ...)
{
  static const char *kLogFormat = PLADebug::kLogFormat;
  static const int kLogBuffer = PLADebug::kLogBuffer;

  char log[kLogBuffer];
  snprintf(log, kLogBuffer, kLogFormat, "ERROR", file, line, format);
  va_list args;
  char message[kLogBuffer];
  va_start(args, format);
  vsnprintf(message, kLogBuffer, log, args);
  va_end(args);
  fprintf(stderr, message);

  Manager::GetInstance()->Issue(file, line, type, std::string(message));
}

PLAError::PLAError(PLAErrorType aType, const std::string &aFile,
                   int aLine, const std::string &aMessage) :
  _type(aType), _file(aFile), _line(aLine), _message(aMessage)
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
  PLAError *error = PLAError::Create(aType, aFile, aLine, aMessage);
  _errors.push(error);
  switch (error->GetType())
  {
    case PLAErrorType::Assert :
      PLA_ASSERT("PLAErrorType::Assert detected.");
      break;
    case PLAErrorType::Expect :
      break;
    default :
      PLA_ASSERT("Unexpected PLAErrorType detected. type : %d", error->GetType());
      break;
  }
}
