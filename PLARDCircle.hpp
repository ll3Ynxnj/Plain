#ifndef PLAIN_PLARDCIRCLE_HPP
#define PLAIN_PLARDCIRCLE_HPP

#include "PLARenderingData.hpp"

struct PLARDCircle : public PLARenderingData
{
  static const int kSplitMin = 12;
  static const int kSplitMax = 256;

  PLACircle circle;
  PLAColor color;
  int split;

  PLARDCircle() :
    PLARenderingData(PLARenderingDataType::Circle),
    circle(kPLACircleNorm),
    color(kPLAColorNorm),
    split(kSplitMin) {};
  PLARDCircle(const PLACircle &aCircle, const PLAColor &aColor,
              int aSplit) :
    PLARenderingData(PLARenderingDataType::Circle),
    circle(aCircle), color(aColor), split(aSplit) {};
  PLARDCircle(float aPx, float aPy, float aRadius,
              float aCr, float aCg, float aCb, float aCa,
              int aSplit) :
    PLARenderingData(PLARenderingDataType::Circle),
    circle(PLAVec3(aPx, aPy, 0), aRadius),
    color(aCr, aCg, aCb, aCa),
    split(aSplit) {};
  virtual ~PLARDCircle() {};
};

#endif // PLAIN_PLARDCIRCLE_HPP
