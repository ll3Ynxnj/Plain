#ifndef PLAIN_PLAERROR_HPP
#define PLAIN_PLAERROR_HPP

#include <string>
#include "PLAObj.hpp"
#include "PLAErrorType.hpp"

class PLAError : public PLAObj
{
  PLAErrorType _type;
  std::string _message;

public:
  PLAError(PLAErrorType aType, const std::string &aMessage);
  ~PLAError();

  PLAErrorType GetType();
  const std::string &GetMessage();
};

#endif // PLAIN_PLAERROR_HPP
