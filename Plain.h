#ifndef PLAIN_ENGINE_PLAIN_HPP
#define PLAIN_ENGINE_PLAIN_HPP

#include "Agent/PLAAGTScene.hpp"
#include "Agent/PLAAGTState.hpp"
#include "Agent/PLAAGTModel.hpp"
#include "Agent/PLAAGTStage.hpp"
#include "Agent/PLAAGTActor.hpp"

#include "Core/PLARendererType.hpp"
#include "Core/PLAFunctionCode.hpp"

using PLAModel = PLAAGTModel;
using PLAActor = PLAAGTActor;

namespace Plain
{
  using Renderer = PLARendererType;

  void Init(PLARendererType aType);
  void Delete(const std::string &aName);

  void Add(const PLAAGTActor &aActor);
  void Add(const PLAAGTModel &aModel);

  void Push(const PLAAGTScene &aAgent);

  namespace Event
  {
    using Actor = PLAFunctionCode::Actor;
    using Stage = PLAFunctionCode::Stage;
    using Scene = PLAFunctionCode::Scene;
  };

  namespace Error
  {
    using Type = PLAErrorType;

    void Assert(const std::string &aMessage);
    void Expect(const std::string &aMessage);
  };

  namespace Print
  {
    void Objects();
    void Resources();
  };

  namespace State
  {
    PLAAGTState Assign();
  };

  namespace Stage
  {
    PLAAGTStage Assign();
    void SetFunction(Event::Stage aEventCode);
  };

  namespace Scene
  {
    PLAAGTScene Create();
    PLAAGTScene Create(const PLAString &aName);
    PLAAGTScene Assign(const PLAString &aName);
  };

  namespace Model
  {
    //using Agent = PLAAGTModel;
    PLAAGTModel Create();
    PLAAGTModel Create(const PLAString &aName);
    PLAAGTModel Assign(const PLAString &aName);
  };

  namespace Actor
  {
    //using Agent = PLAAGTActor;
    PLAAGTActor CreateRect(const PLAVec3f &aPivot,
                           const PLAColor &aColor,
                           const PLATransform &aTransform,
                           const PLARect &aRect);

    PLAAGTActor CreateRect(const PLAVec3f &aPivot,
                           const PLAColor &aColor,
                           const PLATransform &aTransform,
                           const PLARect &aRect,
                           const PLAColor &aFillColor);

    PLAAGTActor CreateRect(const PLAVec3f &aPivot,
                           const PLAColor &aColor,
                           const PLATransform &aTransform,
                           const PLARect &aRect,
                           const std::string &aImage,
                           const PLARect &aClip);

    PLAAGTActor CreateCircle(const PLAVec3f &aPivot,
                             const PLAColor &aColor,
                             const PLATransform &aTransform,
                             const PLACircle &aCircle);

    PLAAGTActor CreateCircle(const PLAVec3f &aPivot,
                             const PLAColor &aColor,
                             const PLATransform &aTransform,
                             const PLACircle &aCircle,
                             const PLAColor &aFillColor);

    PLAAGTActor CreateCircle(const PLAVec3f &aPivot,
                             const PLAColor &aColor,
                             const PLATransform &aTransform,
                             const PLACircle &aCircle,
                             const std::string &aImage,
                             const PLARect &aClip);

    PLAAGTActor CreateTile(const PLAVec2f &aOffset,
                           const std::string &aImageName,
                           const GRAVec2<PLASize> &aTileSize,
                           const GRAVec2<PLASize> &aChipSize,
                           const IPLATileLayerDataSource *aDataSource);

    PLAAGTActor Assign(const PLAString &aName);
  };
};

#endif //PLAIN_ENGINE_PLAIN_HPP
