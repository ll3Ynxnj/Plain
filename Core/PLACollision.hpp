//
// Created by Kawai Kentaro on 2020/10/20.
//

#ifndef PLAIN_ENGINE_PLACOLLISION_HPP
#define PLAIN_ENGINE_PLACOLLISION_HPP

#include "PLACollisionType.hpp"
#include "PLAShape.hpp"

class PLACollision
{
  PLACollisionType _type = PLACollisionType::None;

public:
  static bool IsCollideWithPointAndPoint(const PLAPoint &aPoint0,
                                         const PLAPoint &aPoint1);
  static bool IsCollideWithPointAndLine(const PLAPoint &aPoint,
                                        const PLALine &aLine);
  static bool IsCollideWithPointAndRect(const PLAPoint &aPoint,
                                        const PLARect &aRect);
  static bool IsCollideWithPointAndCircle(const PLAPoint &aPoint,
                                          const PLACircle &aCircle);
  static bool IsCollideWithLineAndLine(const PLALine &aLine0,
                                       const PLALine &aLine1);
  static bool IsCollideWithLineAndRect(const PLALine &aLine,
                                       const PLARect &aRect);
  static bool IsCollideWithLineAndCircle(const PLALine &aLine,
                                         const PLACircle &aCircle);
  static bool IsCollideWithRectAndRect(const PLARect &aRect0,
                                       const PLARect &aRect1);
  static bool IsCollideWithRectAndCircle(const PLARect &aRect,
                                         const PLACircle &aCircle);
  static bool IsCollideWithCircleAndCircle(const PLACircle &aCircle0,
                                           const PLACircle &aCircle1);

  explicit PLACollision(PLACollisionType aType);
  ~PLACollision();

  PLACollisionType GetCollisionType() const { return _type; };
  bool IsCollide(const PLACollision &aCollision) const;

  virtual bool IsCollideWithShape(const PLAShape *aShape) const = 0;
  //virtual bool IsCollideWithPixel(const PLAPixel &aPixel) const = 0;
};

class PLACOLShape : public PLACollision
{
  PLAShape *_shape = nullptr;

public:
  explicit PLACOLShape(PLAShape *aShape);
  ~PLACOLShape();

  const PLAShape *GetShape() const { return _shape; }

  virtual bool IsCollideWithShape(const PLAShape *aShape) const;
  //virtual bool IsCollideWithPixel(const PLAPixel aPixel) const;
};

#endif //PLAIN_ENGINE_PLACOLLISION_HPP
