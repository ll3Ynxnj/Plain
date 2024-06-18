#ifndef PLAIN_ENGINE_PLAIN_HPP
#define PLAIN_ENGINE_PLAIN_HPP

#include "plain/core/app/PLAApp.hpp"

#include "plain/core/agent/PLAAGTScene.hpp"
#include "plain/core/agent/PLAAGTState.hpp"
#include "plain/core/agent/PLAAGTModel.hpp"
#include "plain/core/agent/PLAAGTPhase.hpp"
#include "plain/core/agent/PLAAGTStage.hpp"
#include "plain/core/agent/actor/PLAAGTActor.hpp"
#include "plain/core/agent/actor/PLAAGTActorForRect.hpp"
#include "plain/core/agent/actor/PLAAGTActorForCircle.hpp"
#include "plain/core/agent/actor/PLAAGTActorForTile.hpp"
#include "plain/core/agent/PLAAGTTimeline.hpp"
#include "plain/core/agent/PLAAGTTimelineNode.hpp"
#include "plain/core/agent/PLAAGTMotion.hpp"
#include "plain/core/agent/PLAAGTMotionNode.hpp"
#include "plain/core/agent/PLAAGTImageClip.hpp"

#include "plain/core/PLARendererType.hpp"
#include "plain/core/PLAFunctionCode.hpp"

#include "plain/core/PLAErrorType.hpp"

#include "plain/core/primitive/PLAPrimitive.hpp"

#include "plain/core/object/layer/IPLATileLayerDataSource.hpp"
#include "plain/core/object/PLAOBJError.hpp"

using PLAModel = PLAAGTModel;
using PLAActor = PLAAGTActor;

/// \~japanese /////////////////////////////////////////////////////////////////
/// \brief 外部からのアクセスに利用する静的メソッド群です。内部からの利用は禁止します。内部からは各クラスに記述された静的メソッドを利用してください。
/// \~english /////////////////////////////////////////////////////////////////
/// \brief Static methods for external access. Internal access is prohibited. Use static methods described in each class.

namespace Plain
{
  using Renderer = PLARendererType;

  void Init(PLARendererType aType, PLAUInt aRefreshRate, PLAUInt aBaseScreenLength);
  //void Delete(const std::string &aName);

  PLAApp *App();

  namespace Event
  {
    using App = PLAFunctionCode::App;
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
    void PopPhase();
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
    void AddActor(const PLAString &aName);
    void RemoveActor(const PLAAGTActor &aActor);
    void RemoveActor(const PLAString &aName);
    PLAVec3f GetSize();
  };

  namespace Phase
  {
    //PLAAGTPhase Create();
    //PLAAGTPhase Create(const PLAString &aName);
    PLAAGTPhase CreateWithTag(PLAId aTag);
    PLAAGTPhase Assign(const PLAId aId);
    PLAAGTPhase Assign(const PLAString &aName);
    PLAAGTPhase AssignWithTag(PLAId aTag);
  };

  namespace Model
  {
    //using Agent = PLAAGTModel;
    PLAAGTModel Create();
    PLAAGTModel Create(const PLAString &aName);
    PLAAGTModel Assign(const PLAId aId);
    PLAAGTModel Assign(const PLAString &aName);
  };

