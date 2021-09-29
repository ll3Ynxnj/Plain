#include "PLAApp.hpp"
#include "Actor/PLAActor.hpp"
#include "../Grain/Type/GRAType.hpp"

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

TEST_F(PLAActorTest, UpdateMotion_UpdateMotions_RefreshProperties)
{
  PLAFloat duration = 3;//0.2;
  PLAMotion m0 = PLAMotion(PLAMotionType::Translation,
                           PLAVec3( 20, 0, 0), duration);
  PLAMotion m1 = PLAMotion(PLAMotionType::Translation,
                           PLAVec3(-20, 0, 0), duration);
  this->_rootActor->AddMotion(&m0);
  this->_rootActor->AddMotion(&m1);
  for (int i = 0; i < PLAApp::kRefreshRate * duration + 3; i++) {
    _rootActor->Update();
    GRA_PRINT("%3d : _rootActor.GetTransform.translation.x : %f\n",
              i, _rootActor->GetTransform().translation.x);
  }
}
