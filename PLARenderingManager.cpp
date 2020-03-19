#include "PLARenderingManager.hpp"
#include "PLAStageManager.hpp"
#include "PLARDRect.hpp"
#include "PLARDCircle.hpp"
#include "PLARenderer.hpp"

PLARenderingManager PLARenderingManager::_instance = PLARenderingManager();

PLARenderingManager::PLARenderingManager() :
  _renderer(nullptr),
  _renderingData()
{

}

PLARenderingManager::~PLARenderingManager()
{

}

void PLARenderingManager::Update()
{
  _renderer->Render();
}

void PLARenderingManager::ClearRenderingData()
{
  for (const PLARenderingData *data : _renderingData)
  {
    delete data;
  }
  _renderingData.clear();
}

void PLARenderingManager::PushRenderingDataRect(const GRARect &aRect, const GRAColor &aColor)
{
  _renderingData.push_back(new PLARDRect(aRect, aColor));
}

void PLARenderingManager::PushRenderingDataCircle(const GRACircle &aCircle, const GRAColor &aColor, int aSplit)
{
  _renderingData.push_back(new PLARDCircle(aCircle, aColor, aSplit));
}

void PLARenderingManager::RefreshRenderingData()
{
  this->ClearRenderingData();
  PLAStageManager::GetInstance()->Render();
}

const PLARenderingDataSet *PLARenderingManager::GetRenderingData() const
{
  return &_renderingData;
}

void PLARenderingManager::SetRenderer(PLARenderer *aRenderer)
{
  _renderer = aRenderer;
}
