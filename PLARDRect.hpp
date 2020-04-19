#ifndef PLARDRECT_HPP
#define PLARDRECT_HPP

#include "PLARenderingData.hpp"
#include "Grain/GRARect.hpp"
#include "Grain/GRAColor.hpp"

struct PLARDRect : public PLARenderingData
{
  GRARect rect;
  GRAColor color;

  PLARDRect() :
    PLARenderingData(PLARenderingDataType::Rect),
    rect(kGRARectNorm),
    color(kGRAColorNorm) {};
  PLARDRect(const GRARect &aRect, const GRAColor &aColor) :
    PLARenderingData(PLARenderingDataType::Rect),
    rect(aRect), color(aColor) {};
  PLARDRect(float aPx, float aPy, float aSw, float aSh,
            float aCr, float aCg, float aCb, float aCa) :
    PLARenderingData(PLARenderingDataType::Rect),
    rect(GRAPoint(aPx, aPy, 0), GRASize(aSw, aSh, 0)),
    color(aCr, aCg, aCb, aCa) {};
  virtual ~PLARDRect() {};
};

#endif
