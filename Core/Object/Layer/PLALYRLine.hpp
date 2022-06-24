#ifndef PLAIN_PLALYRLINE_HPP
#define PLAIN_PLALYRLINE_HPP

#include "PLAOBJLayer.hpp"
#include "Primitive/PLAPRMColor.hpp"

class PLALYRLine : public PLAOBJLayer
{
  PLAVec2 _vector = kPLAVec2None;
  PLAColor _color = kPLAColorNone;

public:
  static PLALYRLine *Create(const PLALine &aLine);

  PLALYRLine() = delete;
  PLALYRLine(const PLAVec3 &aOffset, const PLAVec2 &aVector,
             const PLAColor &aColor) :
    PLAOBJLayer(PLAOBJLayerType::Line, aOffset),//, "== PLALYRLine =="),
    _vector(aVector), _color(aColor) {};
  virtual ~PLALYRLine() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  PLALine GetLine() const;

  const PLAColor &GetColor() const;
  void SetColor(const PLAColor &aColor);
};

#endif //PLAIN_PLALYRLINE_HPP
