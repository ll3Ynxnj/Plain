//
// Created by Kawai Kentaro on 2020/10/20.
//

#ifndef PLAIN_ENGINE_PLACOLLISION_HPP
#define PLAIN_ENGINE_PLACOLLISION_HPP

#include "PLACollisionType.hpp"
#include "PLALayer.hpp"

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
  virtual ~PLACollision();

  PLACollisionType GetCollisionType() const { return _type; };
  bool IsCollide(const PLACollision &aCollision) const;

  virtual bool IsCollideWithLayer(const PLALayer *aLayer) const = 0;
  //virtual bool IsCollideWithPixel(const PLAPixel &aPixel) const = 0;
};

class PLACOLLayer : public PLACollision
{
  PLALayer *_layer = nullptr;

public:
  explicit PLACOLLayer(PLALayer *aLayer);
  ~PLACOLLayer();

  const PLALayer *GetLayer() const { return _layer; }

  virtual bool IsCollideWithLayer(const PLALayer *aLayer) const;
  //virtual bool IsCollideWithPixel(const PLAPixel aPixel) const;
};

#endif //PLAIN_ENGINE_PLACOLLISION_HPP
