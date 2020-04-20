#ifndef PLARDRECT_HPP
#define PLARDRECT_HPP

#include "PLARenderingData.hpp"
#include "PLAType.hpp"

struct PLARDRect : public PLARenderingData
{
  PLARect rect;
  PLAColor color;

  PLARDRect() :
    PLARenderingData(PLARenderingDataType::Rect),
    rect(kPLARectNorm),
    color(kPLAColorNorm) {};
  PLARDRect(const PLARect &aRect, const PLAColor &aColor) :
    PLARenderingData(PLARenderingDataType::Rect),
    rect(aRect), color(aColor) {};
  PLARDRect(float aPx, float aPy, float aSw, float aSh,
            float aCr, float aCg, float aCb, float aCa) :
    PLARenderingData(PLARenderingDataType::Rect),
    rect(PLAVec3(aPx, aPy, 0), PLAVec3(aSw, aSh, 0)),
    color(aCr, aCg, aCb, aCa) {};
  virtual ~PLARDRect() {};
};

#endif
