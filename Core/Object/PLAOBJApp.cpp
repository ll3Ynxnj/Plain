#include "PLAOBJApp.hpp"
#include "Object/Input/PLAInputManager.hpp"
#include "PLAOBJRenderer.hpp"
#include "PLAOBJError.hpp"

PLAOBJApp PLAOBJApp::_instance = PLAOBJApp();

PLAOBJActor *PLAOBJApp::Actor(const PLAString &aName)
{
  return PLAOBJActor::Object(aName);
}

void PLAOBJApp::AddTimelineThread(PLAOBJTimeline *aThread)
{
  _rootThread.AddThread(aThread);
}

void PLAOBJApp::UpdateTimelineThread()
{
  _rootThread.Update();
}

/*
void PLAOBJApp::RemoveTimelineThread(const PLAOBJTimeline *aThread)
{
  _rootThread.
}
 */

void PLAOBJApp::PrintNodes() const
{
  GRA_PRINT("//-- void PLAOBJApp::PrintNodes() const ////////////////////////////////////////\n");
  GRA_PRINT(" LV :  STEPS / LENGTH | CURRENT | NAME                                         |\n");
  _rootThread.PrintNodes();
  GRA_PRINT("----:-----------------|---------|----------------------------------------------|\n");
  GRA_PRINT("////////////////////////////////////////////////////////////////////////////////\n");
}

PLAInputSignalCode PLAOBJApp::GetInputSignalCodeFromChar(unsigned char aCharacter)
{
  return PLAInput::GetCodeForKeyFromChar(aCharacter);
}

PLAOBJApp::PLAOBJApp() :
PLAObject(PLAObjectType::App)//, "== PLAOBJApp ==")
{

}

PLAOBJApp::~PLAOBJApp()
{
  if (_state) { delete _state; };
  _state = nullptr;
  if (_stage) { delete _stage; };
  _stage = nullptr;
  _renderer = nullptr;
}

void PLAOBJApp::Init(PLARendererType aRendererType)
{
  PLAOBJResource::Manager::Instance()->Init();
  _renderer = PLAOBJRenderer::Create(aRendererType);
  _renderer->Init();
  PLAOBJError::Manager::Instance()->Init();
  PLAOBJScene::Manager::Instance()->Init();
  _state = PLAOBJState::Create();
  _stage = PLAOBJStage::Create();
  _scene = PLAOBJScene::Create();
  PLAInputManager::Instance()->SetHandler(_stage);
}

void PLAOBJApp::Reset()
{
  PLAOBJError::Manager::Instance()->Reset();
}

void PLAOBJApp::Input(PLAInputDeviceType aDevice, PLAInputSignalCode aCode,
                      PLAInputSignal aSignal, const PLAPoint &aPoint)
{
  PLAInputManager::Instance()->Input(aDevice, aCode, aSignal, aPoint);
}

void PLAOBJApp::Update()
{
  PLAObject::Manager::Instance()->DeleteUnboundObjects();
  PLAInputManager::Instance()->Flush();
  UpdateTimelineThread();
  _scene->Update();
  _stage->Update();
  ++_frame;
}

void PLAOBJApp::Render()
{
  //GRA_PRINT("-- Render\n");
  _renderer->Clear();
  _renderer->Render(_stage->GetContext());
  _renderer->Flush();
}

void PLAOBJApp::RefreshScreenSize(int aWidth, int aHeight)
{
  PLAVec3f frameSize(aWidth, aHeight, 0);
  PLAVec3f stageSize(kBaseScreenLength);

  if (aWidth < aHeight) { stageSize.y *= PLAFloat(aHeight) / PLAFloat(aWidth ); }
  else if (aWidth > aHeight) { stageSize.x *= PLAFloat(aWidth ) / PLAFloat(aHeight); }

  _contentScaleFactor = PLAVec3f(frameSize.x / stageSize.x,
                                frameSize.y / stageSize.y,
                                frameSize.z / stageSize.z);

  _renderer->RefreshScreenSize(frameSize, stageSize);
  _stage->SetSize(stageSize);
}
