#include "PLAStage.hpp"
#include "PLAType.hpp"
#include "PLARectActor.hpp"
#include "PLACircleActor.hpp"

PLAStage::PLAStage() :
  _context(new PLARectActor(PLARect(PLAVec3(0), PLAVec3(0)),
                            kPLAColorGray,
                            PLAVec3(0.5, 0.5, 0)))
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
  static const int kNumberOfCircleActors = 3;

  static const PLACircle kCircles[kNumberOfCircleActors] =
  {
    PLACircle(PLAVec3(10, 10, 0), 120),
    PLACircle(PLAVec3(10, 10, 0), 100),
    PLACircle(PLAVec3(10, 10, 0),  80),
  };

  static const PLAColor kCircleColors[] =
  {
    kPLAColorRed,
    kPLAColorGreen,
    kPLAColorBlue,
  };

  PLACircleActor *circleActors[kNumberOfCircleActors];
  for (int i = 0; i < kNumberOfCircleActors; i++)
  {
    circleActors[i] = new PLACircleActor(kCircles[i], kCircleColors[i]);
  }

  for (int i = 0; i < kNumberOfCircleActors; i++)
  {
    if (i == 0) { _context->AddActor(circleActors[i]);            }
    else        { circleActors[i - 1]->AddActor(circleActors[i]); }
  }

  static const int kNumberOfRectActors = 3;

  static const PLARect kRects[kNumberOfRectActors] =
  {
    PLARect(PLAVec3(10, 10, 0), PLAVec3(120, 120, 0)),
    PLARect(PLAVec3(10, 10, 0), PLAVec3( 80,  80, 0)),
    PLARect(PLAVec3(10, 10, 0), PLAVec3( 40,  40, 0)),
  };

  static const PLAColor kRectColors[] =
  {
    kPLAColorCyan,
    kPLAColorMagenta,
    kPLAColorYellow,
  };

  static const PLAVec3 kRectPivot = PLAVec3(0.5, 0.5, 0);

  PLARectActor *rectActors[kNumberOfCircleActors];
  for (int i = 0; i < kNumberOfRectActors; i++)
  {
    rectActors[i] = new PLARectActor(kRects[i], kRectColors[i], kRectPivot);
  }

  for (int i = 0; i < kNumberOfRectActors; i++)
  {
    if (i == 0) { _context->AddActor(rectActors[i]);          }
    else        { rectActors[i - 1]->AddActor(rectActors[i]); }
  }
}

void PLAStage::SetSize(const PLAVec3 &aSize)
{
  _context->SetSize(aSize);
}
