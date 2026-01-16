// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/freetype/PLAFreeTypeFontRasterizer.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include <cmath>
#include <fstream>
#include <filesystem>

PLAFreeTypeFontRasterizer *PLAFreeTypeFontRasterizer::Create(const PLAString &aName)
{
  PLAFreeTypeFontRasterizer *rasterizer = new PLAFreeTypeFontRasterizer(aName);
  if (!rasterizer->Initialize()) {
    delete rasterizer;
    return nullptr;
  }
  return rasterizer;
}

PLAFreeTypeFontRasterizer *PLAFreeTypeFontRasterizer::CreateWithFontPath(
  const PLAString &aFontPath, const PLAString &aName)
{
  PLAFreeTypeFontRasterizer *rasterizer = new PLAFreeTypeFontRasterizer(aName);
  rasterizer->SetFontPath(aFontPath);
  if (!rasterizer->Initialize()) {
    delete rasterizer;
    return nullptr;
  }
  rasterizer->Bind();  // Register with manager for name lookup
  return rasterizer;
}

PLAFreeTypeFontRasterizer::PLAFreeTypeFontRasterizer(const PLAString &aName) :
  PLAOBJFontRasterizer(aName)
{
}

PLAFreeTypeFontRasterizer::~PLAFreeTypeFontRasterizer()
{
  Cleanup();
}

std::vector<uint32_t> PLAFreeTypeFontRasterizer::DecodeUTF8(const PLAString &aText)
{
  std::vector<uint32_t> codepoints;
  const unsigned char *str = reinterpret_cast<const unsigned char *>(aText.c_str());
  size_t len = aText.length();
  size_t i = 0;

  while (i < len) {
    uint32_t codepoint;
    unsigned char c = str[i];

    if ((c & 0x80) == 0) {
      // 1-byte (ASCII): 0xxxxxxx
      codepoint = c;
      i += 1;
    } else if ((c & 0xE0) == 0xC0) {
      // 2-byte: 110xxxxx 10xxxxxx
      if (i + 1 >= len) break;
      codepoint = ((c & 0x1F) << 6) | (str[i + 1] & 0x3F);
      i += 2;
    } else if ((c & 0xF0) == 0xE0) {
      // 3-byte: 1110xxxx 10xxxxxx 10xxxxxx
      if (i + 2 >= len) break;
      codepoint = ((c & 0x0F) << 12) | ((str[i + 1] & 0x3F) << 6) | (str[i + 2] & 0x3F);
      i += 3;
    } else if ((c & 0xF8) == 0xF0) {
      // 4-byte: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
      if (i + 3 >= len) break;
      codepoint = ((c & 0x07) << 18) | ((str[i + 1] & 0x3F) << 12) |
                  ((str[i + 2] & 0x3F) << 6) | (str[i + 3] & 0x3F);
      i += 4;
    } else {
      // Invalid UTF-8 byte, skip
      i += 1;
      continue;
    }

    codepoints.push_back(codepoint);
  }

  return codepoints;
}

PLAString PLAFreeTypeFontRasterizer::FindSystemFont()
{
  // First, check CMake-configured default font path
#ifdef PLA_DEFAULT_FONT_PATH
  if (std::filesystem::exists(PLA_DEFAULT_FONT_PATH)) {
    return PLAString(PLA_DEFAULT_FONT_PATH);
  }
#endif

  // Second, search for specific fonts in Resources/fonts/ directory (iOS compatible)
  static const char* preferredFonts[] = {
    "Resources/fonts/HiraginoSans-W3.ttc",  // iOS Japanese font
    "Resources/fonts/HelveticaNeue.ttc",    // iOS English font
    nullptr
  };

  for (int i = 0; preferredFonts[i] != nullptr; ++i) {
    if (std::filesystem::exists(preferredFonts[i])) {
      return PLAString(preferredFonts[i]);
    }
  }

  // Third, search in Resources/fonts/ directory for any font
  static const char* resourceDirs[] = {
    "Resources/fonts/",
    nullptr
  };

  for (int i = 0; resourceDirs[i] != nullptr; ++i) {
    if (std::filesystem::exists(resourceDirs[i])) {
      for (const auto& entry : std::filesystem::directory_iterator(resourceDirs[i])) {
        if (entry.is_regular_file()) {
          PLAString ext = entry.path().extension().string();
          if (ext == ".ttf" || ext == ".TTF" || ext == ".otf" || ext == ".OTF" ||
              ext == ".ttc" || ext == ".TTC") {
            return entry.path().string();
          }
        }
      }
    }
  }

  // Fallback to system fonts - prioritize CJK fonts for Japanese support
  static const char* systemFontPaths[] = {
    // Noto Sans CJK (Japanese support)
    "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",
    "/usr/share/fonts/noto-cjk/NotoSansCJK-Regular.ttc",
    "/usr/share/fonts/google-noto-cjk/NotoSansCJK-Regular.ttc",
    "/usr/share/fonts/OTF/NotoSansCJK-Regular.ttc",
    "/usr/share/fonts/noto/NotoSansCJK-Regular.ttc",
    "/usr/share/fonts/truetype/noto/NotoSansCJK-Regular.ttc",
    // Noto Sans JP (Japanese specific)
    "/usr/share/fonts/opentype/noto/NotoSansJP-Regular.otf",
    "/usr/share/fonts/noto/NotoSansJP-Regular.otf",
    "/usr/share/fonts/google-noto/NotoSansJP-Regular.otf",
    // IPAex Gothic (Japanese)
    "/usr/share/fonts/ipa-gothic/ipagp.ttf",
    "/usr/share/fonts/truetype/fonts-japanese-gothic.ttf",
    "/usr/share/fonts/opentype/ipaexfont-gothic/ipaexg.ttf",
    // VL Gothic (Japanese)
    "/usr/share/fonts/truetype/vlgothic/VL-Gothic-Regular.ttf",
    "/usr/share/fonts/vlgothic/VL-Gothic-Regular.ttf",
    // Takao Gothic (Japanese)
    "/usr/share/fonts/truetype/takao-gothic/TakaoGothic.ttf",
    // Generic fallbacks
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
    "/usr/share/fonts/TTF/DejaVuSans.ttf",
    "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
    "/usr/share/fonts/truetype/freefont/FreeSans.ttf",
    "/usr/share/fonts/noto/NotoSans-Regular.ttf",
    "/usr/share/fonts/TTF/NotoSans-Regular.ttf",
    nullptr
  };

  for (int i = 0; systemFontPaths[i] != nullptr; ++i) {
    std::ifstream file(systemFontPaths[i]);
    if (file.good()) {
      return PLAString(systemFontPaths[i]);
    }
  }

  return PLAString();
}

