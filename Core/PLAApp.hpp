#ifndef PLAIN_ENGINE_PLAAPP_HPP
#define PLAIN_ENGINE_PLAAPP_HPP

#include "PLAObject.hpp"
#include "Core/Input/PLAInputType.hpp"
#include "PLARendererType.hpp"
#include "Type/PLAVector.hpp"
#include "Type/PLAPoint.hpp"

#include "PLAState.hpp"
#include "PLAScene.hpp"
#include "PLAStage.hpp"
#include "Timeline/PLATimelineThread.hpp"
#include "Actor/PLAActor.hpp"

class PLARenderer;

class PLAApp final : public PLAObject
{
  static PLAApp _instance;

  //std::map<std::string, PLATimelineNode *> _subNodes = std::map<std::string, PLATimelineNode *>();
  PLATimelineThread _nodeThread = PLATimelineThread(nullptr); /// Infinity node

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

  /*static */void AddNodeThread(PLATimelineThread *aThread);
  /*static */void UpdateNodeThread();
  //*static */void RemoveNode(const PLATimelineNode *aNode);

  void PrintNodes() const;

  //-- このStage関連のメソッド、Stage()から呼べばいいので不要なのでは？
  static void InitStage();
  static void AddActor(PLAActor *aActor);
  static PLAActor *Actor(const std::string &aKey);
  static void SetStageFunction(PLAStage::FunctionCode aKey,
                               const std::function<void(PLAStage *)> &aFunc);
  static PLAVec3 GetStageSize();
  static void PrintStageActors();
  //--------------------------------------------------------------------------//

  static PLAInputSignalCode GetInputSignalCodeFromChar(const unsigned char aCharacter);

  ~PLAApp();

  void Init(PLARenderer *aType);
  void Reset();
  void Input(PLAInputDeviceType aDevice, PLAInputSignalCode aCode,
             PLAInputSignal aSignal, const PLAPoint &aPoint);
  void Update();
  void Render();

  void RefreshScreenSize(int aWidth, int aHeight);

  const PLAVec3 &GetContentScaleFactor() { return _contentScaleFactor; }
};

#endif // PLAIN_ENGINE_PLAAPP