  namespace Actor
  {
    //using Agent = Actor;
    PLAAGTActorForRect CreateRect(const PLAVec2f &aOrigin,
                                  const PLAVec2f &aSize,
                                  const PLAColor &aFillColor,
                                  const PLAString &aName = kPLAStrUndefined);
    PLAAGTActorForRect CreateRect(const PLAVec3f &aPivot,
                                  const PLATransform &aTransform,
                                  const PLARect &aRect,
                                  const PLAString &aName = kPLAStrUndefined);
    PLAAGTActorForRect CreateRect(const PLAVec3f &aPivot,
                                  const PLATransform &aTransform,
                                  const PLARect &aRect,
                                  const PLAColor &aFillColor,
                                  const PLAString &aName = kPLAStrUndefined);
    PLAAGTActorForRect CreateRect(const PLAVec3f &aPivot,
                                  const PLATransform &aTransform,
                                  const PLARect &aRect,
                                  const std::string &aImage,
                                  const PLARect &aClip,
                                  const PLAString &aName = kPLAStrUndefined);
    PLAAGTActorForCircle CreateCircle(const PLAVec2f &aOrigin,
                                      const PLAFloat aRadius,
                                      const PLAColor &aFillColor,
                                      const PLAString &aName = kPLAStrUndefined);
    PLAAGTActorForCircle CreateCircle(const PLAVec3f &aPivot,
                                      const PLATransform &aTransform,
                                      const PLACircle &aCircle,
                                      const PLAString &aName = kPLAStrUndefined);
    PLAAGTActorForCircle CreateCircle(const PLAVec3f &aPivot,
                                      const PLATransform &aTransform,
                                      const PLACircle &aCircle,
                                      const PLAColor &aFillColor,
                                      const PLAString &aName = kPLAStrUndefined);
    PLAAGTActorForCircle CreateCircle(const PLAVec3f &aPivot,
                                      const PLATransform &aTransform,
                                      const PLACircle &aCircle,
                                      const PLAString &aImage,
                                      const PLARect &aClip,
                                      const PLAString &aName = kPLAStrUndefined);
    PLAAGTActorForTile CreateTile(const PLAVec2f &aOffset,
                                  const PLAString &aImage,
                                  const GRAVec2<PLASize> &aTileSize,
                                  const GRAVec2<PLASize> &aChipSize,
                                  const IPLATileLayerDataSource *aDataSource,
                                  const PLAString &aName = kPLAStrUndefined);

    PLAAGTActor Assign(PLAId aId);
    PLAAGTActor Assign(const PLAString &aName);
    PLAAGTActor AssignWithTag(PLAId aTag);

    PLAAGTActorForRect AssignRect(PLAId aId);
    PLAAGTActorForRect AssignRect(const PLAString &aName);
    PLAAGTActorForRect AssignRectWithTag(PLAId aTag);

    PLAAGTActorForCircle AssignCircle(PLAId aId);
    PLAAGTActorForCircle AssignCircle(const PLAString &aName);
    PLAAGTActorForCircle AssignCircleWithTag(PLAId aTag);

    PLAAGTActorForTile AssignTile(PLAId aId);
    PLAAGTActorForTile AssignTile(const PLAString &aName);
    PLAAGTActorForTile AssignTileWithTag(PLAId aTag);
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
    PLAAGTMotion Assign(const PLAId aId);
    PLAAGTMotion Assign(const PLAString &aName);
  };

  namespace MotionNode
  {
    PLAAGTMotionNode Create();
    PLAAGTMotionNode Create(const PLAString &aName);
    PLAAGTMotionNode Assign(const PLAId &aId);
    PLAAGTMotionNode Assign(const PLAString &aName);

    PLAAGTMotionNode CreateColor(const PLAColor &aBegin, const PLAColor &aEnd,
                                 PLAEasing::Type aEasingType,
                                 PLATimeInterval aDuration);
    PLAAGTMotionNode CreateTranslation(const PLAVec3f &aBegin, const PLAVec3f &aEnd,
                                       PLAEasing::Type aEasingType,
                                       PLATimeInterval aDuration);
    PLAAGTMotionNode CreateRotation(const PLAVec3f &aBegin, const PLAVec3f &aEnd,
                                    PLAEasing::Type aEasingType,
                                    PLATimeInterval aDuration);
    PLAAGTMotionNode CreateScale(const PLAVec3f &aBegin, const PLAVec3f &aEnd,
                                 PLAEasing::Type aEasingType,
                                 PLATimeInterval aDuration);
  };

  namespace ImageClip
  {
    //PLAAGTImageClip Create(const PLAString &aImageName);
    PLAAGTImageClip Create(const PLAString &aImageName, const PLARect &aClip);
    PLAAGTImageClip Assign(const PLAId &aId);
    PLAAGTImageClip Assign(const std::string &aName);
  };

};

#endif //PLAIN_ENGINE_PLAIN_HPP
