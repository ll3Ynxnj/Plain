#ifndef PLAIN_ENGINE_PLAOBJERROR_HPP
#define PLAIN_ENGINE_PLAOBJERROR_HPP

#include <string>
#include <queue>
#include "Core/Object/PLAObject.hpp"
#include "Core/PLAErrorType.hpp"

#define PLA_ERROR_ISSUE(...)\
PLAOBJError::Manager::Instance()->\
Issue(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

class PLAOBJError : public PLAObject
{
  PLAErrorType _type = PLAErrorType::None;
  const PLAString _file = kPLAStrUndefined;
  const PLAInt _line = 0;
  PLAString _message = kPLAStrUndefined;

protected:
  PLAOBJError();
  PLAOBJError(PLAErrorType aType, const PLAString &aFile, PLAInt aLine,
              const PLAString &aMessage);

public:
  static PLAOBJError *Create(PLAErrorType aType, const PLAString &aFile,
                             PLAInt aLine, const PLAString &aMessage);

  virtual ~PLAOBJError();

  PLAErrorType GetType();
  const PLAString &GetMessage();

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager
  {
    static Manager _instance;

    std::queue<PLAOBJError *> _errors;

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

#endif // PLAIN_ENGINE_PLAOBJERROR_HPP
