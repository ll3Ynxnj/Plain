#include "PLARenderer.hpp"

#include "PLARenderingManager.hpp"
#include "PLADebug.hpp"

PLARenderer::PLARenderer()
{

}

PLARenderer::~PLARenderer()
{

}

void PLARenderer::Render()
{
  this->Clear();

  this->DrawDemo();

  PLARenderingManager::GetInstance()->RefreshRenderingData();
  const PLARenderingDataSet *renderingData =
    PLARenderingManager::GetInstance()->GetRenderingData();
  for (PLARenderingDataSet::const_iterator it = renderingData->begin();
       it != renderingData->end(); it++)
  {
    switch ((*it)->type)
    {
    case PLARenderingDataType::Rect :
      this->DrawRect(static_cast<const PLARDRect *>(*it));
      break;
    case PLARenderingDataType::Circle :
      this->DrawCircle(static_cast<const PLARDCircle *>(*it));
      break;
    default :
      PLADebug::Assert("Unexpected PLARenderingDataType detected.");
      break;
    }
  }

  this->Flush();
}
