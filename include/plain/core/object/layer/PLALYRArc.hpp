// Copyright (c) 2024. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_PLALYRARC_HPP
#define PLAIN_PLALYRARC_HPP

#include "plain/core/object/layer/PLAOBJLayer.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"

class PLALYRArc : public PLAOBJLayer
{
  PLAFloat _radius = 0;
  PLAFloat _startAngle = 0;      // Start angle in radians
  PLAFloat _endAngle = M_PI;     // End angle in radians
  PLAColor _fillColor = kPLAColorWhite;
  PLAColor _strokeColor = kPLAColorNone;
  PLAFloat _strokeWidth = 2.0f;
  PLAOBJImageClip *_imageClip = nullptr;
  PLAOBJVideoClip *_videoClip = nullptr;

public:
  PLALYRArc(const PLAVec3f &aOffset, PLAFloat aRadius,
            PLAFloat aStartAngle, PLAFloat aEndAngle,
            const PLAColor &aFillColor, const PLAColor &aStrokeColor,
            const std::string &aImageName, const PLARect &aClip);

  static PLALYRArc *Create(PLAFloat aRadius,
                           PLAFloat aStartAngle, PLAFloat aEndAngle);
  static PLALYRArc *Create(PLAFloat aRadius,
                           PLAFloat aStartAngle, PLAFloat aEndAngle,
                           const PLAColor &aFillColor,
                           const PLAColor &aStrokeColor,
                           const std::string &aImage, const PLARect &aClip);

  PLALYRArc() = delete;
  virtual ~PLALYRArc() {};

  PLAVec3f GetSize() const override;
  void GetSize(PLAVec3f *aSize) const override;
  void SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot) override;

  void SetImageClip(PLAOBJImageClip *aImageClip) override;
  void SetVideoClip(PLAOBJVideoClip *aVideoClip) override;

  bool IsCollideWithPoint(const PLAPoint &aPoint) const override;
  bool IsCollideWithLine(const PLALine &aLine) const override;
  bool IsCollideWithRect(const PLARect &aRect) const override;
  bool IsCollideWithCircle(const PLACircle &aCircle) const override;

  PLAFloat GetRadius() const { return _radius; };
  PLAFloat GetStartAngle() const { return _startAngle; };
  PLAFloat GetEndAngle() const { return _endAngle; };
  PLAFloat GetAngleSpan() const { return _endAngle - _startAngle; };

  void SetRadius(PLAFloat aRadius) { _radius = aRadius; };
  void SetStartAngle(PLAFloat aAngle) { _startAngle = aAngle; };
  void SetEndAngle(PLAFloat aAngle) { _endAngle = aAngle; };
  void SetAngles(PLAFloat aStartAngle, PLAFloat aEndAngle)
  { _startAngle = aStartAngle; _endAngle = aEndAngle; };

  const PLAColor &GetStrokeColor() const { return _strokeColor; };
  void SetStrokeColor(const PLAColor &aColor) { _strokeColor = aColor; };
  const PLAColor &GetFillColor() const { return _fillColor; };
  void SetFillColor(const PLAColor &aColor) { _fillColor = aColor; };

  PLAFloat GetStrokeWidth() const { return _strokeWidth; };
  void SetStrokeWidth(PLAFloat aWidth) { _strokeWidth = aWidth; };

  const PLAOBJImageClip *GetImageClip() const { return _imageClip; };
};

#endif //PLAIN_PLALYRARC_HPP
