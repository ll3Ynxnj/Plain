#ifndef PLAIN_ENGINE_PLAERROR_HPP
#define PLAIN_ENGINE_PLAERROR_HPP

#include <string>
#include <queue>
#include "PLAObject.hpp"
#include "PLAErrorType.hpp"

#define PLA_ERROR_ISSUE(...)\
PLAError::Manager::Instance()->\
Issue(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

class PLAError : public PLAObject
{
  PLAErrorType _type = PLAErrorType::None;
  const PLAString _file = kPLAStrUndefined;
  const PLAInt _line = 0;
  PLAString _message = kPLAStrUndefined;

protected:
  PLAError();
  PLAError(PLAErrorType aType, const PLAString &aFile, PLAInt aLine,
           const PLAString &aMessage);

public:
  static PLAError *Create(PLAErrorType aType, const PLAString &aFile,
                          PLAInt aLine, const PLAString &aMessage);

  virtual ~PLAError();

  PLAErrorType GetType();
  const PLAString &GetMessage();

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager
  {
    static Manager _instance;

    std::queue<PLAError *> _errors;

    Manager();

  public:
    static Manager *Instance() { return &_instance; }

    ~Manager();

    void Init();
    void Reset();
    void Issue(const char *aFile, const char *aFunc, const int aLine,
               const PLAErrorType aType, const char *aFormat, ...);
  };
};

#endif // PLAIN_ENGINE_PLAERROR_HPP
