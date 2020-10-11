#ifndef PLAIN_PLAERROR_HPP
#define PLAIN_PLAERROR_HPP

#include <string>
#include <queue>
#include "PLAObject.hpp"
#include "PLAErrorType.hpp"

#define PLA_ERROR_ISSUE(...)\
PLAError::Manager::GetInstance()->\
Issue(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

class PLAError : public PLAObject
{
  PLAErrorType _type = PLAErrorType::None;
  const std::string _file = kPLACharUndefined;
  const int _line = 0;
  std::string _message = kPLACharUndefined;

public:
  static PLAError *Create(PLAErrorType aType, const std::string &aFile,
                          int aLine, const std::string &aMessage);

  PLAError(PLAErrorType aType, const std::string &aFile, int aLine,
           const std::string &aMessage);
  ~PLAError();

  PLAErrorType GetType();
  const std::string &GetMessage();

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager
  {
    static Manager _instance;

    std::queue<PLAError *> _errors;

    Manager();

  public:
    static Manager *GetInstance() { return &_instance; }

    ~Manager();

    void Init();
    void Reset();
    void Issue(const char *aFile, const char *aFunc, const int aLine,
               const PLAErrorType aType, const char *aFormat, ...);
  };
};

#endif // PLAIN_PLAERROR_HPP
