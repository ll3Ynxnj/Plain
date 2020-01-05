#include "PLARenderingManager.hpp"

#include "PLARDRect.hpp"

PLARenderingManager::PLARenderingManager() :
  _renderingData()
{

}

PLARenderingManager::~PLARenderingManager()
{

}

void PLARenderingManager::RefreshRenderingData()
{
  static const PLARDRect rd[] =
  {
    PLARDRect( -0.3, -0.3, 0.6, 0.6, 0.0, 1.0, 1.0, 1.0 ),
    PLARDRect( -0.2, -0.2, 0.4, 0.4, 1.0, 0.0, 1.0, 1.0 ),
    PLARDRect( -0.1, -0.1, 0.2, 0.2, 1.0, 1.0, 0.0, 1.0 ),
  };

  _renderingData.clear();

  for (int i = 0; i < 3; i++)
  {
    _renderingData.push_back(static_cast<const PLARenderingData *>(&rd[i]));
  }
}

const PLARenderingDataSet *PLARenderingManager::GetRenderingData() const
{
  return &_renderingData;
}
