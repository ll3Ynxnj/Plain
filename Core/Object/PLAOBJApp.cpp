#include "PLAOBJApp.hpp"
#include "Object/Input/PLAInputManager.hpp"
#include "PLAOBJRenderer.hpp"
#include "PLAOBJError.hpp"

PLAOBJApp PLAOBJApp::_instance = PLAOBJApp();

PLAOBJScene *PLAOBJApp::Scene()
{
  return PLAOBJScene::Manager::Instance()->RefCurrentScene();
}

PLAOBJActor *PLAOBJApp::Actor(const PLAString &aName)
{
  PLAObject *object = PLAObject::Object(aName);
  if (object && object->GetObjectType() == PLAObjectType::Actor)
  { return static_cast<PLAOBJActor *>(object); }
  return nullptr;
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
  GRA_PRINT(" LV :  STEPS / LENGTH | CURRENT | NAME                             |\n");
  _rootThread.PrintNodes();
  GRA_PRINT("----:-----------------|---------|----------------------------------|\n");
}

/*
void PLAOBJApp::InitStage()
{
  _instance._stage->Init();
}

void PLAOBJApp::AddActor(PLAOBJActor *aActor)
{
  _instance._stage->AddActor(aActor);
  PLAOBJScene::Manager::Instance()->RefCurrentScene()->AddActor(aActor);
}

PLAVec3 PLAOBJApp::GetStageSize()
{
  _instance._stage->GetSize();
}
*/

/*
void PLAOBJApp::SetStageFunction(PLAOBJStage::FunctionCode aKey,
                             const std::function<void(PLAOBJStage *)> &aFunc)
{
  _instance._stage->SetFunction(aKey, aFunc);
}
 */

/*
void PLAOBJApp::PrintStageActors()
{
  _instance._stage->PrintActors();
}
*/

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
  if (_stage) { delete _stage; };
  _stage = nullptr;
  _renderer = nullptr;
}

void PLAOBJApp::Init(PLARendererType aRendererType)
{
  _renderer = PLAOBJRenderer::Create(aRendererType);
  _renderer->Init();
  PLAOBJError::Manager::Instance()->Init();
  PLAOBJScene::Manager::Instance()->Init();
  _stage = PLAOBJStage::Create();
  _stage->PrintActors();
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

void PLAOBJApp::Render()
{
  //GRA_PRINT("-- Render\n");
  _renderer->Clear();
  _renderer->Render(_stage->GetContext());
  _renderer->Flush();
}

void PLAOBJApp::RefreshScreenSize(int aWidth, int aHeight)
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
