#ifndef PLARDCIRCLE_HPP
#define PLARDCIRCLE_HPP

#include "PLARenderingData.hpp"
#include "Grain/GRACircle.h"
#include "Grain/GRAColor.h"

struct PLARDCircle : public PLARenderingData
{
  static const int kSplitMin = 12;
  static const int kSplitMax = 256;

  GRACircle circle;
  GRAColor color;
  int split;

  PLARDCircle() :
    PLARenderingData(PLARenderingDataType::Circle),
    circle(kGRACircleNorm),
    color(kGRAColorNorm),
    split(kSplitMin) {};
  PLARDCircle(const GRACircle &aCircle, const GRAColor &aColor,
              int aSplit) :
    PLARenderingData(PLARenderingDataType::Circle),
    circle(aCircle), color(aColor), split(aSplit) {};
  PLARDCircle(float aPx, float aPy, float aRadius,
              float aCr, float aCg, float aCb, float aCa,
              int aSplit) :
    PLARenderingData(PLARenderingDataType::Circle),
    circle((GRACircle){{aPx, aPy}, aRadius }),
    color((GRAColor){aCr, aCg, aCb, aCa}),
    split(aSplit) {};
  virtual ~PLARDCircle() {};
};

#endif
