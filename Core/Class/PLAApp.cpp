#include "PLAApp.hpp"
#include "Core/Input/PLAInput.hpp"
#include "PLARenderer.hpp"
#include "PLAError.hpp"

PLAApp PLAApp::_instance = PLAApp();

PLAScene *PLAApp::Scene()
{
  return PLAScene::Manager::Instance()->RefCurrentScene();
}

void PLAApp::AddNodeThread(PLATimelineThread *aThread)
{
  //_instance._subNodes[aNode->GetObjectName()] = aNode;
  _nodeThread.AddThread(aThread);
}

void PLAApp::UpdateNodeThread()
{
  //for (const auto [name, node]: _instance._subNodes)
  //{ _instance._subNodes[name]->Update(); }
  _nodeThread.Update();
  this->PrintNodes();
  ;
}

/*
void PLAApp::RemoveNode(const PLATimelineNode *aNode)
{
  //_instance._subNodes.erase(aNode->GetObjectName());
}
 */

void PLAApp::PrintNodes() const
{
  GRA_PRINT(" LV :  STEPS / LENGTH | CURRENT | NAME                             |\n");
  _nodeThread.PrintNodes();
  GRA_PRINT("----:-----------------|---------|----------------------------------|\n");
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

void PLAApp::Init(PLARenderer *aRenderer)
{
  PLATimelineNode *node = PLATimelineNode::Create(PLATimelineNode::Type::None);
  node->SetInfinity(true);
  _nodeThread.AddNode(node);
  _renderer = aRenderer;
  _renderer->Init();
  PLAError::Manager::Instance()->Init();
  PLAScene::Manager::Instance()->Init();
  _stage = PLAStage::Create();
  PLAInputManager::Instance()->SetHandler(_stage);
  //PLA_ERROR_ISSUE(PLAErrorType::Assert, "[%s] : %d %x %p", "TEST", 0, 1, this);
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
  // DeleteはDestroyに名称変更
  // 削除を実行するとレンダリング時にエラー。つまり削除済みノードへの参照が残っている。
  PLAObject::Manager::Instance()->DeleteUnboundObjects();
  PLAInputManager::Instance()->Flush();
  UpdateNodeThread();
  _stage->Update();
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