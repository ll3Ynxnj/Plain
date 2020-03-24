#include "PLARenderingManager.hpp"
#include "PLAErrorManager.hpp"
#include "PLAStageManager.hpp"
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
  _renderer->Clear();
  this->Clear();

  _renderer->DrawDemo();

  PLAStageManager::GetInstance()->Render();
  this->Render();

  _renderer->Flush();
}

void PLARenderingManager::PushRenderingData(const PLARenderingData *aData)
{
  _renderingData.push_back(aData);
}

void PLARenderingManager::SetRenderer(PLARenderer *aRenderer)
{
  _renderer = aRenderer;
}

void PLARenderingManager::Clear()
{
  for (const PLARenderingData *data : _renderingData)
  {
    delete data;
  }
  _renderingData.clear();
}

void PLARenderingManager::Render()
{
  for (PLARenderingDataSet::const_iterator it = _renderingData.begin();
       it != _renderingData.end(); it++)
  {
    switch ((*it)->type)
    {
      case PLARenderingDataType::Rect :
        _renderer->DrawRect(static_cast<const PLARDRect *>(*it));
        break;
      case PLARenderingDataType::Circle :
        _renderer->DrawCircle(static_cast<const PLARDCircle *>(*it));
        break;
      default :
        PLAErrorManager::GetInstance()->
        Throw(PLAErrorType::Assert, "Unexpected PLARenderingDataType detected.");
        break;
    }
  }
}
