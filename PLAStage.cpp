#include "PLAApp.hpp"
#include "PLAStage.hpp"
#include "PLAError.hpp"
#include "PLARectActor.hpp"
#include "PLACircleActor.hpp"
#include "Grain/GRARect.hpp"
#include "Grain/GRACircle.hpp"

PLAStage::PLAStage() :
  _context(new PLARectActor(GRARect(GRAPoint(0), GRASize(0)),
                            kGRAColorGray,
                            GRAPoint(0.5, 0.5, 0)))
{

}

PLAStage::~PLAStage()
{
  delete(_context);
  _context = nullptr;
}

void PLAStage::Update()
{
  _context->Update();
}

void PLAStage::Render()
{
  _context->Render();
}

void PLAStage::SetupActors()
{
  static const GRACircle kCircles[] =
  {
    GRACircle(GRAPoint( 0,  0, 0), 120),
    GRACircle(GRAPoint(10, 10, 0), 100),
    GRACircle(GRAPoint(20, 20, 0),  80),
  };

  static const GRAColor kCircleColors[] =
  {
    kGRAColorRed,
    kGRAColorGreen,
    kGRAColorBlue,
  };

  for (int i = 0; i < 3; i++)
  {
    PLAActor *actor(new PLACircleActor(kCircles[i], kCircleColors[i]));
    _context->AddActor(actor);
  }

  static const GRARect kRects[] =
  {
    GRARect(GRAPoint(0, 0, 0), GRASize(120, 120, 0)),
    GRARect(GRAPoint(10, 10, 0), GRASize( 80,  80, 0)),
    GRARect(GRAPoint(20, 20, 0), GRASize( 40,  40, 0)),
  };

  static const GRAColor kRectColors[] =
  {
    kGRAColorCyan,
    kGRAColorMagenta,
    kGRAColorYellow,
  };

  static const GRAPoint kRectPivot = GRAPoint(0.5, 0.5, 0);

  for (int i = 0; i < 3; i++)
  {
    PLAActor *actor(new PLARectActor(kRects[i], kRectColors[i], kRectPivot));
    _context->AddActor(actor);
  }
}

void PLAStage::SetSize(const GRASize &aSize)
{
  _context->SetSize(aSize);
}
