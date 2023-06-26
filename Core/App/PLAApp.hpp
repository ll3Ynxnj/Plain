// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAOBJAPP_HPP
#define PLAIN_ENGINE_PLAOBJAPP_HPP

#include "Object/PLAObject.hpp"

#include "PLAInputType.hpp"
#include "PLARendererType.hpp"

#include "Primitive/PLAPRMVector.hpp"
#include "Primitive/PLAPRMPoint.hpp"

#include "Object/PLAOBJState.hpp"
#include "Object/PLAOBJScene.hpp"
#include "Object/PLAOBJStage.hpp"
#include "Object/Timeline/PLAOBJTimeline.hpp"
#include "Object/Actor/PLAOBJActor.hpp"

#include "Agent/PLAAGTStage.hpp"

class PLAOBJRenderer;

class PLAApp// final : public PLAObject
{
  static PLAApp _instance;

  //std::map<std::string, PLAOBJTimelineNode *> _subNodes = std::map<std::string, PLAOBJTimelineNode *>();
  PLAOBJTimeline *_timeline = nullptr;//PLAOBJTimeline(nullptr); /// Infinity node

  PLAUInt _frame = 0;

  PLAOBJScene *_scene = nullptr;
  PLAOBJState *_state = nullptr;
  PLAOBJStage *_stage = nullptr;
  PLAOBJRenderer *_renderer = nullptr;
  PLAVec3f _contentScaleFactor = kPLAVec3fNorm;

public:
  using Functor = GRAOBJFunctor<const PLAApp *, PLAFunctionCode::App>;

private:
  Functor _functor = Functor();

private:
  PLAApp();

public:
  static const int kRefreshRate = 60;
  static const int kBaseScreenLength = 320;

  static PLAApp *Instance() { return &_instance; };
  static PLAOBJState *State() { return _instance._state; };
  static PLAOBJStage *Stage() { return _instance._stage; };
  static PLAOBJScene *Scene() { return _instance._scene; };
  static PLAOBJActor *Actor(const PLAString &aName); // PLAOBJActor::Object(aName)があるので不要では？

  void AddTimelineThread(PLAOBJTimeline *aThread);
  void UpdateTimelineThread();
  //void RemoveTimelineThread(const PLAOBJTimeline *aThread);

  void SetFunction(PLAFunctionCode::App aKey,
                   const std::function<void(const PLAApp *)> &aFunc);

  void PrintNodes() const;

  //--------------------------------------------------------------------------//

  static PLAInputSignalCode GetInputSignalCodeFromChar(const unsigned char aCharacter);

  ~PLAApp();

  void Init(PLARendererType aType);
  void Reset();
  void Input(PLAInputDeviceType aDevice, PLAInputSignalCode aCode,
             PLAInputSignal aSignal, const PLAPoint &aPoint);
  void Update();
  void Render();

  void RefreshScreenSize(int aWidth, int aHeight);

  void PrintTimelineNodes() const;

  const PLAVec3f &GetContentScaleFactor() { return _contentScaleFactor; }

private:
  void RunFunction(PLAFunctionCode::App aKey);
};

#endif // PLAIN_ENGINE_PLAOBJAPP
