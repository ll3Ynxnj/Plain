#include "../PLAActor.hpp"

class PLAActorTest : public ::testing::Test
{
protected:
  PLAActor *_rootActor = nullptr;
  std::vector<PLAActor *> _actors = std::vector<PLAActor *>();

  virtual void SetUp()
  {
    static const int kNumberOfActors = 3;
    for (int i = 0; i < kNumberOfActors; i++)
    {
      PLAStyle style;
      style.SetColorValue(PLAStyleType::FillColor, kPLAColorWhite);
      PLASHPRect shape(kPLAPointNorm, style);
      _actors.push_back(PLAActor::Create(kPLAVec3Norm, kPLAColorWhite,
                                         PLATransform(), shape));
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
