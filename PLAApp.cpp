#include "PLAApp.hpp"

#include "PLAErrorManager.hpp"
#include "PLAStageManager.hpp"
#include "PLARenderingManager.hpp"

PLAApp PLAApp::_instance = PLAApp();

PLAApp::PLAApp()
{

}

PLAApp::~PLAApp()
{

}

void PLAApp::Init()
{
  PLAErrorManager::GetInstance()->Init();
  PLAStageManager::GetInstance()->Init();
}

void PLAApp::Setup()
{
  PLAStageManager::GetInstance()->SetupActors();
}

void PLAApp::Reset()
{
  PLAErrorManager::GetInstance()->Reset();
  PLAStageManager::GetInstance()->Reset();
}

void PLAApp::Update()
{
  PLAStageManager::GetInstance()->Update();
  PLARenderingManager::GetInstance()->Update();
}

void PLAApp::SetRenderer(PLARenderer *aRenderer)
{
  PLARenderingManager::GetInstance()->SetRenderer(aRenderer);
}

void PLAApp::SetScreenSize(const GRASize &aSize)
{
  PLAStageManager::GetInstance()->SetStageSize(aSize);
}
