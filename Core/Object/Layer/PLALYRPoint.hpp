#ifndef PLAIN_PLALYRPOINT_HPP
#define PLAIN_PLALYRPOINT_HPP

#include "PLALayer.hpp"
#include "Primitive/PLAColor.hpp"

class PLALYRPoint : public PLALayer
{
  PLAColor _color = kPLAColorNone;

public:
  static PLALYRPoint *Create(const PLAPoint &aPoint);

  PLALYRPoint() = delete;
  PLALYRPoint(const PLAVec3 &aOffset, const PLAColor &aColor) :
    PLALayer(PLALayerType::Point, aOffset),//, "== PLALYRPoint =="),
    _color(aColor) {};//, aStyle) {};
  virtual ~PLALYRPoint() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  PLAPoint GetPoint() const;

  const PLAColor &GetColor() const;
  void SetColor(const PLAColor &aColor);
};

#endif //PLAIN_PLALYRPOINT_HPP
