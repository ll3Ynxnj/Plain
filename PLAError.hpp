#ifndef PLAIN_PLAERROR_HPP
#define PLAIN_PLAERROR_HPP

#include <string>
#include <queue>
#include "PLAObj.hpp"
#include "PLAErrorType.hpp"

class PLAError : public PLAObj
{
  PLAErrorType _type = PLAErrorType::None;
  std::string _message = kPLACharUndefined;

public:
  static void Init() { PLAError::Manager::GetInstance()->Init(); };
  static void Reset() { PLAError::Manager::GetInstance()->Reset(); };
  static void Throw(PLAErrorType aType, const std::string &aMessage)
  { PLAError::Manager::GetInstance()->Throw(aType, aMessage); };

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

    void Throw(PLAErrorType aType, const std::string &aMessage);
  };
};

#endif // PLAIN_PLAERROR_HPP
