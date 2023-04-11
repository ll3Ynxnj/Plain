#ifndef PLAIN_ENGINE_PLAIN_HPP
#define PLAIN_ENGINE_PLAIN_HPP

#include "Grain/Grain.h"

#include "Primitive/PLAPRMType.hpp"
#include "Object/Layer/IPLATileLayerDataSource.hpp"

#include "Object/PLARendererType.hpp"
#include "Object/PLAOBJError.hpp"

#include "Object/PLAObject.hpp"
#include "Object/Agent/PLAAGTScene.hpp"
#include "Object/Agent/PLAAGTState.hpp"
#include "Object/Agent/PLAAGTModel.hpp"
#include "Object/Agent/PLAAGTStage.hpp"
#include "Object/Agent/PLAAGTActor.hpp"

class Plain {
public:
  using Renderer = PLARendererType;

  static void Init(PLARendererType aType);
  static void Delete(const std::string &aName);
  static PLAAGTState *State();
  static PLAAGTStage *Stage();

  class Error {
    static void Assert(const std::string &aMessage);
    static void Expect(const std::string &aMessage);
  };

  class State {
  public:
    static const void AddModel(PLAAGTModel *aModel);
  };

  class Stage {
  public:
    static const void AddActor(PLAAGTActor *aActor);
    /*
    void AddListener(GRAOBJListener<PLAAGTStage, PLAAGTStage::FunctionCode> *aListener);
    void RemoveListener(GRAOBJListener<PLAAGTStage, PLAAGTStage::FunctionCode> *aListener);
    void SetFunction(PLAAGTStage::FunctionCode aKey,
                     const std::function<void(PLAAGTStage *)> &aFunc);

    void AddActor(PLAOBJActor *aActor);
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
    static PLAAGTModel *Create();
    static PLAAGTModel *Create(const PLAString &aName);
    static PLAAGTModel *Assign(const PLAString &aName);
  };

  class Actor {
  public:
    static PLAAGTActor *CreateRect(const PLAVec3f &aPivot,
                                   const PLAColor &aColor,
                                   const PLATransform &aTransform,
                                   const PLARect &aRect);
    static PLAAGTActor *CreateRect(const PLAVec3f &aPivot,
                                   const PLAColor &aColor,
                                   const PLATransform &aTransform,
                                   const PLARect &aRect,
                                   const PLAColor &aFillColor);
    static PLAAGTActor *CreateRect(const PLAVec3f &aPivot,
                                   const PLAColor &aColor,
                                   const PLATransform &aTransform,
                                   const PLARect &aRect,
                                   const std::string &aImage,
                                   const PLARect &aClip);
    static PLAAGTActor *CreateCircle(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLACircle &aCircle);
    static PLAAGTActor *CreateCircle(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLACircle &aCircle,
                                     const PLAColor &aFillColor);
    static PLAAGTActor *CreateCircle(const PLAVec3f &aPivot,
                                     const PLAColor &aColor,
                                     const PLATransform &aTransform,
                                     const PLACircle &aCircle,
                                     const std::string &aImage,
                                     const PLARect &aClip);
    static PLAAGTActor *CreateTile(const PLAVec2f &aOffset,
                                   const std::string &aImageName,
                                   const GRAVec2<PLASize> &aTileSize,
                                   const GRAVec2<PLASize> &aChipSize,
                                   const IPLATileLayerDataSource *aDataSource);
    static PLAAGTActor *Assign(const PLAString &aName);
  };

private:
  static const PLAObject *Object(const PLAOBJAgent *aAgent);
  static PLAOBJAgent *Assign(const PLAString &aName);
};

#endif //PLAIN_ENGINE_PLAIN_HPP
