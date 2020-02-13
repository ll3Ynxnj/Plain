#ifndef PLARENDERINGMANAGER_HPP
#define PLARENDERINGMANAGER_HPP

#include <vector>
#include "PLARenderingData.hpp"
#include "./Grain/GRAType.h"
#include "./Grain/GRARect.h"
#include "./Grain/GRACircle.h"
#include "./Grain/GRAColor.h"

typedef std::vector<const PLARenderingData *> PLARenderingDataSet;

class PLARenderingManager
{
  PLARenderingDataSet _renderingData;

  PLARenderingManager();

public:
  static PLARenderingManager* GetInstance()
  { static PLARenderingManager instance; return &instance; }

  ~PLARenderingManager();

  void ClearRenderingData();

  void PushRenderingDataRect(GRARect &aRect, GRAColor aColor);
  void PushRenderingDataCircle(GRACircle &aCircle, GRAColor aColor, GRAInt aSplit);

  void RefreshRenderingData();
  const PLARenderingDataSet *GetRenderingData() const;
};

#endif
