#include "PLARenderer.hpp"
#include "../GLUT/PLAGLUTRenderer.hpp"
#include "PLAError.hpp"

PLARenderer *PLARenderer::Create(PLARendererType aType)
{
  switch (aType)
  {
    case PLARendererType::GLUT : return PLAGLUTRenderer::Create();
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Unexpected renderer type detected.");
      return nullptr;
  }
}

PLARenderer::PLARenderer() :
PLAObject(PLAObjectType::Renderer, "== PLARenderer ==")
{

}

PLARenderer::~PLARenderer()
{

}
