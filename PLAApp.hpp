#ifndef PLAAPP_HPP
#define PLAAPP_HPP

#include "Grain/GRASize.h"

class PLARenderer;

class PLAApp
{
  static PLAApp _instance;

  PLAApp();

public:
  static PLAApp *GetInstance() { return &_instance; }

  ~PLAApp();

  static void Init();
  static void Setup();
  static void Reset();
  static void Update();

  static void SetRenderer(PLARenderer *aRenderer);
  static void SetScreenSize(const GRASize &aSize);
};

#endif
