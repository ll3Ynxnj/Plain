#ifndef PLAIN_PLALYRCIRCLE_HPP
#define PLAIN_PLALYRCIRCLE_HPP

#include "plain/core/object/layer/PLAOBJLayer.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"
#include "plain/core/primitive/PLAPRMStroke.hpp"

class PLALYRCircle : public PLAOBJLayer
{
  PLAFloat _radius = 0;
  PLAColor _fillColor = kPLAColorWhite;
  PLAStroke _stroke;
  PLAOBJImageClip *_imageClip = nullptr;
  PLAOBJVideoClip *_videoClip = nullptr;

public:
  PLALYRCircle(const PLAVec3f &aOffset, PLAFloat aRadius,
               const PLAColor &aFillColor, const PLAColor &aStrokeColor,
               const std::string &aImageName, const PLARect &aClip) :
    PLAOBJLayer(PLALayerType::Circle, aOffset),//, "== PLALYRRect =="),
    _radius(aRadius), _fillColor(aFillColor), _stroke(aStrokeColor, 2.0f)
    {
      if (aImageName != kPLAStrUndefined) {
        _imageClip = PLAOBJImageClip::Create(aImageName, aClip);
      }
    };

  PLALYRCircle(const PLACircle aCircle,
               const PLAColor &aFillColor, const PLAColor &aStrokeColor,
               const std::string &aImageName, const PLARect &aClip) :
    PLAOBJLayer(PLALayerType::Circle,
                PLAVec3f(aCircle.origin.x, aCircle.origin.y, 0)),//, "== PLALYRRect =="),
    _radius(aCircle.radius), _fillColor(aFillColor), _stroke(aStrokeColor, 2.0f)
  {
    if (aImageName != kPLAStrUndefined) {
      _imageClip = PLAOBJImageClip::Create(aImageName, aClip);
    }
  };

  static PLALYRCircle *Create(const PLACircle &aCircle);
  /*
  static PLALYRCircle *Create(const PLACircle &aCircle,
                              const PLAColor &aFillColor);
  static PLALYRCircle *Create(const PLACircle &aCircle,
                              const PLAColor &aFillColor,
                              const PLAColor &aStrokeColor);
  static PLALYRCircle *Create(const PLACircle &aCircle,
                              const std::string &aImage,
                              const PLARect &aClip);
  static PLALYRCircle *Create(const PLACircle &aCircle,
                              const PLAColor &aFillColor,
                              const std::string &aImage,
                              const PLARect &aClip);
  */
  static PLALYRCircle *Create(const PLACircle &aCircle,
                              const PLAColor &aFillColor,
                              const PLAColor &aStrokeColor,
                              const std::string &aImage,
                              const PLARect &aClip);

  PLALYRCircle() = delete;
  virtual ~PLALYRCircle() {};

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
  PLACircle GetCircle() const;

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

#endif //PLAIN_PLALYRCIRCLE_HPP
