#include "PLARenderingManager.hpp"

#include "PLARDRect.hpp"
#include "PLARDCircle.hpp"

PLARenderingManager::PLARenderingManager() :
  _renderingData()
{

}

PLARenderingManager::~PLARenderingManager()
{

}

void PLARenderingManager::RefreshRenderingData()
{
  _renderingData.clear();

  static const int kSplit = 24;
  static const PLARDCircle kRDCircle[] =
  {
    PLARDCircle({{{ 0.0, 0.0 }, 0.6 }, kGRAColorRed,   kSplit}),
    PLARDCircle({{{ 0.0, 0.0 }, 0.5 }, kGRAColorGreen, kSplit}),
    PLARDCircle({{{ 0.0, 0.0 }, 0.4 }, kGRAColorBlue,  kSplit}),
  };
  for (int i = 0; i < 3; i++)
  {
    _renderingData.push_back(static_cast<const PLARenderingData *>(&kRDCircle[i]));
  }

  static const PLARDRect kRDRect[] =
  {
    PLARDRect({{{ -0.3, -0.3 }, { 0.6, 0.6 }}, kGRAColorCyan    }),
    PLARDRect({{{ -0.2, -0.2 }, { 0.4, 0.4 }}, kGRAColorMagenta }),
    PLARDRect({{{ -0.1, -0.1 }, { 0.2, 0.2 }}, kGRAColorYellow  }),
  };
  for (int i = 0; i < 3; i++)
  {
    _renderingData.push_back(static_cast<const PLARenderingData *>(&kRDRect[i]));
  }
}

const PLARenderingDataSet *PLARenderingManager::GetRenderingData() const
{
  return &_renderingData;
}
