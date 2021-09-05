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
#include "PLANode.hpp"
#include "Actor/PLAActor.hpp"

class PLARenderer;

class PLAApp final : public PLAObject
{
  static PLAApp _instance;

  PLAStage *_stage = nullptr;
  PLARenderer *_renderer = nullptr;
  PLAVec3 _contentScaleFactor = kPLAVec3Norm;
  PLANode _node = PLANode(kPLAIntUndefined);

  PLAApp();

public:
  static const int kBaseScreenLength = 320;

  static PLAApp *GetInstance() { return &_instance; };
  static PLAStage *Stage() { return _instance._stage; };
  static PLAScene *Scene();

  //-- このStage関連のメソッド、Stage()から呼べばいいので不要なのでは？
  static void InitStage();
  static void AddActor(PLAActor *actor);
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
