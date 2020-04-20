#ifndef PLAAPP_HPP
#define PLAAPP_HPP

#include "PLAType.hpp"

class PLAStage;
class PLARenderer;
struct PLARenderingData;

class PLAApp
{
  static PLAApp _instance;

  PLAStage *_stage;
  PLARenderer *_renderer;

  PLAApp();

public:
  static const int kBaseScreenLength = 320;

  static PLAApp *GetInstance() { return &_instance; }

  ~PLAApp();

  void Init();
  void Setup();
  void Reset();
  void Update();
  void Render();

  void PushRenderingData(const PLARenderingData *aData);
  void RefreshScreenSize(int aWidth, int aHeight);

  void SetRenderer(PLARenderer *aRenderer);
};


#endif
