#ifndef PLAIN_ENGINE_PLAOBJAPP_HPP
#define PLAIN_ENGINE_PLAOBJAPP_HPP

#include "PLAObject.hpp"
#include "Object/Input/PLAInputType.hpp"
#include "Object/PLARendererType.hpp"
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
  PLAOBJTimeline _rootThread = PLAOBJTimeline(nullptr); /// Infinity node

  PLAUInt _frame = 0;

  PLAOBJStage *_stage = nullptr;
  PLAOBJRenderer *_renderer = nullptr;
  PLAVec3 _contentScaleFactor = kPLAVec3Norm;

  PLAOBJApp();

public:
  static const int kRefreshRate = 60;
  static const int kBaseScreenLength = 320;

  static PLAOBJApp *Instance() { return &_instance; };
  static PLAOBJStage *Stage() { return _instance._stage; };
  static PLAOBJScene *Scene();
  static PLAOBJActor *Actor(const PLAString &aName);

  /*static */void AddTimelineThread(PLAOBJTimeline *aThread);
  /*static */void UpdateTimelineThread();
  //*static */void RemoveTimelineThread(const PLAOBJTimeline *aThread);

  void PrintNodes() const;

  //-- このStage関連のメソッド、Stage()から呼べばいいので不要なのでは？
  /*
  static void InitStage();
  static void AddActor(PLAOBJActor *aActor);
  static PLAOBJActor *Actor(const PLAString &aName);
  //static void SetStageFunction(PLAAGTStage::FunctionCode aKey,
  //                             const std::function<void(PLAOBJStage *)> &aFunc);
  static PLAVec3 GetStageSize();
  static void PrintStageActors();
  */
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

  const PLAVec3 &GetContentScaleFactor() { return _contentScaleFactor; }
};

#endif // PLAIN_ENGINE_PLAOBJAPP
