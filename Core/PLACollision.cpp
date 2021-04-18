#include "PLACollision.hpp"

bool PLACollision::IsCollideWithPointAndPoint(const PLAPoint &aPoint0,
                                              const PLAPoint &aPoint1)
{
  // A point cannot collide with point. This code was written to show that.
  return false;
}

bool PLACollision::IsCollideWithPointAndLine(const PLAPoint &aPoint,
                                             const PLALine &aLine)
{
  return false;
}

bool PLACollision::IsCollideWithPointAndRect(const PLAPoint &aPoint,
                                             const PLARect &aRect)
{
  PLA_PRINT("--\n");
  PLA_TRACE("%.2f <  %.2f : %d",
            aPoint.x, aRect.pos.x, aPoint.x < aRect.pos.x);
  if (aPoint.x < aRect.pos.x) { return false; }
  PLA_TRACE("%.2f <  %.2f : %d",
            aPoint.y, aRect.pos.x, aPoint.y < aRect.pos.y);
  if (aPoint.y < aRect.pos.y) { return false; }
  PLA_TRACE("%.2f <= %.2f : %d",
            aRect.pos.x + aRect.size.x, aPoint.x,
            aRect.pos.x + aRect.size.x <= aPoint.x);
  if (aRect.pos.x + aRect.size.x <= aPoint.x) { return false; }
  PLA_TRACE("%.2f <= %.2f : %d",
            aRect.pos.y + aRect.size.y, aPoint.y,
            aRect.pos.y + aRect.size.y <= aPoint.y);
  if (aRect.pos.y + aRect.size.y <= aPoint.y) { return false; }
  PLA_TRACE("return true");
  return true;
}

bool PLACollision::IsCollideWithPointAndCircle(const PLAPoint &aPoint,
                                               const PLACircle &aCircle)
{
  PLA_PRINT("--\n");
  PLA_PRINT("%.2f > %.2f",
            aCircle.radius,
            abs(hypot(aCircle.origin.x - aPoint.x, aCircle.origin.y - aPoint.y)));
  PLA_PRINT(" : %d\n", aCircle.radius >
            abs(hypot(aCircle.origin.x - aPoint.x, aCircle.origin.y - aPoint.y)));
  PLA_PRINT("aPoint : x : %.2f, y : %.2f\n", aPoint.x, aPoint.y);
  PLA_PRINT("aCircle : origin.x : %.2f, origin.y : %.2f\n",
            aCircle.origin.x, aCircle.origin.y);
  return
  aCircle.radius >
  abs(hypot(aCircle.origin.x - aPoint.x, aCircle.origin.y - aPoint.y));
}

bool PLACollision::IsCollideWithLineAndLine(const PLALine &aLine0,
                                            const PLALine &aLine1)
{
  return false;
}

bool PLACollision::IsCollideWithLineAndRect(const PLALine &aLine,
                                            const PLARect &aRect)
{
  return false;
}

bool PLACollision::IsCollideWithLineAndCircle(const PLALine &aLine,
                                              const PLACircle &aCircle)
{
  return false;
}

bool PLACollision::IsCollideWithRectAndRect(const PLARect &aRect0,
                                            const PLARect &aRect1)
{
  if ((aRect1.pos.x + aRect1.size.x) <= aRect0.pos.x) { return false; }
  if ((aRect1.pos.y + aRect1.size.y) <= aRect0.pos.y) { return false; }
  if ((aRect0.pos.x + aRect0.size.x) <= aRect1.pos.x) { return false; }
  if ((aRect0.pos.y + aRect0.size.y) <= aRect1.pos.y) { return false; }
  return true;
}

bool PLACollision::IsCollideWithRectAndCircle(const PLARect &aRect,
                                              const PLACircle &aCircle)
{
  PLARect combinedRect = aRect;
  combinedRect.pos.x -= aCircle.radius;
  combinedRect.pos.y -= aCircle.radius;
  combinedRect.size.x += aCircle.radius * 2;
  combinedRect.size.y += aCircle.radius * 2;
  if (!PLACollision::IsCollideWithPointAndRect(aCircle.origin, combinedRect))
  { return false; }

  if (PLACollision::IsCollideWithPointAndRect(aCircle.origin, aRect))
  { return true; }

  PLAPoint nearestPoint = kPLAPointNone;
  nearestPoint.x =
  abs(aCircle.origin.x - aRect.pos.x) <=
  abs(aCircle.origin.x - (aRect.pos.x + aRect.size.x)) ?
  aRect.pos.x : aRect.pos.x + aRect.size.x;
  nearestPoint.y =
  abs(aCircle.origin.y - aRect.pos.y) <=
  abs(aCircle.origin.y - (aRect.pos.y + aRect.size.y)) ?
  aRect.pos.y : aRect.pos.y + aRect.size.y;
  return PLACollision::IsCollideWithPointAndCircle(nearestPoint, aCircle);
}

bool PLACollision::IsCollideWithCircleAndCircle(const PLACircle &aCircle0,
                                                const PLACircle &aCircle1)
{
  return
  aCircle0.radius + aCircle1.radius >
  abs(hypot(aCircle1.origin.x - aCircle0.origin.x,
            aCircle1.origin.y - aCircle0.origin.y));
}

PLACollision::PLACollision(PLACollisionType aType) :
_type(aType)
{

}

PLACollision::~PLACollision()
{

}

PLACOLLayer::PLACOLLayer(PLALayer *aLayer) :
PLACollision(PLACollisionType::Layer),
_layer(aLayer)
{

}

PLACOLLayer::~PLACOLLayer()
{

}

bool PLACollision::IsCollide(const PLACollision &aCollision) const
{
  switch (aCollision.GetCollisionType())
  {
    case PLACollisionType::Layer :
      return this->IsCollideWithLayer
      (static_cast<const PLACOLLayer &>(aCollision).GetLayer());
    default :
      return false;
  }
}

bool PLACOLLayer::IsCollideWithLayer(const PLALayer *aLayer) const
{
  switch (aLayer->GetLayerType())
  {
    case PLALayerType::Point :
      return _layer->IsCollideWithPoint
      (static_cast<const PLALYRPoint *>(aLayer)->GetPoint());
      break;
    case PLALayerType::Line :
      return false;
      break;
    case PLALayerType::Rect :
      return _layer->IsCollideWithRect
      (static_cast<const PLALYRRect *>(aLayer)->GetRect());
      break;
    case PLALayerType::Circle :
      return _layer->IsCollideWithCircle
      (static_cast<const PLALYRCircle *>(aLayer)->GetCircle());
      break;
    default :
      return false;
      break;
  }
}
