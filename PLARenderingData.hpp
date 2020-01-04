#ifndef PLARENDERINGDATA_HPP
#define PLARENDERINGDATA_HPP

#include "./Grain/GRARect.h"
#include "./Grain/GRAColorRGBA.h"

struct PLARenderingData
{
  PLARenderingData() {};
  virtual ~PLARenderingData() {};
};

struct PLARDRect : public PLARenderingData
{
  GRARect rect;
  GRAColorRGBA color;

  PLARDRect(const GRARect &aRect, const GRAColorRGBA &aColor) :
  rect(aRect), color(aColor) {};
  virtual ~PLARDRect() {};
};

#endif
