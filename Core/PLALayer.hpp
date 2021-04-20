#ifndef PLAIN_ENGINE_PLALAYER_HPP
#define PLAIN_ENGINE_PLALAYER_HPP

#include "PLAObject.hpp"
#include "PLALayerType.hpp"

class PLALayer : public PLAObject
{
  PLALayerType _type = PLALayerType::None;
  PLAVec3 _offset = kPLAVec3None;

public:
  static PLALayer *Create(const PLALayer &aLayer);

  PLALayer() = delete;
  PLALayer(PLALayerType aType, const PLAVec3 &aOffset, const std::string &aName);
  virtual ~PLALayer();

  PLALayerType GetLayerType() const { return _type; };
  const PLAVec3 &GetOffset() const { return _offset; };
  void SetOffset(const PLAVec3 &aOffset) { _offset = aOffset; }

  virtual PLAVec3 GetSize() const = 0;
  virtual void GetSize(PLAVec3 *aSize) const = 0;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot) = 0;

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const = 0;
  virtual bool IsCollideWithLine(const PLALine &aLine) const = 0;
  virtual bool IsCollideWithRect(const PLARect &aRect) const = 0;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const = 0;
};

class PLALYRPoint : public PLALayer
{
  PLAColor _color = kPLAColorNone;

public:
  static PLALYRPoint *Create(const PLAPoint &aPoint);

  PLALYRPoint() = delete;
  PLALYRPoint(const PLAVec3 &aOffset, const PLAColor &aColor) :
    PLALayer(PLALayerType::Point, aOffset, "== PLALYRPoint =="),
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

class PLALYRLine : public PLALayer
{
  PLAVec2 _vector = kPLAVec2None;
  PLAColor _color = kPLAColorNone;

public:
  static PLALYRLine *Create(const PLALine &aLine);

  PLALYRLine() = delete;
  PLALYRLine(const PLAVec3 &aOffset, const PLAVec2 &aVector,
             const PLAColor &aColor) :
    PLALayer(PLALayerType::Line, aOffset, "== PLALYRLine =="),
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

class PLALYRRect : public PLALayer
{
  PLAVec2 _vector = kPLAVec2None;
  PLAColor _fillColor = kPLAColorWhite;
  PLAColor _strokeColor = kPLAColorNone;

public:
  static PLALYRRect *Create(const PLARect &aRect);

  PLALYRRect() = delete;
  PLALYRRect(const PLAVec3 &aOffset, const PLAVec2 &aVector,
             const PLAColor &aFillColor) :
    PLALayer(PLALayerType::Rect, aOffset, "== PLALYRRect =="),
    _vector(aVector), _fillColor(aFillColor), _strokeColor(kPLAColorNone) {};
  PLALYRRect(const PLAVec3 &aOffset, const PLAVec2 &aVector,
             const PLAColor &aFillColor, const PLAColor &aStrokeColor) :
    PLALayer(PLALayerType::Rect, aOffset, "== PLALYRRect =="),
    _vector(aVector), _fillColor(aFillColor), _strokeColor(aStrokeColor) {};
  virtual ~PLALYRRect() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  PLARect GetRect() const;

  const PLAColor &GetStrokeColor() const { return _strokeColor; };
  void SetStrokeColor(const PLAColor &aColor) { _strokeColor = aColor; };
  const PLAColor &GetFillColor() const { return _fillColor; };
  void SetFillColor(const PLAColor &aColor) { _fillColor = aColor; };
};

class PLALYRCircle : public PLALayer
{
  float _radius = 0;
  PLAColor _fillColor = kPLAColorWhite;
  PLAColor _strokeColor = kPLAColorNone;

public:
  static PLALYRCircle *Create(const PLACircle &aCircle);

  PLALYRCircle() = delete;
  PLALYRCircle(const PLAVec3 &aOffset, float aRadius,
               const PLAColor &aFillColor) :
    PLALayer(PLALayerType::Circle, aOffset, "== PLALYRCircle =="),
    _radius(aRadius), _fillColor(aFillColor), _strokeColor(kPLAColorNone) {};
  PLALYRCircle(const PLAVec3 &aOffset, float aRadius,
               const PLAColor &aFillColor, const PLAColor &aStrokeColor) :
    PLALayer(PLALayerType::Circle, aOffset, "== PLALYRCircle =="),
    _radius(aRadius), _fillColor(aFillColor), _strokeColor(aStrokeColor) {};
  virtual ~PLALYRCircle() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  float GetRadius() const { return _radius; };
  PLACircle GetCircle() const;

  const PLAColor &GetStrokeColor() const { return _strokeColor; };
  void SetStrokeColor(const PLAColor &aColor) { _strokeColor = aColor; };
  const PLAColor &GetFillColor() const { return _fillColor; };
  void SetFillColor(const PLAColor &aColor) { _fillColor = aColor; };
};

#endif // PLAIN_ENGINE_PLALAYER_HPP
