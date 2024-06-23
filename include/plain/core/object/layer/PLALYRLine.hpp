#ifndef PLAIN_PLALYRLINE_HPP
#define PLAIN_PLALYRLINE_HPP

#include "plain/core/object/layer/PLAOBJLayer.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"

class PLALYRLine : public PLAOBJLayer
{
  PLAVec2f _vector = kPLAVec2fNone;
  PLAColor _color = kPLAColorNone;

public:
  static PLALYRLine *Create(const PLALine &aLine);

  PLALYRLine() = delete;
  PLALYRLine(const PLAVec3f &aOffset, const PLAVec2f &aVector,
             const PLAColor &aColor) :
    PLAOBJLayer(PLALayerType::Line, aOffset),//, "== PLALYRLine =="),
    _vector(aVector), _color(aColor) {};
  virtual ~PLALYRLine() {};

  PLAVec3f GetSize() const override;
  void GetSize(PLAVec3f *aSize) const override;
  void SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot) override;

  void SetImageClip(PLAOBJImageClip *aImageClip) override { return; } // Stab
  void SetVideoClip(PLAOBJVideoClip *aVideoClip) override { return; } // Stab

  bool IsCollideWithPoint(const PLAPoint &aPoint) const override;
  bool IsCollideWithLine(const PLALine &aLine) const override;
  bool IsCollideWithRect(const PLARect &aRect) const override;
  bool IsCollideWithCircle(const PLACircle &aCircle) const override;

  PLALine GetLine() const;

  const PLAColor &GetColor() const;
  void SetColor(const PLAColor &aColor);
};

#endif //PLAIN_PLALYRLINE_HPP
