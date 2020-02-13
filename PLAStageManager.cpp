#include "PLAStageManager.hpp"
#include "PLARectActor.hpp"
#include "PLACircleActor.hpp"

PLAStageManager::PLAStageManager() :
  _stage(nullptr)
{

}

PLAStageManager::~PLAStageManager()
{

}

void PLAStageManager::Initialize()
{
  GRARect rect = {kGRAPointNone, kGRASizeNone};
  _stage = new PLARectActor(rect, kGRAColorBlue);
}

void PLAStageManager::Update()
{
  _stage->Update();
}

void PLAStageManager::Render()
{
  _stage->Render();
}

void PLAStageManager::SetStageSize(const GRASize aSize)
{
  _stage->SetSize(aSize);
}

void PLAStageManager::SetupActors()
{
  static const GRACircle kCircles[] =
  {
    {{ 0.0, 0.0 }, 0.6 },
    {{ 0.0, 0.0 }, 0.5 },
    {{ 0.0, 0.0 }, 0.4 },
  };

  static const GRAColor kCircleColors[] =
  {
    kGRAColorRed,
    kGRAColorGreen,
    kGRAColorBlue,
  };

  for (int i = 0; i < 3; i++)
  {
    PLAActor *actor = new PLACircleActor(kCircles[i], kCircleColors[i]);
    _stage->AddActor(actor);
  }

  static const GRARect kRects[] =
  {
    {{ -0.3, -0.3 }, { 0.6, 0.6 }},
    {{ -0.2, -0.2 }, { 0.4, 0.4 }},
    {{ -0.1, -0.1 }, { 0.2, 0.2 }},
  };

  static const GRAColor kRectColors[] =
  {
    kGRAColorCyan,
    kGRAColorMagenta,
    kGRAColorYellow,
  };

  for (int i = 0; i < 3; i++)
  {
    PLAActor *actor = new PLARectActor(kRects[i], kRectColors[i]);
    _stage->AddActor(actor);
  }
}
