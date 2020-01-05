#include "PLARenderer.hpp"

#include "PLARenderingManager.hpp"

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
    this->DrawRect(static_cast<const PLARDRect *>(*it));
  }

  this->Flush();
}
