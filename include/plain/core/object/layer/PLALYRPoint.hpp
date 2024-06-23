#ifndef PLAIN_PLALYRPOINT_HPP
#define PLAIN_PLALYRPOINT_HPP

#include "plain/core/object/layer/PLAOBJLayer.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"

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

  PLAVec3f GetSize() const override;
  void GetSize(PLAVec3f *aSize) const override;
  void SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot) override;

  void SetImageClip(PLAOBJImageClip *aImageClip) override { return; } // Stab
  void SetVideoClip(PLAOBJVideoClip *aVideoClip) override { return; } // Stab

  bool IsCollideWithPoint(const PLAPoint &aPoint) const override;
  bool IsCollideWithLine(const PLALine &aLine) const override;
  bool IsCollideWithRect(const PLARect &aRect) const override;
  bool IsCollideWithCircle(const PLACircle &aCircle) const override;

  PLAPoint GetPoint() const;

  const PLAColor &GetColor() const;
  void SetColor(const PLAColor &aColor);
};

#endif //PLAIN_PLALYRPOINT_HPP
