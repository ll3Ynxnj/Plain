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
  PLAFloat duration = 0.1;//0.2;
  PLAMotionNode m0 = PLAMotionNode(PLAMotionType::Translation,
                                   PLAVec3(0, 0, 0), PLAVec3( 10, 0, 0), duration);
  m0.SetObjectName("m0");
  PLAMotionNode m1 = PLAMotionNode(PLAMotionType::Translation,
                                   PLAVec3(10, 0, 0), PLAVec3(0, 0, 0), duration);
  m1.SetObjectName("m1");
  /*
  PLAMotionNode motion = PLAMotionNode();
  motion.AddMain(&m0);
  motion.AddQueue(&m1);
  _rootActor->SetMotion(motion);
   */
  //*
  this->_rootActor->AddMotion(&m0);
  this->_rootActor->AddMotion(&m1);
   //*/
  PLAUInt totalSteps = ceil(PLAApp::kRefreshRate * duration) * 2;
  for (PLAUInt i = 0; i < totalSteps + 3; i++) {
    GRA_PRINT("-- FRAME : %3d --\n", i);
    _rootActor->Update();
    PLAFloat ttx = _rootActor->GetTransform().translation.x;
    GRA_PRINT("%3d : _rootActor.GetTransform.translation.x : %f\n", i, ttx);
    PLAProperty p = _rootActor->GetMotionProperty(PLAMotionType::Translation);
    if (p.GetPropertyType() == PLAPropertyType::None) { continue; }
    PLAVec3 pt = p.GetVec3();
    PLAFloat ptx = pt.x;
    GRA_PRINT("ptx: %f\n", i, ptx);
    GRA_PRINT("-----------------\n");
  }
}
