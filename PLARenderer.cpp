#include "PLARenderer.hpp"
#include "PLAError.hpp"
#include "PLAGLUTRenderer.hpp"
#include "PLAShape.hpp"

PLARenderer *PLARenderer::Create(PLARendererType aType)
{
  switch (aType)
  {
    case PLARendererType::GLUT :
      return new PLAGLUTRenderer();
    default :
      PLAError::
      Throw(PLAErrorType::Assert,
            "Unexpected PLARenderingDataType detected.");
  }
  return nullptr;
}

PLARenderer::PLARenderer()
{

}

PLARenderer::~PLARenderer()
{

}

void PLARenderer::Render(const PLAColor *aColor,
                         const PLATransform *aTransform,
                         const PLAShape *aShape) const
{
  switch (aShape->GetShapeType()) {
    case PLAShapeType::Rect :
      this->DrawRect(aColor, aTransform,
                     static_cast<const PLAShapeRect *>(aShape));
      break;
    case PLAShapeType::Circle :
      this->DrawCircle(aColor, aTransform,
                       static_cast<const PLAShapeCircle *>(aShape));
      break;
    default :
      PLAError::Throw(PLAErrorType::Assert,
                      "Unexpected PLARenderingDataType detected.");
      break;
  }
}
