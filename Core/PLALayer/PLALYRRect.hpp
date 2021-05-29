#ifndef ANHR_PLALYRRECT_HPP
#define ANHR_PLALYRRECT_HPP


#include "PLALayer.hpp"

class PLALYRRect : public PLALayer
{
  PLAVec2 _vector = kPLAVec2None;
  PLAColor _fillColor = kPLAColorWhite;
  PLAColor _strokeColor = kPLAColorNone;
  PLAImageClip *_imageClip = nullptr;

protected:
  PLALYRRect(const PLAVec3 &aOffset, const PLAVec2 &aVector,
             const PLAColor &aFillColor, const PLAColor &aStrokeColor,
             const std::string &aImageName, const PLARect &aClip) :
    PLALayer(PLALayerType::Rect, aOffset),//, "== PLALYRRect =="),
    _vector(aVector), _fillColor(aFillColor)
  {
    if (aImageName != kGRACharUndefined) {
      _imageClip = PLAImageClip::Create(aImageName, aClip);
    }
  };

public:
  /*
  static PLALYRRect *Create(const PLARect &aRect);
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
                            const std::string &aImage,
                            const PLARect &aClip);

  PLALYRRect() = delete;
  virtual ~PLALYRRect() {};

  virtual PLAVec3 GetSize() const;
  virtual void GetSize(PLAVec3 *aSize) const;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot);

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const;
  virtual bool IsCollideWithLine(const PLALine &aLine) const;
  virtual bool IsCollideWithRect(const PLARect &aRect) const;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const;

  PLARect GetRect() const;

  const PLAColor &GetStrokeColor() const { return _strokeColor; };
  void SetStrokeColor(const PLAColor &aColor) { _strokeColor = aColor; };
  const PLAColor &GetFillColor() const { return _fillColor; };
  void SetFillColor(const PLAColor &aColor) { _fillColor = aColor; };
  const PLAImageClip *GetImageClip() const { return _imageClip; };
};


#endif //ANHR_PLALYRRECT_HPP
