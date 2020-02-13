#include "PLARenderingManager.hpp"
#include "PLAStageManager.hpp"
#include "PLARDRect.hpp"
#include "PLARDCircle.hpp"

PLARenderingManager::PLARenderingManager() :
  _renderingData()
{

}

PLARenderingManager::~PLARenderingManager()
{

}

void PLARenderingManager::ClearRenderingData()
{
  for (const PLARenderingData *data : _renderingData)
  {
    delete data;
  }
  _renderingData.clear();
}

void PLARenderingManager::PushRenderingDataRect(GRARect &aRect, GRAColor aColor)
{
  _renderingData.push_back(new PLARDRect(aRect, aColor));
}

void PLARenderingManager::PushRenderingDataCircle(GRACircle &aCircle, GRAColor aColor, GRAInt aSplit)
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
