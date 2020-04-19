#ifndef PLARENDERINGDATA_HPP
#define PLARENDERINGDATA_HPP

#include "PLARenderingDataType.hpp"
#include "Grain/GRAPoint.hpp"

struct PLARenderingData
{
  PLARenderingDataType type;
  GRAPoint offset;

  explicit PLARenderingData(PLARenderingDataType aType) :
      type(aType), offset(0, 0, 0) {};
  PLARenderingData(PLARenderingDataType aType, const GRAPoint &aOffset) :
    type(aType), offset(aOffset) {};
  virtual ~PLARenderingData() {};
};

#endif
