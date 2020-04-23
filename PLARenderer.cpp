#include "PLARenderer.hpp"
#include "PLAErrorManager.hpp"
#include "PLAGLUTRenderer.hpp"

PLARenderer *PLARenderer::Create(PLARendererType aType)
{
  switch (aType)
  {
    case PLARendererType::GLUT :
      return new PLAGLUTRenderer();
    default :
      PLAErrorManager::GetInstance()->
      Throw(PLAErrorType::Assert,
            "Unexpected PLARenderingDataType detected.");
  }
  return nullptr;
}

PLARenderer::PLARenderer() :
_renderingDataSet()
{

}

PLARenderer::~PLARenderer()
{

}

void PLARenderer::PushRenderingData(const PLARenderingData *aData)
{
  _renderingDataSet.push_back(aData);
}

void PLARenderer::Render()
{
  for (std::vector<const PLARenderingData *>::const_iterator it =
  _renderingDataSet.begin(); it != _renderingDataSet.end(); it++) {
    switch ((*it)->type) {
      case PLARenderingDataType::Rect :
        this->DrawRect(static_cast<const PLARDRect *>(*it));
        break;
      case PLARenderingDataType::Circle :
        this->DrawCircle(static_cast<const PLARDCircle *>(*it));
        break;
      default :
        PLAErrorManager::GetInstance()->
        Throw(PLAErrorType::Assert,
              "Unexpected PLARenderingDataType detected.");
        break;
    }
  }
}
