#include "PLAStage.hpp"
#include "Plain.hpp"
#include "PLAActor.hpp"

PLAStage::PLAStage()
{
  PLAStyle style;
  style.SetColorValue(PLAStyleType::FillColor, kPLAColorGray);
  PLAShapeRect shape(PLAVec2Make(0, 160), style);
  _context = new PLAActor(PLAVec3Make(0.5, 0.5, 0), kPLAColorWhite,
                          PLATransform(), shape);
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

void PLAStage::SetupActors()
{
  static const int kNumberOfCircleActors = 3;

  static const PLACircle kCircles[kNumberOfCircleActors] = {
    PLACircleMake(PLAVec2Make(10, 10), 120),
    PLACircleMake(PLAVec2Make(10, 10), 100),
    PLACircleMake(PLAVec2Make( 0,  0), 80),
  };

  static const PLAColor kCircleColors[kNumberOfCircleActors] = {
    kPLAColorRed,
    kPLAColorGreen,
    kPLAColorBlue,
  };

  static const PLAVec3 kCirclePivot = PLAVec3Make(0.5, 0.5, 0);

  PLAActor *circleActors[kNumberOfCircleActors];
  for (int i = 0; i < kNumberOfCircleActors; i++)
  {
    PLATransform transform;
    transform.translation.x = kCircles[i].origin.x;
    transform.translation.y = kCircles[i].origin.y;
    PLAStyle style;
    style.SetColorValue(PLAStyleType::FillColor, kCircleColors[i]);
    PLAShapeCircle shape(kCircles[i].radius, style);
    circleActors[i] = new PLAActor(kCirclePivot, kPLAColorWhite,
                                   transform, shape);
  }

  for (int i = 0; i < kNumberOfCircleActors; i++)
  {
    if (i == 0) { _context->AddActor(circleActors[i]); }
    else { circleActors[i - 1]->AddActor(circleActors[i]); }
  }

  static const int kNumberOfRectActors = 3;

  static const PLARect kRects[kNumberOfRectActors] = {
    PLARectMake(PLAVec2Make(10, 10), PLAVec2Make(120, 120)),
    PLARectMake(PLAVec2Make(10, 10), PLAVec2Make(80, 80)),
    PLARectMake(PLAVec2Make(0, 0), PLAVec2Make(40, 40)),
  };

  static const PLAColor kRectColors[kNumberOfRectActors] = {
    kPLAColorCyan,
    kPLAColorMagenta,
    kPLAColorYellow,
  };

  static const PLAVec3 kRectPivot = PLAVec3Make(0.5, 0.5, 0);

  PLAActor *rectActors[kNumberOfRectActors];
  for (int i = 0; i < kNumberOfRectActors; i++)
  {
    PLATransform transform;
    transform.translation.x = kRects[i].pos.x;
    transform.translation.y = kRects[i].pos.y;
    PLAStyle style;
    style.SetColorValue(PLAStyleType::FillColor, kRectColors[i]);
    PLAShapeRect shape(kRects[i].size, style);
    rectActors[i] = new PLAActor(kRectPivot, kPLAColorWhite,
                                 transform, shape);
  }

  for (int i = 0; i < kNumberOfRectActors; i++)
  {
    if (i == 0) { _context->AddActor(rectActors[i]); }
    else { rectActors[i - 1]->AddActor(rectActors[i]); }
  }

  // test
  /*
  {
    PLADebug::PrintStr("0\n");
    clock_t clockStart = clock();
    for (int i = 0; i < 0xFFFF; i++)
    {
      circleActors[i % kNumberOfCircleActors]->
        SetSize(circleActors[(i + 1) % kNumberOfCircleActors]->GetSize());
      rectActors[i % kNumberOfRectActors]->
        SetSize(rectActors[(i + 1) % kNumberOfRectActors]->GetSize());
    }
    clock_t clockStop = clock();
    double clockDur = (double)(clockStop - clockStart) / CLOCKS_PER_SEC;
    PLADebug::PrintStr("time : %f\n", clockDur);
  }

  {
    PLADebug::PrintStr("1\n");
    clock_t clockStart = clock();
    for (int i = 0; i < 0xFFFF; i++)
    {
      PLAVec3 sizeCircle(kPLAVec3None);
      circleActors[i % kNumberOfCircleActors]->GetSize(&sizeCircle);
      circleActors[(i + 1) % kNumberOfCircleActors]->SetSize(sizeCircle);
      PLAVec3 sizeRect(kPLAVec3None);
      rectActors[i % kNumberOfRectActors]->GetSize(&sizeRect);
      rectActors[(i + 1) % kNumberOfRectActors]->SetSize(sizeRect);
    }
    clock_t clockStop = clock();
    double clockDur = (double)(clockStop - clockStart) / CLOCKS_PER_SEC;
    PLADebug::PrintStr("time : %f\n", clockDur);
  }
   */

  PLA_PRINT_STR("");
}

void PLAStage::SetSize(const PLAVec3 &aSize)
{
  _context->SetSize(aSize);
}
