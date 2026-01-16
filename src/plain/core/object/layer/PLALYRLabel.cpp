// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/core/object/layer/PLALYRLabel.hpp"
#include "plain/core/object/PLAOBJImage.hpp"
#include "plain/core/PLAFontRasterizerType.hpp"
#include "plain/core/library/PLALIBCollision.hpp"

static const PLAString kDefaultFontRasterizerName = "DefaultFontRasterizer";

PLALYRLabel *PLALYRLabel::Create(const PLAString &aText)
{
  return Create(aText, 24.0f, kPLAColorWhite);
}

PLALYRLabel *PLALYRLabel::Create(const PLAString &aText, PLAFloat aFontSize)
{
  return Create(aText, aFontSize, kPLAColorWhite);
}

PLALYRLabel *PLALYRLabel::Create(const PLAString &aText, PLAFloat aFontSize,
                                  const PLAColor &aTextColor)
{
  PLALYRLabel *label = new PLALYRLabel(kPLAVec3fNone, aText, aFontSize, aTextColor);

  // Use existing rasterizer if available, otherwise create new one
  PLAOBJFontRasterizer *rasterizer =
    PLAOBJFontRasterizer::Rasterizer(kDefaultFontRasterizerName);
  if (!rasterizer)
  {
    rasterizer = PLAOBJFontRasterizer::Create(
      PLAFontRasterizerType::FreeType, kDefaultFontRasterizerName);
  }
  label->SetFontRasterizer(rasterizer);

  return label;
}

PLALYRLabel::PLALYRLabel(const PLAVec3f &aOffset, const PLAString &aText,
                          PLAFloat aFontSize, const PLAColor &aTextColor) :
  PLAOBJLayer(PLALayerType::Label, aOffset),
  _text(aText),
  _fontSize(aFontSize),
  _textColor(aTextColor)
{
}

PLALYRLabel::~PLALYRLabel()
{
  if (_textureImage) {
    delete _textureImage;
    _textureImage = nullptr;
  }
}

PLAVec3f PLALYRLabel::GetSize() const
{
  return PLAVec3f(_size.x, _size.y, 0);
}

void PLALYRLabel::GetSize(PLAVec3f *aSize) const
{
  *aSize = PLAVec3f(_size.x, _size.y, 0);
}

void PLALYRLabel::SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot)
{
  _size = PLAVec2f(aSize.x, aSize.y);
}

void PLALYRLabel::SetFontRasterizer(PLAOBJFontRasterizer *aRasterizer)
{
  _rasterizer = aRasterizer;
  _needsUpdate = true;
}

void PLALYRLabel::SetFontRasterizerByName(const PLAString &aRasterizerName)
{
  PLAOBJFontRasterizer *rasterizer = PLAOBJFontRasterizer::Rasterizer(aRasterizerName);
  if (rasterizer)
  {
    SetFontRasterizer(rasterizer);
  }
}

void PLALYRLabel::SetText(const PLAString &aText)
{
  if (_text != aText) {
    _text = aText;
    _needsUpdate = true;
  }
}

void PLALYRLabel::SetFontSize(PLAFloat aFontSize)
{
  if (_fontSize != aFontSize) {
    _fontSize = aFontSize;
    _needsUpdate = true;
  }
}

void PLALYRLabel::SetRasterScale(PLAFloat aScale)
{
  if (_rasterScale != aScale) {
    _rasterScale = aScale;
    _needsUpdate = true;
  }
}

void PLALYRLabel::SetTextColor(const PLAColor &aColor)
{
  if (_textColor.r != aColor.r || _textColor.g != aColor.g ||
      _textColor.b != aColor.b || _textColor.a != aColor.a) {
    _textColor = aColor;
    _needsUpdate = true;
  }
}

void PLALYRLabel::SetAlignment(PLATextAlignment aAlignment)
{
  _alignment = aAlignment;
}

void PLALYRLabel::SetAlignmentWidth(PLAFloat aWidth)
{
  _alignmentWidth = aWidth;
}

void PLALYRLabel::SetAlignmentHeight(PLAFloat aHeight)
{
  _alignmentHeight = aHeight;
}

void PLALYRLabel::Update()
{
  if (_needsUpdate) {
    UpdateTexture();
    _needsUpdate = false;
  }
}

void PLALYRLabel::UpdateTexture()
{
  if (!_rasterizer || !_rasterizer->IsInitialized()) {
    return;
  }

  if (_text.empty()) {
    _size = PLAVec2f(0, 0);
    _fontMetrics = {0, 0, 0};
    return;
  }

  PLAFloat rasterSize = _fontSize * _rasterScale;
  cv::Mat textImage = _rasterizer->Rasterize(_text, rasterSize, _textColor);
  if (textImage.empty()) {
    return;
  }

  _size = PLAVec2f(textImage.cols / _rasterScale, textImage.rows / _rasterScale);

  // Get font metrics (scaled to logical size) for proper text positioning
  PLAFontMetrics rasterMetrics = _rasterizer->GetMetrics(rasterSize);
  _fontMetrics.ascender = rasterMetrics.ascender / _rasterScale;
  _fontMetrics.descender = rasterMetrics.descender / _rasterScale;
  _fontMetrics.lineHeight = rasterMetrics.lineHeight / _rasterScale;

  if (_textureImage) {
    delete _textureImage;
    _textureImage = nullptr;
  }

  static int labelCounter = 0;
  PLAString imageName = "label_texture_" + std::to_string(labelCounter++);
  _textureImage = PLAOBJImage::CreateFromMemory(
    imageName,
    textImage.data,
    PLAOBJImageSize(textImage.cols, textImage.rows),
    PLAImageType::Raw
  );
}

PLARect PLALYRLabel::GetRect() const
{
  PLAVec3f offset = this->GetOffset();
  return PLARect(PLAVec2f(offset.x, offset.y), _size);
}

bool PLALYRLabel::IsCollideWithPoint(const PLAPoint &aPoint) const
{
  return PLACollision::IsCollideWithPointAndRect(aPoint, this->GetRect());
}

bool PLALYRLabel::IsCollideWithLine(const PLALine &aLine) const
{
  return PLACollision::IsCollideWithLineAndRect(aLine, this->GetRect());
}

bool PLALYRLabel::IsCollideWithRect(const PLARect &aRect) const
{
  return PLACollision::IsCollideWithRectAndRect(this->GetRect(), aRect);
}

bool PLALYRLabel::IsCollideWithCircle(const PLACircle &aCircle) const
{
  return PLACollision::IsCollideWithRectAndCircle(this->GetRect(), aCircle);
}
