#ifndef PLARDRECT_HPP
#define PLARDRECT_HPP

#include "PLARenderingData.hpp"

#include "./Grain/GRARect.h"
#include "./Grain/GRAColor.h"

struct PLARDRect : public PLARenderingData
{
  GRARect rect;
  GRAColor color;

  PLARDRect(const GRARect &aRect, const GRAColor &aColor) :
    PLARenderingData(PLARenderingDataType::Rect),
    rect(aRect), color(aColor) {};
  PLARDRect(float aPx, float aPy, float aSw, float aSh,
            float aCr, float aCg, float aCb, float aCa) :
    PLARenderingData(PLARenderingDataType::Rect),
    rect((GRARect){{aPx, aPy}, {aSw, aSh}}),
    color((GRAColor){aCr, aCg, aCb, aCa}) {};
  virtual ~PLARDRect() {};
};

#endif
