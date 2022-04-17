#ifndef PLAIN_ENGINE_PLAIN_HPP
#define PLAIN_ENGINE_PLAIN_HPP

#include "Grain/Grain.h"
#include "Core/Type/PLAType.hpp"
#include "Core/Layer/IPLALYRTileDataSource.hpp"

#include "Core/Class/PLARendererType.hpp"

#include "Core/Class/PLAObject.hpp"
#include "Core/Agent/PLAAGTScene.hpp"

class Plain {
public:
  using Renderer = PLARendererType;
  static void Init(PLARendererType aType);

  class Stage {
  public:
  };

  class State {
  public:
  };

  class Scene {
  public:
    static const PLAAGTScene *Create();
    static void Push(const PLAAGTScene *aCreate);
  };

private:
  static const PLAObject *GetObject(const PLAAgent *aAgent);
};

#endif //PLAIN_ENGINE_PLAIN_HPP
