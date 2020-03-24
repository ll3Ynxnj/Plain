#ifndef PLARENDERINGMANAGER_HPP
#define PLARENDERINGMANAGER_HPP

#include <vector>

class PLARenderer;
class PLARenderingData;

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
  void PushRenderingData(const PLARenderingData *aData);

  void SetRenderer(PLARenderer *aRenderer);

private:
  void Clear();
  void Render();
};

#endif
