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
    _rootActor->SetObjectName("_rootActor");

    static const int kNumberOfActors = 3;
    for (int i = 0; i < kNumberOfActors; i++)
    {
      PLAActor *actor = PLAActor::CreateRect(kPLAVec3Norm, kPLAColorWhite,
                                             kPLATransformNorm, kPLARectNorm);
      actor->SetObjectName("actor");
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
  PLAFloat duration = 0.04;//0.2;
  PLAMotion m0 = PLAMotion(PLAMotionType::Translation,
                           PLAVec3( 20, 0, 0), duration);
  m0.SetObjectName("m0");
  PLAMotion m1 = PLAMotion(PLAMotionType::Translation,
                           PLAVec3(-20, 0, 0), duration);
  m1.SetObjectName("m1");
  this->_rootActor->AddMotion(&m0);
  this->_rootActor->AddMotion(&m1);
  PLAUInt totalSteps = PLAApp::kRefreshRate * duration + 2;
  for (PLAUInt i = 0; i < totalSteps + 3; i++) {
    _rootActor->Update();
    PLAFloat ttx = _rootActor->GetTransform().translation.x;
    GRA_PRINT("%3d : _rootActor.GetTransform.translation.x : %f\n", i, ttx);
    PLAProperty p = _rootActor->GetMotionProperty(PLAMotionType::Translation);
    if (p.GetPropertyType() == PLAPropertyType::None) { continue; }
    PLAVec3 pt = p.GetVec3();
    PLAFloat ptx = pt.x;
    GRA_PRINT("ptx: %f\n", i, ptx);
  }
}
