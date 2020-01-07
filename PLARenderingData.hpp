#ifndef PLARENDERINGDATA_HPP
#define PLARENDERINGDATA_HPP

#include "PLARenderingDataType.hpp"

struct PLARenderingData
{
  PLARenderingDataType type;

  PLARenderingData(PLARenderingDataType aType) : type(aType) {};
  virtual ~PLARenderingData() {};
};

#endif
