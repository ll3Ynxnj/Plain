#ifndef PLARDCIRCLE_HPP
#define PLARDCIRCLE_HPP

#include "PLARenderingData.hpp"

#include "./Grain/GRACircle.h"
#include "./Grain/GRAColor.h"

struct PLARDCircle : public PLARenderingData
{
  GRACircle circle;
  GRAColor color;
  GRAInt split;

  PLARDCircle(const GRACircle &aCircle, const GRAColor &aColor,
              GRAInt aSplit) :
    PLARenderingData(PLARenderingDataType::Circle),
    circle(aCircle), color(aColor), split(aSplit) {};
  PLARDCircle(GRAFloat aPx, GRAFloat aPy, GRAFloat aRadius,
              GRAFloat aCr, GRAFloat aCg, GRAFloat aCb, GRAFloat aCa,
              GRAInt aSplit) :
    PLARenderingData(PLARenderingDataType::Circle),
    circle((GRACircle){{aPx, aPy}, aRadius }),
    color((GRAColor){aCr, aCg, aCb, aCa}),
    split(aSplit) {};
  virtual ~PLARDCircle() {};
};

#endif
