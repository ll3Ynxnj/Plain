#include "../PLARectActor.hpp"
#include "../PLACircleActor.hpp"

class PLAActorTest : public ::testing::Test
{
protected:
  static const int kNumRectActors = 3;
  static const int kNumCircleActors = 3;
  PLARectActor *_rootActor = nullptr;
  std::vector<PLAActor *> _actors = std::vector<PLAActor *>();

  virtual void SetUp()
  {
    _rootActor = new PLARectActor(kGRARectNorm, kGRAColorWhite, GRAPoint(0));

    static const GRARect kRects[] =
    {
      {{ -0.3, -0.3, 0.0 }, { 0.6, 0.6, 0.0 }},
      {{ -0.2, -0.2, 0.0 }, { 0.4, 0.4, 0.0 }},
      {{ -0.1, -0.1, 0.0 }, { 0.2, 0.2, 0.0 }},
    };

    static const GRAColor kRectColors[] =
    {
      kGRAColorCyan,
      kGRAColorMagenta,
      kGRAColorYellow,
    };

    for (int i = 0; i < kNumRectActors; i++)
    {
      _actors.push_back(new PLARectActor(kRects[i], kRectColors[i]));
    }

    static const GRACircle kCircles[] =
    {
      {{ 0.0, 0.0, 0.0 }, 0.6 },
      {{ 0.0, 0.0, 0.0 }, 0.5 },
      {{ 0.0, 0.0, 0.0 }, 0.4 },
    };

    static const GRAColor kCircleColors[] =
    {
      kGRAColorRed,
      kGRAColorGreen,
      kGRAColorBlue,
    };

    for (int i = 0; i < kNumCircleActors; i++)
    {
      _actors.push_back(new PLACircleActor(kCircles[i], kCircleColors[i]));
    }
  }

  virtual void TearDown()
  {
    _rootActor = nullptr;
    for (PLAActor *actor : _actors)
    {
      delete(actor);
    }
  }
};

TEST_F(PLAActorTest, AddActor_AddActors_IncreaseActors)
{
  EXPECT_EQ(0, this->_rootActor->GetNumberOfActors());
  this->_rootActor->AddActor(_actors[0]);
  EXPECT_EQ(1, this->_rootActor->GetNumberOfActors());
  this->_rootActor->AddActor(_actors[1]);
  EXPECT_EQ(2, this->_rootActor->GetNumberOfActors());
}
