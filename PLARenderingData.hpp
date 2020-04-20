#ifndef PLARENDERINGDATA_HPP
#define PLARENDERINGDATA_HPP

#include "PLARenderingDataType.hpp"
#include "PLAType.hpp"

struct PLARenderingData
{
  PLARenderingDataType type;
  PLAVec3 offset;

  explicit PLARenderingData(PLARenderingDataType aType) :
      type(aType), offset(0, 0, 0) {};
  PLARenderingData(PLARenderingDataType aType, const PLAVec3 &aOffset) :
    type(aType), offset(aOffset) {};
  virtual ~PLARenderingData() {};
};

#endif
