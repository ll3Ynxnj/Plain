#include "PLAApp.hpp"
#include "PLAError.hpp"
#include "PLAStage.hpp"
#include "PLARenderer.hpp"

PLAApp PLAApp::_instance = PLAApp();

PLAApp::PLAApp() :
PLAObject(PLAObjectType::App)
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
  _stage->SetupActors();
  //PLA_ERROR_ISSUE(PLAErrorType::Assert, "[%s] : %d %x %p", "TEST", 0, 1, this);
}

void PLAApp::Reset()
{
  PLAError::Manager::GetInstance()->Reset();
}

void PLAApp::Update()
{
  _stage->Update();
}

void PLAApp::Render()
{
  _renderer->Clear();
  _renderer->Render(_stage->GetContext());
  _renderer->Flush();
}

void PLAApp::RefreshScreenSize(int aWidth, int aHeight)
{
  PLAVec3 frameSize(PLAVec3Make(aWidth, aHeight, 0));
  PLAVec3 stageSize(PLAVec3Make(kBaseScreenLength));

  if      (aWidth < aHeight)
  { stageSize.y *= float(aHeight) / float(aWidth ); }
  else if (aWidth > aHeight)
  { stageSize.x *= float(aWidth ) / float(aHeight); }

  _renderer->RefreshScreenSize(frameSize, stageSize);
  _stage->SetSize(stageSize);
}
