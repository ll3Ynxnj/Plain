#ifndef PLAIN_PLAAPP_HPP
#define PLAIN_PLAAPP_HPP

#include "PLAObj.hpp"
#include "PLARendererType.hpp"

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

  void Init(PLARendererType Type);
  void Reset();
  void Update();
  void Render();

  //void PushRenderingData(const PLARenderingData *aData);
  void RefreshScreenSize(int aWidth, int aHeight);
};

#endif // PLAIN_PLAAPP
