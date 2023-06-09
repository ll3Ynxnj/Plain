#ifndef PLAIN_ENGINE_PLAOBJAPP_HPP
#define PLAIN_ENGINE_PLAOBJAPP_HPP

#include "PLAObject.hpp"
#include "Core/PLAInputType.hpp"
#include "Core/PLARendererType.hpp"
#include "Primitive/PLAPRMVector.hpp"
#include "Primitive/PLAPRMPoint.hpp"

#include "PLAOBJState.hpp"
#include "PLAOBJScene.hpp"
#include "PLAOBJStage.hpp"
#include "Object/Timeline/PLAOBJTimeline.hpp"
#include "Actor/PLAOBJActor.hpp"
#include "Agent/PLAAGTStage.hpp"

class PLAOBJRenderer;

class PLAOBJApp final : public PLAObject
{
  static PLAOBJApp _instance;

  //std::map<std::string, PLAOBJTimelineNode *> _subNodes = std::map<std::string, PLAOBJTimelineNode *>();
  PLAOBJTimeline _timeline = PLAOBJTimeline(nullptr); /// Infinity node

  PLAUInt _frame = 0;

  PLAOBJScene *_scene = nullptr;
  PLAOBJState *_state = nullptr;
  PLAOBJStage *_stage = nullptr;
  PLAOBJRenderer *_renderer = nullptr;
  PLAVec3f _contentScaleFactor = kPLAVec3fNorm;

  PLAOBJApp();

public:
  static const int kRefreshRate = 60;
  static const int kBaseScreenLength = 320;

  static PLAOBJApp *Instance() { return &_instance; };
  static PLAOBJState *State() { return _instance._state; };
  static PLAOBJStage *Stage() { return _instance._stage; };
  static PLAOBJScene *Scene() { return _instance._scene; };
  static PLAOBJActor *Actor(const PLAString &aName); // PLAOBJActor::Object(aName)があるので不要では？

  void AddTimelineThread(PLAOBJTimeline *aThread);
  void UpdateTimelineThread();
  //void RemoveTimelineThread(const PLAOBJTimeline *aThread);

  void PrintNodes() const;

  //--------------------------------------------------------------------------//

  static PLAInputSignalCode GetInputSignalCodeFromChar(const unsigned char aCharacter);

  ~PLAOBJApp();

  void Init(PLARendererType aType);
  void Reset();
  void Input(PLAInputDeviceType aDevice, PLAInputSignalCode aCode,
             PLAInputSignal aSignal, const PLAPoint &aPoint);
  void Update();
  void Render();

  void RefreshScreenSize(int aWidth, int aHeight);

  void PrintTimelineNodes() const;

  const PLAVec3f &GetContentScaleFactor() { return _contentScaleFactor; }
};

#endif // PLAIN_ENGINE_PLAOBJAPP
