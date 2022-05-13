#ifndef PLAIN_ENGINE_PLAIN_HPP
#define PLAIN_ENGINE_PLAIN_HPP

#include "Grain/Grain.h"
#include "Core/Type/PLAType.hpp"
#include "Core/Layer/IPLALYRTileDataSource.hpp"

#include "Core/Class/PLARendererType.hpp"

#include "Core/Class/PLAObject.hpp"
#include "Core/Agent/PLAAGTStage.hpp"
#include "Core/Agent/PLAAGTScene.hpp"
#include "Core/Agent/PLAAGTActor.hpp"

class Plain {
public:
  using Renderer = PLARendererType;
  static void Init(PLARendererType aType);
  static void Delete(const std::string &aName);
  static PLAAGTStage *Stage();

  class State {
  public:
    //static const void AddModel(PLAAGTModel *aModel);
  };

  class Stage {
  public:
    static const void AddActor(PLAAGTActor *aActor);
    /*
    void AddListener(GRAListener<PLAAGTStage, PLAAGTStage::FunctionCode> *aListener);
    void RemoveListener(GRAListener<PLAAGTStage, PLAAGTStage::FunctionCode> *aListener);
    void SetFunction(PLAAGTStage::FunctionCode aKey,
                     const std::function<void(PLAAGTStage *)> &aFunc);

    void AddActor(PLAActor *aActor);
    void PrintActors() const;
     */
  };

  class Scene {
  public:
    static PLAAGTScene *Create();
    static PLAAGTScene *Create(const PLAString &aName);
    static PLAAGTScene *Assign(const PLAString &aName);
    static void Push(const PLAAGTScene *aCreate);
  };

  class Model {
  public:
    //static const PLAAGTModel *Model();
  };

  class Actor {
  public:
    static PLAAGTActor *CreateRect(const PLAVec3 &aPivot,
                                   const PLAColor &aColor,
                                   const PLATransform &aTransform,
                                   const PLARect &aRect);
    static PLAAGTActor *CreateRect(const PLAVec3 &aPivot,
                                   const PLAColor &aColor,
                                   const PLATransform &aTransform,
                                   const PLARect &aRect,
                                   const PLAColor &aFillColor);
    static PLAAGTActor *CreateRect(const PLAVec3 &aPivot,
                                   const PLAColor &aColor,
                                   const PLATransform &aTransform,
                                   const PLARect &aRect,
                                   const std::string &aImage,
                                   const PLARect &aClip);
    static PLAAGTActor *CreateCircle(const PLAVec3 &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLACircle &aCircle);
    static PLAAGTActor *CreateCircle(const PLAVec3 &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLACircle &aCircle,
                                     const PLAColor &aFillColor);
    static PLAAGTActor *CreateCircle(const PLAVec3 &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLACircle &aCircle,
                                     const std::string &aImage,
                                     const PLARect &aClip);
    static PLAAGTActor *CreateTile(const PLAVec2 &aOffset,
                                   const std::string &aImageName,
                                   const GRAVec2<PLASize> &aTileSize,
                                   const GRAVec2<PLASize> &aChipSize,
                                   const IPLALYRTileDataSource *aDataSource);
    static PLAAGTActor *Assign(const PLAString &aName);
  };

private:
  static const PLAObject *Object(const PLAAgent *aAgent);
  static PLAAgent *Assign(const PLAString &aName);
};

#endif //PLAIN_ENGINE_PLAIN_HPP
