#ifndef PLAIN_ENGINE_PLAAPP_HPP
#define PLAIN_ENGINE_PLAAPP_HPP

#include "PLAObject.hpp"
#include "Object/Input/PLAInputType.hpp"
#include "Object/PLARendererType.hpp"
#include "Primitive/PLAVector.hpp"
#include "Primitive/PLAPoint.hpp"

#include "PLAState.hpp"
#include "PLAScene.hpp"
#include "PLAStage.hpp"
#include "Object/Timeline/PLATimeline.hpp"
#include "Actor/PLAActor.hpp"
#include "Agent/PLAAGTStage.hpp"

class PLARenderer;

class PLAApp final : public PLAObject
{
  static PLAApp _instance;

  //std::map<std::string, PLATimelineNode *> _subNodes = std::map<std::string, PLATimelineNode *>();
  PLATimeline _rootThread = PLATimeline(nullptr); /// Infinity node

  PLAUInt _frame = 0;

  PLAStage *_stage = nullptr;
  PLARenderer *_renderer = nullptr;
  PLAVec3 _contentScaleFactor = kPLAVec3Norm;

  PLAApp();

public:
  static const int kRefreshRate = 60;
  static const int kBaseScreenLength = 320;

  static PLAApp *Instance() { return &_instance; };
  static PLAStage *Stage() { return _instance._stage; };
  static PLAScene *Scene();
  static PLAActor *Actor(const PLAString &aName);

  /*static */void AddTimelineThread(PLATimeline *aThread);
  /*static */void UpdateTimelineThread();
  //*static */void RemoveTimelineThread(const PLATimeline *aThread);

  void PrintNodes() const;

  //-- このStage関連のメソッド、Stage()から呼べばいいので不要なのでは？
  /*
  static void InitStage();
  static void AddActor(PLAActor *aActor);
  static PLAActor *Actor(const PLAString &aName);
  //static void SetStageFunction(PLAAGTStage::FunctionCode aKey,
  //                             const std::function<void(PLAStage *)> &aFunc);
  static PLAVec3 GetStageSize();
  static void PrintStageActors();
  */
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

  const PLAVec3 &GetContentScaleFactor() { return _contentScaleFactor; }
};

#endif // PLAIN_ENGINE_PLAAPP
