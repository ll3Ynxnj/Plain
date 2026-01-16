// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAFREETYPEFONTRASTERIZER_HPP
#define PLAIN_ENGINE_PLAFREETYPEFONTRASTERIZER_HPP

#include "plain/core/object/font/PLAOBJFontRasterizer.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>
#include <cstdint>

class PLAFreeTypeFontRasterizer : public PLAOBJFontRasterizer
{
  FT_Library _library = nullptr;
  FT_Face _face = nullptr;
  PLAString _fontPath;
  FT_Long _faceIndex = 0;

protected:
  PLAFreeTypeFontRasterizer(const PLAString &aName);

public:
  static PLAFreeTypeFontRasterizer *Create(const PLAString &aName = "FreeTypeFontRasterizer");
  static PLAFreeTypeFontRasterizer *CreateWithFontPath(const PLAString &aFontPath,
                                                        const PLAString &aName);
  static PLAFreeTypeFontRasterizer *CreateWithFontPathAndFaceIndex(
    const PLAString &aFontPath, FT_Long aFaceIndex, const PLAString &aName);

  virtual ~PLAFreeTypeFontRasterizer();

  bool Initialize() override;
  cv::Mat Rasterize(const PLAString &aText, PLAFloat aFontSize,
                    const PLAColor &aColor) override;
  PLAVec2f GetTextSize(const PLAString &aText, PLAFloat aFontSize) override;
  PLAFontMetrics GetMetrics(PLAFloat aFontSize) override;

  void SetFontPath(const PLAString &aPath);
  void SetFontPathAndFaceIndex(const PLAString &aPath, FT_Long aFaceIndex);
  const PLAString &GetFontPath() const { return _fontPath; }

private:
  static PLAString FindSystemFont();
  static bool ResolveFontNameToPathAndIndex(const PLAString &aFontName,
                                            PLAString &outPath, FT_Long &outFaceIndex);
  static std::vector<uint32_t> DecodeUTF8(const PLAString &aText);
  void Cleanup();
};

#endif // PLAIN_ENGINE_PLAFREETYPEFONTRASTERIZER_HPP
