#ifndef PLARENDERINGMANAGER_HPP
#define PLARENDERINGMANAGER_HPP

#include <vector>

#include "PLARenderingData.hpp"

typedef std::vector<const PLARenderingData *> PLARenderingDataSet;

class PLARenderingManager
{
  PLARenderingDataSet _renderingData;

  PLARenderingManager();

public:
  static PLARenderingManager* GetInstance()
  { static PLARenderingManager instance; return &instance; }

  ~PLARenderingManager();

  void RefreshRenderingData();
  const PLARenderingDataSet *GetRenderingData() const;
};

#endif
