#ifndef PLAIN_PLAERRORMANAGER_HPP
#define PLAIN_PLAERRORMANAGER_HPP

#include <queue>
#include <string>
#include "PLAObj.hpp"
#include "PLAError.hpp"
#include "PLAErrorType.hpp"

class PLAErrorManager : public PLAObj
{
  static PLAErrorManager _instance;

  std::queue<PLAError *> _errors;

  PLAErrorManager();

public:
  static PLAErrorManager *GetInstance() { return &_instance; }

  ~PLAErrorManager();

  void Init();
  void Reset();

  void Throw(PLAErrorType aType, const std::string &aMessage);
};

#endif // PLAIN_PLAERRORMANAGER_HPP
