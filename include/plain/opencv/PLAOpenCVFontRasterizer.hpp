// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAOPENCVFONTRASTERIZER_HPP
#define PLAIN_ENGINE_PLAOPENCVFONTRASTERIZER_HPP

#include "plain/core/object/font/PLAOBJFontRasterizer.hpp"

class PLAOpenCVFontRasterizer : public PLAOBJFontRasterizer
{
  int _fontFace = cv::FONT_HERSHEY_SIMPLEX;
  int _thickness = 2;

protected:
  PLAOpenCVFontRasterizer(const PLAString &aName);

public:
  static PLAOpenCVFontRasterizer *Create(const PLAString &aName = "OpenCVFontRasterizer");

  virtual ~PLAOpenCVFontRasterizer();

  bool Initialize() override;
  cv::Mat Rasterize(const PLAString &aText, PLAFloat aFontSize,
                    const PLAColor &aColor) override;
  PLAVec2f GetTextSize(const PLAString &aText, PLAFloat aFontSize) override;

  void SetFontFace(int aFontFace) { _fontFace = aFontFace; }
  void SetThickness(int aThickness) { _thickness = aThickness; }
};

#endif // PLAIN_ENGINE_PLAOPENCVFONTRASTERIZER_HPP
