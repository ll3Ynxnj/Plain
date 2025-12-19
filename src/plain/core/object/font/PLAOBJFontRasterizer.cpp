// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/core/object/font/PLAOBJFontRasterizer.hpp"
#include "plain/opencv/PLAOpenCVFontRasterizer.hpp"
#include "plain/core/object/PLAOBJError.hpp"

PLAOBJFontRasterizer *PLAOBJFontRasterizer::Create(PLAFontRasterizerType aType)
{
  switch (aType)
  {
    case PLAFontRasterizerType::OpenCV:
      return PLAOpenCVFontRasterizer::Create();
    case PLAFontRasterizerType::FreeType:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Font rasterizer type not yet implemented.");
      return nullptr;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Unexpected font rasterizer type detected.");
      return nullptr;
  }
}

PLAOBJFontRasterizer::PLAOBJFontRasterizer() :
  PLAObject(PLAObjectType::FontRasterizer, "== PLAOBJFontRasterizer ==")
{
}

PLAOBJFontRasterizer::~PLAOBJFontRasterizer()
{
}
