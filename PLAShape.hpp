#ifndef PLAIN_PLASHAPE_HPP
#define PLAIN_PLASHAPE_HPP

#include "PLAObject.hpp"
#include "PLAShapeType.hpp"
#include "PLAStyle.hpp"

class PLAShape : public PLAObject
{
  PLAShapeType _type = PLAShapeType::None;
  PLAStyle _style = PLAStyle();

public:
  static PLAShape *Create(const PLAShape &aShape);

  PLAShape() = delete;
  PLAShape(PLAShapeType aType, const PLAStyle &aStyle);
  virtual ~PLAShape();

  PLAShapeType GetType() const { return _type; };
  const PLAStyle *GetStyle() const { return &_style; };
  virtual PLAVec3 GetSize() const = 0;
  virtual void GetSize(PLAVec3 *aSize) const = 0;
  virtual void SetSize(const PLAVec3 &aSize) = 0;
};

class PLASHPPoint : public PLAShape
{
public:
  PLASHPPoint(const PLAStyle &aStyle) :
  PLAShape(PLAShapeType::Point, aStyle) {};
  virtual ~PLASHPPoint() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize);
};

class PLASHPLine : public PLAShape
{
  PLAVec2 _vector;

public:
  PLASHPLine(const PLAVec2 &aVector, const PLAStyle &aStyle) :
  PLAShape(PLAShapeType::Line, aStyle), _vector(aVector) {};
  virtual ~PLASHPLine() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize);
};

class PLASHPRect : public PLAShape
{
  PLAVec2 _vector;

public:
  PLASHPRect(const PLAVec2 &aVector, const PLAStyle &aStyle) :
  PLAShape(PLAShapeType::Rect, aStyle), _vector(aVector) {};
  virtual ~PLASHPRect() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize);
};

class PLASHPCircle : public PLAShape
{
  float _radius;

public:
  PLASHPCircle(float aRadius, const PLAStyle &aStyle) :
  PLAShape(PLAShapeType::Circle, aStyle), _radius(aRadius) {};
  virtual ~PLASHPCircle() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize);

  float GetRadius() const { return _radius; };
};

#endif // PLAIN_PLASHAPE_HPP