bool PLAFreeTypeFontRasterizer::Initialize()
{
  if (_fontPath.empty()) {
    _fontPath = FindSystemFont();
    if (_fontPath.empty()) {
      PLA_ERROR_ISSUE(PLAErrorType::Expect,
                      "No system font found. Use SetFontPath() to specify a font file.");
      return false;
    }
  }

  FT_Error error = FT_Init_FreeType(&_library);
  if (error) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to initialize FreeType library. Error: %d", error);
    return false;
  }

  error = FT_New_Face(_library, _fontPath.c_str(), 0, &_face);
  if (error) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to load font: %s. Error: %d", _fontPath.c_str(), error);
    FT_Done_FreeType(_library);
    _library = nullptr;
    return false;
  }

  _isInitialized = true;
  return true;
}

void PLAFreeTypeFontRasterizer::Cleanup()
{
  if (_face) {
    FT_Done_Face(_face);
    _face = nullptr;
  }
  if (_library) {
    FT_Done_FreeType(_library);
    _library = nullptr;
  }
  _isInitialized = false;
}

void PLAFreeTypeFontRasterizer::SetFontPath(const PLAString &aPath)
{
  if (_fontPath != aPath) {
    _fontPath = aPath;
    if (_isInitialized) {
      Cleanup();
      Initialize();
    }
  }
}

