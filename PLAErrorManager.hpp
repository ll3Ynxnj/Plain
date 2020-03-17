#ifndef PLAERRORMANAGER_HPP
#define PLAERRORMANAGER_HPP

#include <queue>
#include <string>
#include "PLAError.hpp"
#include "PLAErrorType.hpp"

class PLAErrorManager
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

#endif
