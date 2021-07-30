#ifndef PLAIN_PLALYRCIRCLE_HPP
#define PLAIN_PLALYRCIRCLE_HPP

#include "PLALayer.hpp"
#include "Type/PLAColor.hpp"

class PLALYRCircle : public PLALayer
{
  PLAFloat _radius = 0;
  PLAColor _fillColor = kPLAColorWhite;
  PLAColor _strokeColor = kPLAColorNone;
  PLAImageClip *_imageClip = nullptr;

protected:
  PLALYRCircle(const PLAVec3 &aOffset, PLAFloat aRadius,
               const PLAColor &aFillColor, const PLAColor &aStrokeColor,
               const std::string &aImageName, const PLARect &aClip) :
    PLALayer(PLALayerType::Circle, aOffset),//, "== PLALYRRect =="),
    _radius(aRadius), _fillColor(aFillColor), _strokeColor(aStrokeColor)
    {
      if (aImageName != kPLAStrUndefined) {
        _imageClip = PLAImageClip::Create(aImageName, aClip);
      }
    };

public:
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

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  PLAFloat GetRadius() const { return _radius; };
  PLACircle GetCircle() const;

  const PLAColor &GetStrokeColor() const { return _strokeColor; };
  void SetStrokeColor(const PLAColor &aColor) { _strokeColor = aColor; };
  const PLAColor &GetFillColor() const { return _fillColor; };
  void SetFillColor(const PLAColor &aColor) { _fillColor = aColor; };
  const PLAImageClip *GetImageClip() const { return _imageClip; };

  virtual void SetFillColor(const PLAColor &aColor) const;
  virtual void SetStrokeColor(const PLAColor &aColor) const;
};


#endif //PLAIN_PLALYRCIRCLE_HPP
