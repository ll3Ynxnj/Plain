#include "PLAApp.hpp"
#include "PLAErrorManager.hpp"
#include "PLAStage.hpp"
#include "PLARenderer.hpp"

PLAApp PLAApp::_instance = PLAApp();

PLAApp::PLAApp() :
_stage(nullptr),
_renderer(nullptr)
{

}

PLAApp::~PLAApp()
{
  delete _stage; _stage = nullptr;
  _renderer = nullptr;
}

void PLAApp::Init(PLARendererType aType)
{
  _renderer = PLARenderer::Create(aType);
  _renderer->Init();
  PLAErrorManager::GetInstance()->Init();
  _stage = new PLAStage();
  _stage->SetupActors();
}

void PLAApp::Reset()
{
  PLAErrorManager::GetInstance()->Reset();
}

void PLAApp::Update()
{
  _stage->Update();
}

void PLAApp::Render()
{
  _renderer->Clear();
  _renderer->DrawDemo();
  _stage->Render();
  _renderer->Render();
  _renderer->Flush();
}

void PLAApp::PushRenderingData(const PLARenderingData *aData)
{
  _renderer->PushRenderingData(aData);
}

void PLAApp::RefreshScreenSize(int aWidth, int aHeight)
{
  PLAVec3 frameSize(aWidth, aHeight, 0);
  PLAVec3 stageSize(kBaseScreenLength);

  if      (aWidth < aHeight)
  { stageSize.y *= float(aHeight) / float(aWidth ); }
  else if (aWidth > aHeight)
  { stageSize.x *= float(aWidth ) / float(aHeight); }

  _renderer->RefreshScreenSize(frameSize, stageSize);
  _stage->SetSize(stageSize);
}
