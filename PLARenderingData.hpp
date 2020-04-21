#ifndef PLAIN_PLARENDERINGDATA_HPP
#define PLAIN_PLARENDERINGDATA_HPP

#include "PLAObj.hpp"
#include "PLARenderingDataType.hpp"

struct PLARenderingData : public PLAObj
{
  PLARenderingDataType type;
  PLAVec3 offset;

  explicit PLARenderingData(PLARenderingDataType aType) :
      type(aType), offset(0, 0, 0) {};
  PLARenderingData(PLARenderingDataType aType, const PLAVec3 &aOffset) :
    type(aType), offset(aOffset) {};
  virtual ~PLARenderingData() {};
};

#endif // PLAIN_PLARENDERINGDATA_HPP
