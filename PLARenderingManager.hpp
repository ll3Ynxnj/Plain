#ifndef PLARENDERINGMANAGER_HPP
#define PLARENDERINGMANAGER_HPP

#include <vector>
#include "PLARenderingData.hpp"
#include "Grain/GRARect.h"
#include "Grain/GRACircle.h"
#include "Grain/GRAColor.h"

class PLARenderer;

typedef std::vector<const PLARenderingData *> PLARenderingDataSet;

class PLARenderingManager
{
  static PLARenderingManager _instance;

  PLARenderer *_renderer;
  PLARenderingDataSet _renderingData;

  PLARenderingManager();

public:
  static PLARenderingManager* GetInstance()
  {  return &_instance; }

  ~PLARenderingManager();

  void Update();

  void ClearRenderingData();

  void PushRenderingDataRect(const GRARect &aRect, const GRAColor &aColor);
  void PushRenderingDataCircle(const GRACircle &aCircle, const GRAColor &aColor, int aSplit);

  void RefreshRenderingData();
  const PLARenderingDataSet *GetRenderingData() const;
  void SetRenderer(PLARenderer *aRenderer);
};

#endif
