// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAOBJFONTRASTERIZER_HPP
#define PLAIN_ENGINE_PLAOBJFONTRASTERIZER_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/PLAFontRasterizerType.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"
#include "plain/core/primitive/PLAPRMVector.hpp"
#include <opencv2/opencv.hpp>

class PLAOBJFontRasterizer : public PLAObject
{
protected:
  bool _isInitialized = false;

  PLAOBJFontRasterizer();

public:
  static PLAOBJFontRasterizer *Create(PLAFontRasterizerType aType);

  virtual ~PLAOBJFontRasterizer();

  virtual bool Initialize() = 0;
  virtual cv::Mat Rasterize(const PLAString &aText, PLAFloat aFontSize,
                            const PLAColor &aColor) = 0;
  virtual PLAVec2f GetTextSize(const PLAString &aText, PLAFloat aFontSize) = 0;

  bool IsInitialized() const { return _isInitialized; }
};

#endif // PLAIN_ENGINE_PLAOBJFONTRASTERIZER_HPP
