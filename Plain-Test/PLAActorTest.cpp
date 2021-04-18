#include "../Core/PLAActor.hpp"

class PLAActorTest : public ::testing::Test
{
protected:
  PLAActor *_rootActor = nullptr;
  std::vector<PLAActor *> _actors = std::vector<PLAActor *>();

  virtual void SetUp()
  {
    _rootActor = PLAActor::Create(kPLAVec3Norm, kPLAColorWhite,
                                  PLATransform(), PLALYRRect(kPLAVec3None, kPLAVec2None));

    static const int kNumberOfActors = 3;
    for (int i = 0; i < kNumberOfActors; i++)
    {
      PLAActor *actor = PLAActor::Create(kPLAVec3Norm, kPLAColorWhite,
                                         PLATransform(), PLALYRRect(kPLAVec3None, kPLAVec2None));
      PLAStyle style;
      style.SetColorValue(PLAStyleType::FillColor, kPLAColorWhite);
      actor->SetStyle(style);
      _actors.push_back(actor);
    }
  }

  virtual void TearDown()
  {
    PLAObject::Delete(_rootActor);
    _rootActor = nullptr;
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
