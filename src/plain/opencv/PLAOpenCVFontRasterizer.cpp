// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/opencv/PLAOpenCVFontRasterizer.hpp"

PLAOpenCVFontRasterizer *PLAOpenCVFontRasterizer::Create(const PLAString &aName)
{
  PLAOpenCVFontRasterizer *rasterizer = new PLAOpenCVFontRasterizer(aName);
  if (!rasterizer->Initialize()) {
    delete rasterizer;
    return nullptr;
  }
  return rasterizer;
}

PLAOpenCVFontRasterizer::PLAOpenCVFontRasterizer(const PLAString &aName) :
  PLAOBJFontRasterizer(aName)
{
}

PLAOpenCVFontRasterizer::~PLAOpenCVFontRasterizer()
{
}

bool PLAOpenCVFontRasterizer::Initialize()
{
  _isInitialized = true;
  return true;
}

cv::Mat PLAOpenCVFontRasterizer::Rasterize(const PLAString &aText,
                                            PLAFloat aFontSize,
                                            const PLAColor &aColor)
{
  if (!_isInitialized) {
    return cv::Mat();
  }

  PLAFloat fontScale = aFontSize / 24.0;
  int baseline = 0;
  cv::Size textSize = cv::getTextSize(aText, _fontFace, fontScale,
                                      _thickness, &baseline);

  int padding = 4;
  int width = textSize.width + padding * 2;
  int height = textSize.height + baseline + padding * 2;

  // Create grayscale image for text mask
  cv::Mat mask(height, width, CV_8UC1, cv::Scalar(0));
  cv::Point textOrg(padding, textSize.height + padding);
  cv::putText(mask, aText, textOrg, _fontFace, fontScale, cv::Scalar(255), _thickness, cv::LINE_AA);

  // Create RGBA image
  cv::Mat image(height, width, CV_8UC4, cv::Scalar(0, 0, 0, 0));

  // Set color and alpha based on mask
  uchar r = static_cast<uchar>(aColor.r * 255);
  uchar g = static_cast<uchar>(aColor.g * 255);
  uchar b = static_cast<uchar>(aColor.b * 255);
  uchar a = static_cast<uchar>(aColor.a * 255);

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      uchar maskVal = mask.at<uchar>(y, x);
      if (maskVal > 0) {
        cv::Vec4b &pixel = image.at<cv::Vec4b>(y, x);
        pixel[0] = b;  // B
        pixel[1] = g;  // G
        pixel[2] = r;  // R
        pixel[3] = (maskVal * a) / 255;  // A (anti-aliased)
      }
    }
  }

  return image;
}

PLAVec2f PLAOpenCVFontRasterizer::GetTextSize(const PLAString &aText,
                                               PLAFloat aFontSize)
{
  if (!_isInitialized) {
    return PLAVec2f(0, 0);
  }

  PLAFloat fontScale = aFontSize / 24.0;
  int baseline = 0;
  cv::Size textSize = cv::getTextSize(aText, _fontFace, fontScale,
                                      _thickness, &baseline);

  int padding = 4;
  return PLAVec2f(textSize.width + padding * 2,
                  textSize.height + baseline + padding * 2);
}

PLAFontMetrics PLAOpenCVFontRasterizer::GetMetrics(PLAFloat aFontSize)
{
  PLAFontMetrics metrics = {0, 0, 0};

  if (!_isInitialized) {
    return metrics;
  }

  // OpenCV fonts don't have standard font metrics, approximate using getTextSize
  PLAFloat fontScale = aFontSize / 24.0;
  int baseline = 0;
  cv::Size textSize = cv::getTextSize("Hg", _fontFace, fontScale,
                                       _thickness, &baseline);

  // Approximate ascender as text height (capital H height)
  // Approximate descender as baseline (descent below baseline for 'g')
  metrics.ascender = static_cast<PLAFloat>(textSize.height);
  metrics.descender = static_cast<PLAFloat>(baseline);
  metrics.lineHeight = metrics.ascender + metrics.descender;

  return metrics;
}
