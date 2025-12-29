// Copyright (c) 2024. CLAYWORK Inc. All rights reserved.

#include <cmath>
#include "plain/core/object/layer/PLALYRArc.hpp"
#include "plain/core/library/PLALIBCollision.hpp"

PLALYRArc::PLALYRArc(const PLAVec3f &aOffset, PLAFloat aRadius,
                     PLAFloat aStartAngle, PLAFloat aEndAngle,
                     const PLAColor &aFillColor, const PLAColor &aStrokeColor,
                     const std::string &aImageName, const PLARect &aClip) :
  PLAOBJLayer(PLALayerType::Arc, aOffset),
  _radius(aRadius), _startAngle(aStartAngle), _endAngle(aEndAngle),
  _fillColor(aFillColor), _stroke(aStrokeColor, 2.0f)
{
  if (aImageName != kPLAStrUndefined) {
    _imageClip = PLAOBJImageClip::Create(aImageName, aClip);
  }
}

PLALYRArc *PLALYRArc::Create(PLAFloat aRadius,
                             PLAFloat aStartAngle, PLAFloat aEndAngle)
{
  PLALYRArc *layer =
    new PLALYRArc(PLAVec3f(-aRadius, -aRadius, 0),
                  aRadius, aStartAngle, aEndAngle,
                  kPLAColorWhite, kPLAColorNone,
                  kPLAStrUndefined, kPLARectNone);
  layer->Bind();
  return layer;
}

PLALYRArc *PLALYRArc::Create(PLAFloat aRadius,
                             PLAFloat aStartAngle, PLAFloat aEndAngle,
                             const PLAColor &aFillColor,
                             const PLAColor &aStrokeColor,
                             const std::string &aImage, const PLARect &aClip)
{
  PLALYRArc *layer =
    new PLALYRArc(PLAVec3f(-aRadius, -aRadius, 0),
                  aRadius, aStartAngle, aEndAngle,
                  aFillColor, aStrokeColor, aImage, aClip);
  layer->Bind();
  return layer;
}

PLAVec3f PLALYRArc::GetSize() const
{
  return { _radius * 2, _radius * 2, 0 };
}

void PLALYRArc::GetSize(PLAVec3f *aSize) const
{
  aSize->x = _radius * 2;
  aSize->y = _radius * 2;
  aSize->z = 0;
}

void PLALYRArc::SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot)
{
  _radius = aSize.x > aSize.y ? aSize.x * 0.5f : aSize.y * 0.5f;
  this->SetOffset(PLAVec3f((aPivot.x - 0.5) * _radius * 2,
                           (aPivot.y - 0.5) * _radius * 2,
                           0));
}

void PLALYRArc::SetImageClip(PLAOBJImageClip *aImageClip)
{
  _imageClip = aImageClip;
}

void PLALYRArc::SetVideoClip(PLAOBJVideoClip *aVideoClip)
{
  _videoClip = aVideoClip;
}

bool PLALYRArc::IsCollideWithPoint(const PLAPoint &aPoint) const
{
  // Check if point is within the arc sector
  PLAVec3f offset = this->GetOffset();
  PLAPoint center = { offset.x + _radius, offset.y + _radius };

  // Check distance from center
  PLAFloat dx = aPoint.x - center.x;
  PLAFloat dy = aPoint.y - center.y;
  PLAFloat distSq = dx * dx + dy * dy;

  if (distSq > _radius * _radius) {
    return false;
  }

  // Check if angle is within arc range
  PLAFloat angle = std::atan2(dy, dx);
  if (angle < 0) angle += M_PI * 2;

  PLAFloat start = _startAngle;
  PLAFloat end = _endAngle;

  // Normalize angles
  while (start < 0) start += M_PI * 2;
  while (end < 0) end += M_PI * 2;

  if (start <= end) {
    return angle >= start && angle <= end;
  } else {
    // Arc wraps around 0
    return angle >= start || angle <= end;
  }
}

bool PLALYRArc::IsCollideWithLine(const PLALine &aLine) const
{
  // Simplified: check if either endpoint is inside the arc
  PLAPoint p0 = { aLine.p0.x, aLine.p0.y };
  PLAPoint p1 = { aLine.p1.x, aLine.p1.y };
  return IsCollideWithPoint(p0) || IsCollideWithPoint(p1);
}

bool PLALYRArc::IsCollideWithRect(const PLARect &aRect) const
{
  // Simplified: check if any corner is inside the arc
  PLAPoint corners[4] = {
    { aRect.pos.x, aRect.pos.y },
    { aRect.pos.x + aRect.size.x, aRect.pos.y },
    { aRect.pos.x, aRect.pos.y + aRect.size.y },
    { aRect.pos.x + aRect.size.x, aRect.pos.y + aRect.size.y }
  };

  for (int i = 0; i < 4; i++) {
    if (IsCollideWithPoint(corners[i])) {
      return true;
    }
  }
  return false;
}

bool PLALYRArc::IsCollideWithCircle(const PLACircle &aCircle) const
{
  // Check if circle center is within arc + circle radius
  PLAVec3f offset = this->GetOffset();
  PLAPoint center = { offset.x + _radius, offset.y + _radius };

  PLAFloat dx = aCircle.origin.x - center.x;
  PLAFloat dy = aCircle.origin.y - center.y;
  PLAFloat dist = std::sqrt(dx * dx + dy * dy);

  return dist <= _radius + aCircle.radius;
}
