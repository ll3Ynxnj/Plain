// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_PLALYRLABEL_HPP
#define PLAIN_PLALYRLABEL_HPP

#include "plain/core/object/layer/PLAOBJLayer.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"
#include "plain/core/primitive/PLAPRMRect.hpp"
#include "plain/core/object/font/PLAOBJFontRasterizer.hpp"

class PLAOBJImage;

class PLALYRLabel : public PLAOBJLayer
{
  PLAString _text;
  PLAFloat _fontSize = 24.0f;
  PLAColor _textColor = kPLAColorWhite;
  PLAVec2f _size = kPLAVec2fNone;

  PLAOBJFontRasterizer *_rasterizer = nullptr;
  PLAOBJImage *_textureImage = nullptr;
  bool _needsUpdate = true;

public:
  static PLALYRLabel *Create(const PLAString &aText);
  static PLALYRLabel *Create(const PLAString &aText, PLAFloat aFontSize);
  static PLALYRLabel *Create(const PLAString &aText, PLAFloat aFontSize,
                             const PLAColor &aTextColor);

  PLALYRLabel(const PLAVec3f &aOffset, const PLAString &aText,
              PLAFloat aFontSize, const PLAColor &aTextColor);

  PLALYRLabel() = delete;

  virtual ~PLALYRLabel();

  virtual PLAVec3f GetSize() const override;
  virtual void GetSize(PLAVec3f *aSize) const override;
  virtual void SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot) override;

  virtual void SetImageClip(PLAOBJImageClip *aImageClip) override {}
  virtual void SetVideoClip(PLAOBJVideoClip *aVideoClip) override {}

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const override;
  virtual bool IsCollideWithLine(const PLALine &aLine) const override;
  virtual bool IsCollideWithRect(const PLARect &aRect) const override;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const override;

  PLARect GetRect() const;

  void SetFontRasterizer(PLAOBJFontRasterizer *aRasterizer);
  PLAOBJFontRasterizer *GetFontRasterizer() const { return _rasterizer; }

  const PLAString &GetText() const { return _text; }
  void SetText(const PLAString &aText);

  PLAFloat GetFontSize() const { return _fontSize; }
  void SetFontSize(PLAFloat aFontSize);

  const PLAColor &GetTextColor() const { return _textColor; }
  void SetTextColor(const PLAColor &aColor);

  const PLAOBJImage *GetTextureImage() const { return _textureImage; }

  void Update();

private:
  void UpdateTexture();
};

#endif // PLAIN_PLALYRLABEL_HPP
