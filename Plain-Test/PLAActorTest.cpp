#include "../Core/PLAActor.hpp"
#include "../Grain/GRAType/GRAType.hpp"

class PLAActorTest : public ::testing::Test
{
protected:
  PLAActor *_rootActor = nullptr;
  std::vector<PLAActor *> _actors = std::vector<PLAActor *>();

  virtual void SetUp()
  {
    //_rootActor = PLAActor::CreateRect(kPLAVec3Norm, kPLAColorWhite,
    //                                  kGRATransformNorm, PLARect(kPLAVec3None, kPLAVec2None));
    _rootActor = PLAActor::CreateRect(kPLAVec3Norm, kPLAColorWhite,
                                      kPLATransformNorm, kPLARectNorm);

    static const int kNumberOfActors = 3;
    for (int i = 0; i < kNumberOfActors; i++)
    {
      PLAActor *actor = PLAActor::CreateRect(kPLAVec3Norm, kPLAColorWhite,
                                             kPLATransformNorm, kPLARectNorm);
      _actors.push_back(actor);
    }
  }

  virtual void TearDown()
  {
    PLAObject::Delete(_rootActor);
    _rootActor = nullptr;
    for (PLAActor *aActor : _actors)
    {
      PLAObject::Delete(aActor);
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
