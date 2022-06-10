#include "PLAApp.hpp"
#include "Object/Input/PLAInputManager.hpp"
#include "PLARenderer.hpp"
#include "PLAError.hpp"

PLAApp PLAApp::_instance = PLAApp();

PLAScene *PLAApp::Scene()
{
  return PLAScene::Manager::Instance()->RefCurrentScene();
}

PLAActor *PLAApp::Actor(const PLAString &aName)
{
  PLAObject *object = PLAObject::Object(aName);
  if (object && object->GetObjectType() == PLAObjectType::Actor)
  { return static_cast<PLAActor *>(object); }
  return nullptr;
}

void PLAApp::AddTimelineThread(PLATimeline *aThread)
{
  _rootThread.AddThread(aThread);
}

void PLAApp::UpdateTimelineThread()
{
  _rootThread.Update();
}

/*
void PLAApp::RemoveTimelineThread(const PLATimeline *aThread)
{
  _rootThread.
}
 */

void PLAApp::PrintNodes() const
{
  GRA_PRINT(" LV :  STEPS / LENGTH | CURRENT | NAME                             |\n");
  _rootThread.PrintNodes();
  GRA_PRINT("----:-----------------|---------|----------------------------------|\n");
}

/*
void PLAApp::InitStage()
{
  _instance._stage->Init();
}

void PLAApp::AddActor(PLAActor *aActor)
{
  _instance._stage->AddActor(aActor);
  PLAScene::Manager::Instance()->RefCurrentScene()->AddActor(aActor);
}

PLAVec3 PLAApp::GetStageSize()
{
  _instance._stage->GetSize();
}
*/

/*
void PLAApp::SetStageFunction(PLAStage::FunctionCode aKey,
                             const std::function<void(PLAStage *)> &aFunc)
{
  _instance._stage->SetFunction(aKey, aFunc);
}
 */

/*
void PLAApp::PrintStageActors()
{
  _instance._stage->PrintActors();
}
*/

PLAInputSignalCode PLAApp::GetInputSignalCodeFromChar(unsigned char aCharacter)
{
  return PLAInput::GetCodeForKeyFromChar(aCharacter);
}

PLAApp::PLAApp() :
PLAObject(PLAObjectType::App)//, "== PLAApp ==")
{

}

PLAApp::~PLAApp()
{
  if (_stage) { delete _stage; };
  _stage = nullptr;
  _renderer = nullptr;
}

void PLAApp::Init(PLARendererType aRendererType)
{
  _renderer = PLARenderer::Create(aRendererType);
  _renderer->Init();
  PLAError::Manager::Instance()->Init();
  PLAScene::Manager::Instance()->Init();
  _stage = PLAStage::Create();
  _stage->PrintActors();
  PLAInputManager::Instance()->SetHandler(_stage);
}

void PLAApp::Reset()
{
  PLAError::Manager::Instance()->Reset();
}

void PLAApp::Input(PLAInputDeviceType aDevice, PLAInputSignalCode aCode,
                   PLAInputSignal aSignal, const PLAPoint &aPoint)
{
  PLAInputManager::Instance()->Input(aDevice, aCode, aSignal, aPoint);
}

void PLAApp::Update()
{
  GRA_PRINT("-- Update -- _frame: %8d\n", _frame);
  PLAObject::Manager::Instance()->DeleteUnboundObjects();
  PLAInputManager::Instance()->Flush();
  UpdateTimelineThread();
  _stage->Update();
  _stage->PrintActors();
  PLAObject::Manager::Instance()->PrintObjects();
  this->PrintNodes();
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
  PLAVec3 frameSize(aWidth, aHeight, 0);
  PLAVec3 stageSize(kBaseScreenLength);

  if (aWidth < aHeight) { stageSize.y *= PLAFloat(aHeight) / PLAFloat(aWidth ); }
  else if (aWidth > aHeight) { stageSize.x *= PLAFloat(aWidth ) / PLAFloat(aHeight); }

  _contentScaleFactor = PLAVec3(frameSize.x / stageSize.x,
                                frameSize.y / stageSize.y,
                                frameSize.z / stageSize.z);

  _renderer->RefreshScreenSize(frameSize, stageSize);
  _stage->SetSize(stageSize);
}
