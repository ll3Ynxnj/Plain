#include "PLAError.hpp"

PLAError * PLAError::Create(PLAErrorType aType, const std::string &aFile,
                            int aLine, const std::string &aMessage)
{
  PLAError *error = new PLAError(aType, aFile, aLine, aMessage);
  PLAObject::Bind(error);
  return error;
}

PLAError::PLAError(PLAErrorType aType, const std::string &aFile, int aLine,
                   const std::string &aMessage) :
  PLAObject(PLAObjectType::Error),//, "== PLAError =="),
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

// PLAError::Manager ///////////////////////////////////////////////////////////

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

void PLAError::Manager::Issue(const char *aFile, const char *aFunc,
                              const int aLine, PLAErrorType aType,
                              const char *aFormat, ...)
{
  static const char *kLogFormat = GRADebug::kLogFormat;
  static const int kLogBuffer = GRADebug::kLogBuffer;

  char log[kLogBuffer] = {0};
  snprintf(log, kLogBuffer, kLogFormat, "ERROR", aFile, aFunc, aLine, aFormat);
  va_list args;
  char message[kLogBuffer];
  va_start(args, aFormat);
  vsnprintf(message, kLogBuffer, log, args);
  va_end(args);
  fprintf(stderr, message);

  PLAError *error = PLAError::Create(aType, aFile, aLine, message);
  _errors.push(error);
  switch (error->GetType())
  {
    case PLAErrorType::Assert :
      GRA_ASSERT("PLAErrorType::Assert detected.");
      break;
    case PLAErrorType::Expect :
      break;
    default :
      GRA_ASSERT("Unexpected PLAErrorType detected. type : %d", error->GetType());
      break;
  }
}