cv::Mat PLAFreeTypeFontRasterizer::Rasterize(const PLAString &aText,
                                              PLAFloat aFontSize,
                                              const PLAColor &aColor)
{
  if (!_isInitialized || aText.empty()) {
    return cv::Mat();
  }

  FT_Error error = FT_Set_Pixel_Sizes(_face, 0, static_cast<FT_UInt>(aFontSize));
  if (error) {
    return cv::Mat();
  }

  // Decode UTF-8 to Unicode codepoints
  std::vector<uint32_t> codepoints = DecodeUTF8(aText);
  if (codepoints.empty()) {
    return cv::Mat();
  }

  // Use face design units for accurate metrics (OpenType/TrueType standard)
  PLAFloat scale = aFontSize / static_cast<PLAFloat>(_face->units_per_EM);
  int ascender = static_cast<int>(std::ceil(_face->ascender * scale));
  int descender = static_cast<int>(std::ceil(-_face->descender * scale));
  int lineHeight = ascender + descender;

  // Check if font has kerning
  bool hasKerning = FT_HAS_KERNING(_face);

  // Calculate total width (including kerning)
  int totalWidth = 0;
  FT_UInt prevGlyphIndex = 0;
  for (uint32_t cp : codepoints) {
    FT_UInt glyphIndex = FT_Get_Char_Index(_face, cp);

    // Apply kerning if available
    if (hasKerning && prevGlyphIndex && glyphIndex) {
      FT_Vector delta;
      FT_Get_Kerning(_face, prevGlyphIndex, glyphIndex, FT_KERNING_DEFAULT, &delta);
      totalWidth += (delta.x >> 6);
    }

    error = FT_Load_Glyph(_face, glyphIndex, FT_LOAD_DEFAULT);
    if (error) {
      prevGlyphIndex = glyphIndex;
      continue;
    }
    totalWidth += (_face->glyph->advance.x >> 6);
    prevGlyphIndex = glyphIndex;
  }

  if (totalWidth <= 0) {
    return cv::Mat();
  }

  cv::Mat image(lineHeight, totalWidth, CV_8UC4, cv::Scalar(0, 0, 0, 0));

  uchar r = static_cast<uchar>(aColor.r * 255);
  uchar g = static_cast<uchar>(aColor.g * 255);
  uchar b = static_cast<uchar>(aColor.b * 255);
  uchar a = static_cast<uchar>(aColor.a * 255);

  // Pen starts at x=0, baseline is at ascender position from top
  int penX = 0;
  int baselineY = ascender;
  prevGlyphIndex = 0;

  for (uint32_t cp : codepoints) {
    FT_UInt glyphIndex = FT_Get_Char_Index(_face, cp);

    // Apply kerning if available
    if (hasKerning && prevGlyphIndex && glyphIndex) {
      FT_Vector delta;
      FT_Get_Kerning(_face, prevGlyphIndex, glyphIndex, FT_KERNING_DEFAULT, &delta);
      penX += (delta.x >> 6);
    }

    error = FT_Load_Glyph(_face, glyphIndex, FT_LOAD_RENDER);
    if (error) {
      prevGlyphIndex = glyphIndex;
      continue;
    }

    FT_GlyphSlot glyph = _face->glyph;
    FT_Bitmap &bitmap = glyph->bitmap;

    int glyphX = penX + glyph->bitmap_left;
    int glyphY = baselineY - glyph->bitmap_top;

    for (unsigned int row = 0; row < bitmap.rows; ++row) {
      for (unsigned int col = 0; col < bitmap.width; ++col) {
        int x = glyphX + col;
        int y = glyphY + row;

        if (x >= 0 && x < totalWidth && y >= 0 && y < lineHeight) {
          uchar gray = bitmap.buffer[row * bitmap.pitch + col];
          if (gray > 0) {
            cv::Vec4b &pixel = image.at<cv::Vec4b>(y, x);
            uchar existingAlpha = pixel[3];
            uchar newAlpha = (gray * a) / 255;

            if (newAlpha > existingAlpha) {
              pixel[0] = r;  // RGBA format for OpenGL
              pixel[1] = g;
              pixel[2] = b;
              pixel[3] = newAlpha;
            }
          }
        }
      }
    }

    penX += (glyph->advance.x >> 6);
    prevGlyphIndex = glyphIndex;
  }

  return image;
}

PLAVec2f PLAFreeTypeFontRasterizer::GetTextSize(const PLAString &aText,
                                                 PLAFloat aFontSize)
{
  if (!_isInitialized || aText.empty()) {
    return PLAVec2f(0, 0);
  }

  FT_Error error = FT_Set_Pixel_Sizes(_face, 0, static_cast<FT_UInt>(aFontSize));
  if (error) {
    return PLAVec2f(0, 0);
  }

  // Decode UTF-8 to Unicode codepoints
  std::vector<uint32_t> codepoints = DecodeUTF8(aText);
  if (codepoints.empty()) {
    return PLAVec2f(0, 0);
  }

  // Use face design units for accurate metrics (OpenType/TrueType standard)
  PLAFloat scale = aFontSize / static_cast<PLAFloat>(_face->units_per_EM);
  int ascender = static_cast<int>(std::ceil(_face->ascender * scale));
  int descender = static_cast<int>(std::ceil(-_face->descender * scale));
  int lineHeight = ascender + descender;

  // Check if font has kerning
  bool hasKerning = FT_HAS_KERNING(_face);

  int totalWidth = 0;
  FT_UInt prevGlyphIndex = 0;
  for (uint32_t cp : codepoints) {
    FT_UInt glyphIndex = FT_Get_Char_Index(_face, cp);

    // Apply kerning if available
    if (hasKerning && prevGlyphIndex && glyphIndex) {
      FT_Vector delta;
      FT_Get_Kerning(_face, prevGlyphIndex, glyphIndex, FT_KERNING_DEFAULT, &delta);
      totalWidth += (delta.x >> 6);
    }

    error = FT_Load_Glyph(_face, glyphIndex, FT_LOAD_DEFAULT);
    if (error) {
      prevGlyphIndex = glyphIndex;
      continue;
    }
    totalWidth += (_face->glyph->advance.x >> 6);
    prevGlyphIndex = glyphIndex;
  }

  return PLAVec2f(totalWidth, lineHeight);
}

PLAFontMetrics PLAFreeTypeFontRasterizer::GetMetrics(PLAFloat aFontSize)
{
  PLAFontMetrics metrics = {0, 0, 0};

  if (!_isInitialized) {
    return metrics;
  }

  FT_Error error = FT_Set_Pixel_Sizes(_face, 0, static_cast<FT_UInt>(aFontSize));
  if (error) {
    return metrics;
  }

  // Use face design units for accurate metrics (OpenType/TrueType standard)
  PLAFloat scale = aFontSize / static_cast<PLAFloat>(_face->units_per_EM);
  metrics.ascender = static_cast<PLAFloat>(_face->ascender) * scale;
  metrics.descender = static_cast<PLAFloat>(-_face->descender) * scale;
  metrics.lineHeight = metrics.ascender + metrics.descender;

  return metrics;
}
