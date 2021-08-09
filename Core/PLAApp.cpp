#include "PLAApp.hpp"
#include "Core/Input/PLAInput.hpp"
#include "PLARenderer.hpp"
#include "PLAError.hpp"

PLAApp PLAApp::_instance = PLAApp();

PLAScene *PLAApp::Scene()
{
  return PLAScene::Manager::Instance()->RefCurrentScene();
}

void PLAApp::InitStage()
{
  _instance._stage->Init();
}

void PLAApp::AddActor(PLAActor *aActor)
{
  _instance._stage->AddActor(aActor);
  PLAScene::Manager::Instance()->RefCurrentScene()->AddActor(aActor);
}

PLAActor *PLAApp::Actor(const std::string &aKey)
{
  PLAObject *object = PLAObject::Manager::Object(aKey);
  if (object && object->GetObjectType() == PLAObjectType::Actor)
  { return static_cast<PLAActor *>(object); }
  return nullptr;
}

PLAVec3 PLAApp::GetStageSize()
{
  _instance._stage->GetSize();
}

void PLAApp::SetStageFunction(PLAStage::FunctionCode aKey,
                             const std::function<void(PLAStage *)> &aFunc)
{
  _instance._stage->SetFunction(aKey, aFunc);
}

void PLAApp::PrintStageActors()
{
  _instance._stage->PrintActors();
}

PLAInputCode PLAApp::GetInputCodeFromChar(unsigned char aCharacter)
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

void PLAApp::Init(PLARenderer *aRenderer)
{
  _renderer = aRenderer;
  _renderer->Init();
  PLAError::Manager::GetInstance()->Init();
  PLAScene::Manager::Instance()->Init();
  _stage = PLAStage::Create();
  //PLA_ERROR_ISSUE(PLAErrorType::Assert, "[%s] : %d %x %p", "TEST", 0, 1, this);
}

void PLAApp::Reset()
{
  PLAError::Manager::GetInstance()->Reset();
}

void PLAApp::Input(PLAInputDeviceType aDevice, PLAInputCode aCode,
                   PLAInputSignal aSignal, const PLAPoint &aPoint)
{
  PLAInputManager::GetInstance()->Input(aDevice, aCode, aSignal, aPoint);
}

void PLAApp::Update()
{
  //GRA_PRINT("-- Update\n");
  _stage->Update();
  PLAInputManager::GetInstance()->Flush();
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
