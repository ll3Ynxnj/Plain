// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "Core/App/PLAApp.hpp"
#include "Core/Object/Input/PLAInputManager.hpp"
#include "Core/Object/PLAOBJRenderer.hpp"
#include "Core/Object/PLAOBJError.hpp"

PLAApp PLAApp::_instance = PLAApp();

PLAOBJActor *PLAApp::Actor(const PLAString &aName)
{
  return PLAOBJActor::Object(aName);
}

void PLAApp::AddTimelineThread(PLAOBJTimeline *aThread)
{
  _timeline->AddThread(aThread);
}

void PLAApp::UpdateTimelineThread()
{
  _timeline->Update();
}

/*
void PLAApp::RemoveTimelineThread(const PLAOBJTimeline *aThread)
{
  _timeline.
}
 */

void PLAApp::PrintNodes() const
{
  GRA_PRINT("//-- void PLAApp::PrintNodes() const ////////////////////////////////////////\n");
  GRA_PRINT(" LV :  STEPS / LENGTH | CURRENT | NAME                                         |\n");
  _timeline->PrintNodes();
  GRA_PRINT("----:-----------------|---------|----------------------------------------------|\n");
  GRA_PRINT("////////////////////////////////////////////////////////////////////////////////\n");
}

PLAInputSignalCode PLAApp::GetInputSignalCodeFromChar(unsigned char aCharacter)
{
  return PLAInput::GetCodeForKeyFromChar(aCharacter);
}

///-----------------------------------------------------------------------------
/// PLAApp()
///
/// PLAOBJAppはSingletonなので、実体が静的オブジェクトとして生成される。
/// PLAObjectのコンストラクタ`PLAObject(PLAObjectType)1が静的変数であるkObjectNameUndefinedを使用している。
/// 翻訳単位の異なる静的オブジェクトのコンストラクタの実行順序は未定義であるため
/// ここではもうひとつのコンストラクタであるPLAObject(PLAObjectType, PLAString)を使用する。
///
/// PLAApp is a singleton, so the instance is created as a static object.
/// PLAObject's constructor `PLAObject(PLAObjectType)` uses a static variable `kObjectNameUndefined`.
/// The execution order of static object constructors in different translation units is undefined,
/// so here we use another constructor `PLAObject(PLAObjectType, PLAString)`.
///
///-----------------------------------------------------------------------------

PLAApp::PLAApp()// :
//PLAObject(PLAObjectType::App)//, "== PLAApp ==")
{

}

PLAApp::~PLAApp()
{
  if (_state) { delete _state; };
  _state = nullptr;
  if (_stage) { delete _stage; };
  _stage = nullptr;
  _renderer = nullptr;
}

void PLAApp::Init(PLARendererType aRendererType,
                  PLAInt aRefreshRate, PLAInt aBaseScreenLength)
{
  _refreshRate = aRefreshRate;
  _baseScreenLength = aBaseScreenLength;
  _timeline = PLAOBJTimeline::Create(nullptr, "PLAApp::Timeline");
  PLAOBJResource::Manager::Instance()->Init();
  _renderer = PLAOBJRenderer::Create(aRendererType);
  _renderer->Init();
  PLAOBJError::Manager::Instance()->Init();
  PLAOBJScene::Manager::Instance()->Init();
  _state = PLAOBJState::Create("PLAApp::State");
  _stage = PLAOBJStage::Create("PLAApp::Stage");
  _scene = PLAOBJScene::Create("PLAApp::Scene");
  PLAInputManager::Instance()->SetHandler(_stage);

  //this->RunFunction(PLAFunctionCode::App::OnInit);
}

void PLAApp::Reset()
{
  PLAOBJError::Manager::Instance()->Reset();
}

void PLAApp::Input(PLAInputDeviceType aDevice, PLAInputSignalCode aCode,
                   PLAInputSignal aSignal, const PLAPoint &aPoint)
{
  PLAInputManager::Instance()->Input(aDevice, aCode, aSignal, aPoint);
}

void PLAApp::Update()
{
  PLAObject::Manager::Instance()->DeleteUnboundObjects();
  PLAInputManager::Instance()->Flush();
  UpdateTimelineThread();
  //_scene->Update();
  _stage->Update();
  this->RunFunction(PLAFunctionCode::App::OnUpdate);
  ++_frame;
}

void PLAApp::Render()
{
  //GRA_PRINT("-- Render\n");
  _renderer->Clear();
  _renderer->Render(_stage->GetContext());
  _renderer->Flush();
}

void PLAApp::RefreshScreenSize(int aWidth, int aHeight)
{
  PLAVec3f frameSize(aWidth, aHeight, 0);
  PLAVec3f stageSize(_baseScreenLength);

  if (aWidth < aHeight) { stageSize.y *= PLAFloat(aHeight) / PLAFloat(aWidth ); }
  else if (aWidth > aHeight) { stageSize.x *= PLAFloat(aWidth ) / PLAFloat(aHeight); }

  _contentScaleFactor = PLAVec3f(frameSize.x / stageSize.x,
                                 frameSize.y / stageSize.y,
                                 frameSize.z / stageSize.z);

  _renderer->RefreshScreenSize(frameSize, stageSize);
  _stage->SetSize(stageSize);
}

void PLAApp::SetFunction(PLAFunctionCode::App aKey,
                         const std::function<void(const PLAApp *)> &aFunc)
{
  _functor.SetFunction(aKey, aFunc);
}

void PLAApp::PrintTimelineNodes() const {
  _timeline->PrintNodes();
}

void PLAApp::RunFunction(PLAFunctionCode::App aKey)
{
  _functor.RunFunction(aKey, this);
}
