#include "PLAOBJError.hpp"

PLAOBJError * PLAOBJError::Create(PLAErrorType aType, const PLAString &aFile,
                                  PLAInt aLine, const PLAString &aMessage)
{
  PLAOBJError *error = new PLAOBJError(aType, aFile, aLine, aMessage);
  error->Bind();
  return error;
}

PLAOBJError::PLAOBJError(PLAErrorType aType, const PLAString &aFile, PLAInt aLine,
                         const PLAString &aMessage) :
  PLAObject(PLAObjectType::Error),//, "== PLAOBJError =="),
  _type(aType), _file(aFile), _line(aLine), _message(aMessage)
{

}

PLAOBJError::~PLAOBJError()
{

}

PLAErrorType PLAOBJError::GetType()
{
  return _type;
}

const PLAString &PLAOBJError::GetMessage()
{
  return _message;
}

// PLAOBJError::Manager ///////////////////////////////////////////////////////////

PLAOBJError::Manager PLAOBJError::Manager::_instance = PLAOBJError::Manager();

PLAOBJError::Manager::Manager()
{

}

PLAOBJError::Manager::~Manager()
{

}

void PLAOBJError::Manager::Init()
{

}

void PLAOBJError::Manager::Reset()
{
  _instance = PLAOBJError::Manager();
}

void PLAOBJError::Manager::Issue(const char *aFile, const char *aFunc,
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
  fprintf(stderr, "%s", message);

  //PLAOBJError *error = PLAOBJError::Create(aType, aFile, aLine, message);
  //_errors.push(error);
  switch (aType)//error->GetType())
  {
    case PLAErrorType::Assert :
      GRA_ASSERT("PLAErrorType::Assert detected.");
      break;
    case PLAErrorType::Expect :
      break;
    default :
      GRA_ASSERT("Unexpected PLAErrorType detected. type : %d",
                 aType);//error->GetType());
      break;
  }
}
