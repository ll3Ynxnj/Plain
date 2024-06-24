#ifndef PLAIN_PLALYRRECT_HPP
#define PLAIN_PLALYRRECT_HPP

#include "plain/core/object/layer/PLAOBJLayer.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"

class PLALYRRect : public PLAOBJLayer
{
  PLAVec2f _vector = kPLAVec2fNone;
  PLAColor _fillColor = kPLAColorWhite;
  PLAColor _strokeColor = kPLAColorNone;
  PLAOBJImageClip *_imageClip = nullptr; // PLAOBJLayerが持つべきでは？
  //PLAOBJVideoClip *_videoClip = nullptr; // PLAOBJLayerが持つべきでは？

public:
  PLALYRRect(const PLAVec3f &aOffset, const PLAVec2f &aVector,
             const PLAColor &aFillColor, const PLAColor &aStrokeColor,
             const std::string &aImageName, const PLARect &aClip) :
    PLAOBJLayer(PLALayerType::Rect, aOffset),//, "== PLALYRRect =="),
    _vector(aVector), _fillColor(aFillColor), _strokeColor(aStrokeColor)
  {
    if (aImageName != kPLAStrUndefined) {
      _imageClip = PLAOBJImageClip::Create(aImageName, aClip);
    }
  };

  PLALYRRect(const PLARect &aRect,
             const PLAColor &aFillColor, const PLAColor &aStrokeColor,
             const std::string &aImageName, const PLARect &aClip) :
    PLAOBJLayer(PLALayerType::Rect, PLAVec3f(aRect.pos.x, aRect.pos.y, 0)),
    _vector(aRect.size), _fillColor(aFillColor),
    _strokeColor(aStrokeColor)
  {
    if (aImageName != kPLAStrUndefined) {
      _imageClip = PLAOBJImageClip::Create(aImageName, aClip);
    }
  }

  static PLALYRRect *Create(const PLARect &aRect);
  /*
  static PLALYRRect *Create(const PLARect &aRect,
                            const PLAColor &aFillColor);
  static PLALYRRect *Create(const PLARect &aRect,
                            const PLAColor &aFillColor,
                            const PLAColor &aStrokeColor);
  static PLALYRRect *Create(const PLARect &aRect,
                            const std::string &aImage,
                            const PLARect &aClip);
  static PLALYRRect *Create(const PLARect &aRect,
                            const PLAColor &aFillColor,
                            const std::string &aImage,
                            const PLARect &aClip);
  */
  static PLALYRRect *Create(const PLARect &aRect,
                            const PLAColor &aFillColor,
                            const PLAColor &aStrokeColor,
                            const PLAString &aImage,
                            const PLARect &aClip);

  PLALYRRect() = delete;



  virtual ~PLALYRRect() {};

  virtual PLAVec3f GetSize() const;
  virtual void GetSize(PLAVec3f *aSize) const;
  virtual void SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot);

  virtual void SetImageClip(PLAOBJImageClip *aImageClip);
  virtual void SetVideoClip(PLAOBJVideoClip *aVideoClip);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  PLARect GetRect() const;

  const PLAColor &GetStrokeColor() const { return _strokeColor; };
  void SetStrokeColor(const PLAColor &aColor) { _strokeColor = aColor; };
  const PLAColor &GetFillColor() const { return _fillColor; };
  void SetFillColor(const PLAColor &aColor) { _fillColor = aColor; };
  const PLAOBJImageClip *GetImageClip() const { return _imageClip; };
};

#endif //PLAIN_PLALYRRECT_HPP
