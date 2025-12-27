// Copyright (c) 2024. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_PLALYRARC_HPP
#define PLAIN_PLALYRARC_HPP

#include "plain/core/object/layer/PLAOBJLayer.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"
#include "plain/core/primitive/PLAPRMStroke.hpp"

class PLALYRArc : public PLAOBJLayer
{
  PLAFloat _radius = 0;
  PLAFloat _startAngle = 0;      // Start angle in radians
  PLAFloat _endAngle = M_PI;     // End angle in radians
  PLAColor _fillColor = kPLAColorWhite;
  PLAStroke _stroke;
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

  const PLAStroke &GetStroke() const { return _stroke; };
  void SetStroke(const PLAStroke &aStroke) { _stroke = aStroke; };
  const PLAColor &GetStrokeColor() const { return _stroke.color; };
  void SetStrokeColor(const PLAColor &aColor) { _stroke.color = aColor; };
  PLAFloat GetStrokeWidth() const { return _stroke.width; };
  void SetStrokeWidth(PLAFloat aWidth) { _stroke.width = aWidth; };
  PLAStrokeJoinType GetStrokeJoin() const { return _stroke.join; };
  void SetStrokeJoin(PLAStrokeJoinType aJoin) { _stroke.join = aJoin; };
  PLAStrokeAlignType GetStrokeAlign() const { return _stroke.align; };
  void SetStrokeAlign(PLAStrokeAlignType aAlign) { _stroke.align = aAlign; };
  const PLAColor &GetFillColor() const { return _fillColor; };
  void SetFillColor(const PLAColor &aColor) { _fillColor = aColor; };

  const PLAOBJImageClip *GetImageClip() const { return _imageClip; };
};

#endif //PLAIN_PLALYRARC_HPP
