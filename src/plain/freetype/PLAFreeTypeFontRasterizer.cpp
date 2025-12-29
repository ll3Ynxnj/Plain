// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/freetype/PLAFreeTypeFontRasterizer.hpp"
#include "plain/core/object/PLAOBJError.hpp"
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

PLAFreeTypeFontRasterizer::PLAFreeTypeFontRasterizer(const PLAString &aName) :
  PLAOBJFontRasterizer(aName)
{
}

PLAFreeTypeFontRasterizer::~PLAFreeTypeFontRasterizer()
{
  Cleanup();
}

PLAString PLAFreeTypeFontRasterizer::FindSystemFont()
{
  // First, check CMake-configured default font path
#ifdef PLA_DEFAULT_FONT_PATH
  if (std::filesystem::exists(PLA_DEFAULT_FONT_PATH)) {
    return PLAString(PLA_DEFAULT_FONT_PATH);
  }
#endif

  // Second, search in Resources/fonts/ directory
  static const char* resourceDirs[] = {
    "Resources/fonts/",
    "Resources/",
    nullptr
  };

  for (int i = 0; resourceDirs[i] != nullptr; ++i) {
    if (std::filesystem::exists(resourceDirs[i])) {
      for (const auto& entry : std::filesystem::directory_iterator(resourceDirs[i])) {
        if (entry.is_regular_file()) {
          PLAString ext = entry.path().extension().string();
          if (ext == ".ttf" || ext == ".TTF" || ext == ".otf" || ext == ".OTF") {
            return entry.path().string();
          }
        }
      }
    }
  }

  // Fallback to system fonts
  static const char* systemFontPaths[] = {
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

  int padding = 4;
  int totalWidth = padding * 2;
  int maxAscender = 0;
  int maxDescender = 0;

  for (char c : aText) {
    error = FT_Load_Char(_face, c, FT_LOAD_DEFAULT);
    if (error) continue;

    totalWidth += (_face->glyph->advance.x >> 6);
    int ascender = _face->glyph->bitmap_top;
    int descender = _face->glyph->bitmap.rows - _face->glyph->bitmap_top;
    if (ascender > maxAscender) maxAscender = ascender;
    if (descender > maxDescender) maxDescender = descender;
  }

  int height = maxAscender + maxDescender + padding * 2;
  int width = totalWidth;

  cv::Mat image(height, width, CV_8UC4, cv::Scalar(0, 0, 0, 0));

  uchar r = static_cast<uchar>(aColor.r * 255);
  uchar g = static_cast<uchar>(aColor.g * 255);
  uchar b = static_cast<uchar>(aColor.b * 255);
  uchar a = static_cast<uchar>(aColor.a * 255);

  int penX = padding;
  int baselineY = padding + maxAscender;

  for (char c : aText) {
    error = FT_Load_Char(_face, c, FT_LOAD_RENDER);
    if (error) continue;

    FT_GlyphSlot glyph = _face->glyph;
    FT_Bitmap &bitmap = glyph->bitmap;

    int glyphX = penX + glyph->bitmap_left;
    int glyphY = baselineY - glyph->bitmap_top;

    for (unsigned int row = 0; row < bitmap.rows; ++row) {
      for (unsigned int col = 0; col < bitmap.width; ++col) {
        int x = glyphX + col;
        int y = glyphY + row;

        if (x >= 0 && x < width && y >= 0 && y < height) {
          uchar gray = bitmap.buffer[row * bitmap.pitch + col];
          if (gray > 0) {
            cv::Vec4b &pixel = image.at<cv::Vec4b>(y, x);
            uchar existingAlpha = pixel[3];
            uchar newAlpha = (gray * a) / 255;

            if (newAlpha > existingAlpha) {
              pixel[0] = b;
              pixel[1] = g;
              pixel[2] = r;
              pixel[3] = newAlpha;
            }
          }
        }
      }
    }

    penX += (glyph->advance.x >> 6);
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

  int padding = 4;
  int totalWidth = padding * 2;
  int maxAscender = 0;
  int maxDescender = 0;

  for (char c : aText) {
    error = FT_Load_Char(_face, c, FT_LOAD_DEFAULT);
    if (error) continue;

    totalWidth += (_face->glyph->advance.x >> 6);
    int ascender = _face->glyph->bitmap_top;
    int descender = _face->glyph->bitmap.rows - _face->glyph->bitmap_top;
    if (ascender > maxAscender) maxAscender = ascender;
    if (descender > maxDescender) maxDescender = descender;
  }

  int height = maxAscender + maxDescender + padding * 2;

  return PLAVec2f(totalWidth, height);
}
