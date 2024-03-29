#ifndef PLAIN_PLALYRPOINT_HPP
#define PLAIN_PLALYRPOINT_HPP

#include "PLAOBJLayer.hpp"
#include "Primitive/PLAPRMColor.hpp"

class PLALYRPoint : public PLAOBJLayer
{
  PLAColor _color = kPLAColorNone;

public:
  static PLALYRPoint *Create(const PLAPoint &aPoint);

  PLALYRPoint() = delete;
  PLALYRPoint(const PLAVec3f &aOffset, const PLAColor &aColor) :
    PLAOBJLayer(PLALayerType::Point, aOffset),//, "== PLALYRPoint =="),
    _color(aColor) {};//, aStyle) {};
  virtual ~PLALYRPoint() {};

  virtual PLAVec3f GetSize() const;
  virtual void GetSize(PLAVec3f *aSize) const;
  virtual void SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot);

  virtual void SetImageClip(PLAOBJImageClip *aImageClip) { return; } // Stab

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  PLAPoint GetPoint() const;

  const PLAColor &GetColor() const;
  void SetColor(const PLAColor &aColor);
};

#endif //PLAIN_PLALYRPOINT_HPP
