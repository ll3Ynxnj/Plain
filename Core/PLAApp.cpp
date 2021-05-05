#include "PLAApp.hpp"
#include "PLAInput.hpp"
#include "PLAStage.hpp"
#include "PLARenderer.hpp"
#include "PLAError.hpp"

PLAApp PLAApp::_instance = PLAApp();

PLAInputCode PLAApp::GetInputCodeFromChar(unsigned char aCharacter)
{
  return PLAInput::GetCodeForKeyFromChar(aCharacter);
}

PLAApp::PLAApp() :
PLAObject(PLAObjectType::App, "== PLAApp ==")
{

}

PLAApp::~PLAApp()
{
  delete _stage; _stage = nullptr;
  _renderer = nullptr;
}

void PLAApp::Init(PLARenderer *aRenderer)
{
  _renderer = aRenderer;
  _renderer->Init();
  PLAError::Manager::GetInstance()->Init();
  _stage = PLAStage::Create();
  PLAInputManager::GetInstance()->SetHandler(_stage);
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
  //PLA_PRINT("-- Update\n");
  _stage->Update();
  PLAInputManager::GetInstance()->Flush();
}

void PLAApp::Render()
{
  //PLA_PRINT("-- Render\n");
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
