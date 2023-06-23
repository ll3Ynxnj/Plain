#ifndef PLAIN_ENGINE_PLAIN_HPP
#define PLAIN_ENGINE_PLAIN_HPP

#include "Agent/PLAAGTScene.hpp"
#include "Agent/PLAAGTState.hpp"
#include "Agent/PLAAGTModel.hpp"
#include "Agent/PLAAGTPhase.hpp"
#include "Agent/PLAAGTStage.hpp"
#include "Agent/PLAAGTActor.hpp"
#include "Agent/PLAAGTTimeline.hpp"
#include "Agent/PLAAGTTimelineNode.hpp"
#include "Agent/PLAAGTMotion.hpp"
#include "Agent/PLAAGTMotionNode.hpp"

#include "Core/PLARendererType.hpp"
#include "Core/PLAFunctionCode.hpp"

#include "Core/PLAErrorType.hpp"

#include "Primitive/PLAPrimitive.hpp"

#include "Object/Layer/IPLATileLayerDataSource.hpp"
#include "Object/PLAOBJError.hpp"

using PLAModel = PLAAGTModel;
using PLAActor = PLAAGTActor;

namespace Plain
{
  using Renderer = PLARendererType;

  void Init(PLARendererType aType);
  void Delete(const std::string &aName);

  namespace Event
  {
    using Actor = PLAFunctionCode::Actor;
    using Phase = PLAFunctionCode::Phase;
    using Stage = PLAFunctionCode::Stage;
    using Scene = PLAFunctionCode::Scene;
    using TimeLineNode = PLAFunctionCode::TimelineNode;
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
    void Phases();
    void Models();
    void Actors();
    void TimelineNodes();
  };

  namespace Scene
  {
    PLAAGTScene Assign();
    void PushPhase(const PLAAGTPhase &aPhase);
  };

  namespace State
  {
    PLAAGTState Assign();
    void AddModel(const PLAAGTModel &aModel);
  };

  namespace Stage
  {
    PLAAGTStage Assign();
    void AddActor(const PLAAGTActor &aActor);
  };

  namespace Phase
  {
    PLAAGTPhase Create();
    PLAAGTPhase Create(const PLAString &aName);
    PLAAGTPhase Assign(const PLAString &aName);
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
                           const PLATransform &aTransform,
                           const PLARect &aRect);
    PLAAGTActor CreateRect(const PLAVec3f &aPivot,
                           const PLATransform &aTransform,
                           const PLARect &aRect,
                           const PLAColor &aFillColor);
    PLAAGTActor CreateRect(const PLAVec3f &aPivot,
                           const PLATransform &aTransform,
                           const PLARect &aRect,
                           const std::string &aImage,
                           const PLARect &aClip);
    PLAAGTActor CreateCircle(const PLAVec3f &aPivot,
                             const PLATransform &aTransform,
                             const PLACircle &aCircle);
    PLAAGTActor CreateCircle(const PLAVec3f &aPivot,
                             const PLATransform &aTransform,
                             const PLACircle &aCircle,
                             const PLAColor &aFillColor);
    PLAAGTActor CreateCircle(const PLAVec3f &aPivot,
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

  /*
  namespace Timeline
  {
    PLAAGTTimeline Create(const PLAAGTTimeline &aParent);
    PLAAGTTimeline Create(const PLAString &aName);
    PLAAGTTimeline Assign(const PLAString &aName);
  };

  namespace TimelineNode
  {
    PLAAGTTimelineNode Create();
    PLAAGTTimelineNode Create(const PLAString &aName);
    PLAAGTTimelineNode Assign(const PLAString &aName);
  };
   */

  namespace Motion
  {
    PLAAGTMotion Create();
    PLAAGTMotion Create(const PLAString &aName);
    PLAAGTMotion Assign(const PLAString &aName);
  };

  namespace MotionNode
  {
    PLAAGTMotionNode Create();
    PLAAGTMotionNode Create(const PLAString &aName);
    PLAAGTMotionNode Assign(const PLAString &aName);

    PLAAGTMotionNode CreateColor(const PLAColor &aBegin, const PLAColor &aEnd,
                                 PLATimeInterval aDuration);
    PLAAGTMotionNode CreateTranslation(const PLAVec3f &aBegin, const PLAVec3f &aEnd,
                                       PLATimeInterval aDuration);
    PLAAGTMotionNode CreateRotation(const PLAVec3f &aBegin, const PLAVec3f &aEnd,
                                    PLATimeInterval aDuration);
    PLAAGTMotionNode CreateScale(const PLAVec3f &aBegin, const PLAVec3f &aEnd,
                                         PLATimeInterval aDuration);
  };

};

#endif //PLAIN_ENGINE_PLAIN_HPP
