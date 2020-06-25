#ifndef PLAIN_PLAERROR_HPP
#define PLAIN_PLAERROR_HPP

#include <string>
#include <queue>
#include "PLAObject.hpp"
#include "PLAErrorType.hpp"

#define PLA_ERROR_ISSUE(...)\
PLAError::Issue(__FILE__, __LINE__, __VA_ARGS__)\

class PLAError : public PLAObject
{
  PLAErrorType _type = PLAErrorType::None;
  std::string _message = kPLACharUndefined;

public:
  static PLAError *Create(PLAErrorType aType, const std::string &aMessage);
  static void Init() { Manager::GetInstance()->Init(); };
  static void Reset() { Manager::GetInstance()->Reset(); };
  static void Issue(const char *aFile, const int aLine,
                    const PLAErrorType aType, const char *aFormat, ...);

  PLAError(PLAErrorType aType, const std::string &aMessage);
  ~PLAError();

  PLAErrorType GetType();
  const std::string &GetMessage();

private:
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
    void Issue(const char *aFile, const int aLine,
               const PLAErrorType aType, const std::string &aMessage);
  };
};

#endif // PLAIN_PLAERROR_HPP
