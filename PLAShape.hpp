#ifndef PLAIN_PLASHAPE_HPP
#define PLAIN_PLASHAPE_HPP

#include "Plain.hpp"
#include "PLAShapeType.hpp"
#include "PLAStyle.hpp"

class PLAShape
{
  PLAShapeType _type = PLAShapeType::None;
  PLAStyle _style = PLAStyle();

public:
  PLAShape() = delete;
  PLAShape(PLAShapeType aType, const PLAStyle &aStyle);
  virtual ~PLAShape();

  PLAShapeType GetType() const { return _type; };
  const PLAStyle *GetStyle() const { return &_style; };
  virtual PLAVec3 GetSize() const = 0;
  virtual void GetSize(PLAVec3 *aSize) const = 0;
  virtual void SetSize(const PLAVec3 &aSize) = 0;
};

class PLAShapePoint : public PLAShape
{
public:
  PLAShapePoint(const PLAStyle &aStyle) :
  PLAShape(PLAShapeType::Point, aStyle) {};
  virtual ~PLAShapePoint() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize);
};

class PLAShapeLine : public PLAShape
{
  PLAVec2 _vector;

public:
  PLAShapeLine(const PLAVec2 &aVector, const PLAStyle &aStyle) :
  PLAShape(PLAShapeType::Line, aStyle), _vector(aVector) {};
  virtual ~PLAShapeLine() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize);
};

class PLAShapeRect : public PLAShape
{
  PLAVec2 _vector;

public:
  PLAShapeRect(const PLAVec2 &aVector, const PLAStyle &aStyle) :
  PLAShape(PLAShapeType::Rect, aStyle), _vector(aVector) {};
  virtual ~PLAShapeRect() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize);
};

class PLAShapeCircle : public PLAShape
{
  float _radius;

public:
  PLAShapeCircle(float aRadius, const PLAStyle &aStyle) :
  PLAShape(PLAShapeType::Circle, aStyle), _radius(aRadius) {};
  virtual ~PLAShapeCircle() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize);

  float GetRadius() const { return _radius; };
};

#endif // PLAIN_PLASHAPE_HPP
