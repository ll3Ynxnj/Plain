// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAOBJFONTRASTERIZER_HPP
#define PLAIN_ENGINE_PLAOBJFONTRASTERIZER_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/PLAFontRasterizerType.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"
#include "plain/core/primitive/PLAPRMVector.hpp"
#include "grain/object/GRAOBJBinder.hpp"
#include <opencv2/opencv.hpp>

// Font metrics following OpenType/TrueType standards
struct PLAFontMetrics
{
  PLAFloat ascender;    // Distance from baseline to top (positive)
  PLAFloat descender;   // Distance from baseline to bottom (positive, measured downward)
  PLAFloat lineHeight;  // Total line height (ascender + descender)
};

class PLAOBJFontRasterizer : public PLAObject,
                             private GRAOBJBinder<PLAOBJFontRasterizer>::Item
{
  using Binder = GRAOBJBinder<PLAOBJFontRasterizer>;

protected:
  bool _isInitialized = false;

  PLAOBJFontRasterizer(const PLAString &aName);

public:
  using PLAFontRasterizerItem = GRAOBJBinder<PLAOBJFontRasterizer>::Item;
  using PLAFontRasterizerError = GRAOBJBinder<PLAOBJFontRasterizer>::Error;

  static PLAOBJFontRasterizer *Create(PLAFontRasterizerType aType,
                                       const PLAString &aName = "FontRasterizer");
  static PLAOBJFontRasterizer *Rasterizer(const PLAString &aName);

  void Bind() override;

protected:
  void Unbind() override;

public:
  virtual ~PLAOBJFontRasterizer();

  virtual bool Initialize() = 0;
  virtual cv::Mat Rasterize(const PLAString &aText, PLAFloat aFontSize,
                            const PLAColor &aColor) = 0;
  virtual PLAVec2f GetTextSize(const PLAString &aText, PLAFloat aFontSize) = 0;
  virtual PLAFontMetrics GetMetrics(PLAFloat aFontSize) = 0;

  bool IsInitialized() const { return _isInitialized; }

//-- GRAOBJBinder::Item --/////////////////////////////////////////////////////////
private:
  const char *GetBinderItemTypeName() const override;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRAOBJBinder<PLAOBJFontRasterizer>
  {
    static Manager _instance;

    Manager();

  public:
    static Manager *Instance() { return &_instance; };

    ~Manager();

    void Init();
  };
};

#endif // PLAIN_ENGINE_PLAOBJFONTRASTERIZER_HPP
