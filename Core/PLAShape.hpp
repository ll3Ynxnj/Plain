#ifndef PLAIN_ENGINE_PLASHAPE_HPP
#define PLAIN_ENGINE_PLASHAPE_HPP

#include "PLAObject.hpp"
#include "PLAShapeType.hpp"
#include "PLAStyle.hpp"

class PLAShape : public PLAObject
{
  PLAShapeType _type = PLAShapeType::None;
  PLAVec3 _offset = kPLAVec3None;

public:
  static PLAShape *Create(const PLAShape &aShape);

  PLAShape() = delete;
  PLAShape(PLAShapeType aType, const PLAVec3 &aOffset, const std::string &aName);
  virtual ~PLAShape();

  PLAShapeType GetShapeType() const { return _type; };
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

class PLASHPPoint : public PLAShape
{
public:
  static PLASHPPoint *Create(const PLAPoint &aPoint);

  PLASHPPoint() = delete;
  PLASHPPoint(const PLAVec3 &aOffset) :
  PLAShape(PLAShapeType::Point, aOffset, "== PLASHPPoint ==") {};//, aStyle) {};
  virtual ~PLASHPPoint() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  PLAPoint GetPoint() const;

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;
};

class PLASHPLine : public PLAShape
{
  PLAVec2 _vector;

public:
  static PLASHPLine *Create(const PLALine &aLine);

  PLASHPLine() = delete;
  PLASHPLine(const PLAVec3 &aOffset, const PLAVec2 &aVector) :
  PLAShape(PLAShapeType::Line, aOffset, "== PLASHPLine =="), _vector(aVector) {};
  virtual ~PLASHPLine() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  PLALine GetLine() const;
};

class PLASHPRect : public PLAShape
{
  PLAVec2 _vector = kPLAVec2None;

public:
  static PLASHPRect *Create(const PLARect &aRect);

  PLASHPRect() = delete;
  PLASHPRect(const PLAVec3 &aOffset, const PLAVec2 &aVector) :
  PLAShape(PLAShapeType::Rect, aOffset, "== PLASHPRect =="), _vector(aVector) {};
  virtual ~PLASHPRect() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  PLARect GetRect() const;
};

class PLASHPCircle : public PLAShape
{
  float _radius = 0;

public:
  static PLASHPCircle *Create(const PLACircle &aCircle);

  PLASHPCircle() = delete;
  PLASHPCircle(const PLAVec3 &aOffset, float aRadius) :
  PLAShape(PLAShapeType::Circle, aOffset, "== PLASHPCircle =="), _radius(aRadius) {};
  virtual ~PLASHPCircle() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  float GetRadius() const { return _radius; };
  PLACircle GetCircle() const;
};

#endif // PLAIN_ENGINE_PLASHAPE_HPP
