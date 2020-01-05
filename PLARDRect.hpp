#ifndef PLARDRECT_HPP
#define PLARDRECT_HPP

#include "PLARenderingData.hpp"

#include "./Grain/GRARect.h"
#include "./Grain/GRAColorRGBA.h"

struct PLARDRect : public PLARenderingData
{
  GRARect rect;
  GRAColorRGBA color;

  PLARDRect(const GRARect &aRect, const GRAColorRGBA &aColor) :
    rect(aRect), color(aColor) {};
  PLARDRect(float aPx, float aPy, float aSw, float aSh,
            float aCr, float aCg, float aCb, float aCa) :
    rect((GRARect){{aPx, aPy}, {aSw, aSh}}),
    color((GRAColorRGBA){aCr, aCg, aCb, aCa}) {};
  virtual ~PLARDRect() {};
};

#endif
