#include "PLARenderer.hpp"
#include "PLARenderingData.hpp"

PLARenderer::PLARenderer()
{

}

PLARenderer::~PLARenderer()
{

}

void PLARenderer::Render()
{
  static const GRAPoint point = { -0.5, -0.5 };
  static const GRASize size = { 1.0, 1.0 };
  static const GRARect rect = { point, size };
  static const GRAColorRGBA color = { 1.0, 1.0, 1.0, 1.0 };
  static const PLARDRect rdRect(rect, color);

  this->DrawRect(&rdRect);
}
