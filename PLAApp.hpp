#ifndef PLAIN_PLAAPP_HPP
#define PLAIN_PLAAPP_HPP

#include "PLAObject.hpp"
#include "PLARendererType.hpp"

class PLAStage;
class PLARenderer;

class PLAApp : public PLAObject
{
  static PLAApp _instance;

  PLAStage *_stage = nullptr;
  PLARenderer *_renderer = nullptr;

  PLAApp();

public:
  static const int kBaseScreenLength = 320;

  static PLAApp *GetInstance() { return &_instance; }

  ~PLAApp();

  void Init(PLARenderer *aType);
  void Reset();
  void Update();
  void Render();

  //void PushRenderingData(const PLARenderingData *aData);
  void RefreshScreenSize(int aWidth, int aHeight);
};

#endif // PLAIN_PLAAPP
