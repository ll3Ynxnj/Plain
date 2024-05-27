#ifndef PLAIN_PLALYRLINE_HPP
#define PLAIN_PLALYRLINE_HPP

#include "Core/Object/Layer/PLAOBJLayer.hpp"
#include "Core/Primitive/PLAPRMColor.hpp"

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

  virtual PLAVec3f GetSize() const;
  virtual void GetSize(PLAVec3f *aSize) const;
  virtual void SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot);

  virtual void SetImageClip(PLAOBJImageClip *aImageClip) { return; } // Stab

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  PLALine GetLine() const;

  const PLAColor &GetColor() const;
  void SetColor(const PLAColor &aColor);
};

#endif //PLAIN_PLALYRLINE_HPP
