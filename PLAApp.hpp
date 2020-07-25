#ifndef PLAIN_PLAAPP_HPP
#define PLAIN_PLAAPP_HPP

#include "PLAObject.hpp"
#include "PLAInputType.hpp"
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

  static PLAApp *GetInstance() { return &_instance; };
  static PLAStage *Stage() { return _instance._stage; };

  static PLAInputCode GetInputCodeFromChar(const unsigned char aCharacter);

  ~PLAApp();

  void Init(PLARenderer *aType);
  void Reset();
  void Input(PLAInputDevice aDevice, PLAInputCode aCode, PLAInputState aState);
  void Update();
  void Render();

  //void PushRenderingData(const PLARenderingData *aData);
  void RefreshScreenSize(int aWidth, int aHeight);
};

#endif // PLAIN_PLAAPP
