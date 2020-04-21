#ifndef PLAIN_PLAAPP_HPP
#define PLAIN_PLAAPP_HPP

#include "PLAObj.hpp"

class PLAStage;
class PLARenderer;
struct PLARenderingData;

class PLAApp : public PLAObj
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

#endif // PLAIN_PLAAPP
