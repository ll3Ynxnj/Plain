#ifndef PLAIN_PLALYRCIRCLE_HPP
#define PLAIN_PLALYRCIRCLE_HPP

#include "plain/core/object/layer/PLAOBJLayer.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"

class PLALYRCircle : public PLAOBJLayer
{
  PLAFloat _radius = 0;
  PLAColor _fillColor = kPLAColorWhite;
  PLAColor _strokeColor = kPLAColorNone;
  PLAOBJImageClip *_imageClip = nullptr;
  PLAOBJVideoClip *_videoClip = nullptr;

public:
  PLALYRCircle(const PLAVec3f &aOffset, PLAFloat aRadius,
               const PLAColor &aFillColor, const PLAColor &aStrokeColor,
               const std::string &aImageName, const PLARect &aClip) :
    PLAOBJLayer(PLALayerType::Circle, aOffset),//, "== PLALYRRect =="),
    _radius(aRadius), _fillColor(aFillColor), _strokeColor(aStrokeColor)
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
    _radius(aCircle.radius), _fillColor(aFillColor), _strokeColor(aStrokeColor)
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

  const PLAColor &GetStrokeColor() const { return _strokeColor; };
  void SetStrokeColor(const PLAColor &aColor) { _strokeColor = aColor; };
  const PLAColor &GetFillColor() const { return _fillColor; };
  void SetFillColor(const PLAColor &aColor) { _fillColor = aColor; };
  const PLAOBJImageClip *GetImageClip() const { return _imageClip; };

  virtual void SetFillColor(const PLAColor &aColor) const;
  virtual void SetStrokeColor(const PLAColor &aColor) const;
};

#endif //PLAIN_PLALYRCIRCLE_HPP
