#include "plain/glut/PLAGLUTRenderer.hpp"
#include "plain/core/object/PLAOBJRenderer.hpp"
#include "plain/core/object/PLAOBJError.hpp"

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
