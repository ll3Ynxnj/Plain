#ifndef PLAIN_ENGINE_PLAIN_HPP
#define PLAIN_ENGINE_PLAIN_HPP

#include "Core/App/PLAApp.hpp"

#include "Core/Agent/PLAAGTScene.hpp"
#include "Core/Agent/PLAAGTState.hpp"
#include "Core/Agent/PLAAGTModel.hpp"
#include "Core/Agent/PLAAGTPhase.hpp"
#include "Core/Agent/PLAAGTStage.hpp"
#include "Core/Agent/Actor/PLAAGTActor.hpp"
#include "Core/Agent/Actor/PLAAGTActorForRect.hpp"
#include "Core/Agent/Actor/PLAAGTActorForCircle.hpp"
#include "Core/Agent/Actor/PLAAGTActorForTile.hpp"
#include "Core/Agent/PLAAGTTimeline.hpp"
#include "Core/Agent/PLAAGTTimelineNode.hpp"
#include "Core/Agent/PLAAGTMotion.hpp"
#include "Core/Agent/PLAAGTMotionNode.hpp"
#include "Core/Agent/PLAAGTImageClip.hpp"

#include "Core/PLARendererType.hpp"
#include "Core/PLAFunctionCode.hpp"

#include "Core/PLAErrorType.hpp"

#include "Core/Primitive/PLAPrimitive.hpp"

#include "Core/Object/Layer/IPLATileLayerDataSource.hpp"
#include "Core/Object/PLAOBJError.hpp"

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
                                  const PLAColor &aFillColor);
    PLAAGTActorForRect CreateRect(const PLAVec3f &aPivot,
                                  const PLATransform &aTransform,
                                  const PLARect &aRect);
    PLAAGTActorForRect CreateRect(const PLAVec3f &aPivot,
                                  const PLATransform &aTransform,
                                  const PLARect &aRect,
                                  const PLAColor &aFillColor);
    PLAAGTActorForRect CreateRect(const PLAVec3f &aPivot,
                                  const PLATransform &aTransform,
                                  const PLARect &aRect,
                                  const std::string &aImage,
                                  const PLARect &aClip);
    PLAAGTActorForCircle CreateCircle(const PLAVec2f &aOrigin,
                                      const PLAFloat aRadius,
                                      const PLAColor &aFillColor);
    PLAAGTActorForCircle CreateCircle(const PLAVec3f &aPivot,
                                      const PLATransform &aTransform,
                                      const PLACircle &aCircle);
    PLAAGTActorForCircle CreateCircle(const PLAVec3f &aPivot,
                                      const PLATransform &aTransform,
                                      const PLACircle &aCircle,
                                      const PLAColor &aFillColor);
    PLAAGTActorForCircle CreateCircle(const PLAVec3f &aPivot,
                                      const PLATransform &aTransform,
                                      const PLACircle &aCircle,
                                      const std::string &aImage,
                                      const PLARect &aClip);
    PLAAGTActorForTile CreateTile(const PLAVec2f &aOffset,
                                  const std::string &aImageName,
                                  const GRAVec2<PLASize> &aTileSize,
                                  const GRAVec2<PLASize> &aChipSize,
                                  const IPLATileLayerDataSource *aDataSource);

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
