#include "GLUT/PLAGLUTRenderer.hpp"
#include "Core/Object/PLAOBJRenderer.hpp"
#include "Core/Object/PLAOBJError.hpp"

PLAOBJRenderer *PLAOBJRenderer::Create(PLARendererType aType)
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

PLAOBJRenderer::PLAOBJRenderer() :
PLAObject(PLAObjectType::Renderer, "== PLAOBJRenderer ==")
{

}

PLAOBJRenderer::~PLAOBJRenderer()
{

}
