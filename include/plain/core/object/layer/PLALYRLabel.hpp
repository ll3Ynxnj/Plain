// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_PLALYRLABEL_HPP
#define PLAIN_PLALYRLABEL_HPP

#include "plain/core/object/layer/PLAOBJLayer.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"
#include "plain/core/primitive/PLAPRMRect.hpp"
#include "plain/core/object/font/PLAOBJFontRasterizer.hpp"
#include "plain/core/PLATextAlignment.hpp"

class PLAOBJImage;

class PLALYRLabel : public PLAOBJLayer
{
  PLAString _text;
  PLAFloat _fontSize = 24.0f;
  PLAFloat _rasterScale = 1.0f;
  PLAColor _textColor = kPLAColorWhite;
  PLAColor _fillColor = kPLAColorNone;
  PLAVec2f _size = kPLAVec2fNone;
  PLATextAlignment _alignment = PLATextAlignment::Left;
  PLAFloat _alignmentWidth = 0.0f;

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

  PLAFloat GetRasterScale() const { return _rasterScale; }
  void SetRasterScale(PLAFloat aScale);

  const PLAColor &GetTextColor() const { return _textColor; }
  void SetTextColor(const PLAColor &aColor);

  const PLAColor &GetFillColor() const { return _fillColor; }
  void SetFillColor(const PLAColor &aColor) { _fillColor = aColor; }

  PLATextAlignment GetAlignment() const { return _alignment; }
  void SetAlignment(PLATextAlignment aAlignment);

  PLAFloat GetAlignmentWidth() const { return _alignmentWidth; }
  void SetAlignmentWidth(PLAFloat aWidth);

  const PLAOBJImage *GetTextureImage() const { return _textureImage; }

  void Update();

private:
  void UpdateTexture();
};

#endif // PLAIN_PLALYRLABEL_HPP
