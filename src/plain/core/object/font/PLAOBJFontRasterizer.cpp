// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/core/object/font/PLAOBJFontRasterizer.hpp"
#include "plain/opencv/PLAOpenCVFontRasterizer.hpp"
#include "plain/freetype/PLAFreeTypeFontRasterizer.hpp"
#include "plain/core/object/PLAOBJError.hpp"

PLAOBJFontRasterizer *PLAOBJFontRasterizer::Create(PLAFontRasterizerType aType,
                                                    const PLAString &aName)
{
  PLAOBJFontRasterizer *rasterizer = nullptr;

  switch (aType)
  {
    case PLAFontRasterizerType::OpenCV:
      rasterizer = PLAOpenCVFontRasterizer::Create(aName);
      break;
    case PLAFontRasterizerType::FreeType:
      rasterizer = PLAFreeTypeFontRasterizer::Create(aName);
      break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Unexpected font rasterizer type detected.");
      return nullptr;
  }

  if (rasterizer) {
    rasterizer->Bind();
  }
  return rasterizer;
}

PLAOBJFontRasterizer *PLAOBJFontRasterizer::Rasterizer(const PLAString &aName)
{
  GRAOBJBinder<PLAOBJFontRasterizer>::Error error(GRAOBJBinder<PLAOBJFontRasterizer>::Error::None);
  return static_cast<PLAOBJFontRasterizer *>(Manager::Instance()->RefItemWithName(aName, &error));
}

void PLAOBJFontRasterizer::Bind()
{
  this->PLAObject::Bind();

  GRAOBJBinder<PLAOBJFontRasterizer>::Error error(GRAOBJBinder<PLAOBJFontRasterizer>::Error::None);
  PLAOBJFontRasterizer::Manager::Instance()->Bind(this, &error);
  if (error != GRAOBJBinder<PLAOBJFontRasterizer>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJFontRasterizer binding. ERROR : %02d", error); }
}

void PLAOBJFontRasterizer::Unbind()
{
  GRAOBJBinder<PLAOBJFontRasterizer>::Error error(GRAOBJBinder<PLAOBJFontRasterizer>::Error::None);
  PLAOBJFontRasterizer::Manager::Instance()->Unbind(this, &error);
  if (error != GRAOBJBinder<PLAOBJFontRasterizer>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJFontRasterizer unbinding. ERROR : %02d", error); }

  this->PLAObject::Unbind();
}

PLAOBJFontRasterizer::PLAOBJFontRasterizer(const PLAString &aName) :
  PLAObject(PLAObjectType::FontRasterizer, aName),
  GRAOBJBinder<PLAOBJFontRasterizer>::Item(aName, Manager::Instance())
{
}

PLAOBJFontRasterizer::~PLAOBJFontRasterizer()
{
}

// GRAOBJBinder::Item //////////////////////////////////////////////////////////

const char *PLAOBJFontRasterizer::GetBinderItemTypeName() const
{
  static const char *kName = "PLAOBJFontRasterizer";
  return kName;
}

// PLAOBJFontRasterizer::Manager ///////////////////////////////////////////////

PLAOBJFontRasterizer::Manager PLAOBJFontRasterizer::Manager::_instance =
  PLAOBJFontRasterizer::Manager();

PLAOBJFontRasterizer::Manager::Manager() : GRAOBJBinder<PLAOBJFontRasterizer>()
{
}

PLAOBJFontRasterizer::Manager::~Manager()
{
}

void PLAOBJFontRasterizer::Manager::Init()
{
  GRAOBJBinder<PLAOBJFontRasterizer>::Init();
}
