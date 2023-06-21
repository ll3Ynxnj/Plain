#include "Core/App/PLAApp.hpp"
#include "Object/Actor/PLAOBJActor.hpp"
#include "../Grain/Primitive/GRAPRMType.hpp"

class PLAActorTest : public ::testing::Test
{
protected:
  PLAOBJActor *_rootActor = nullptr;
  std::vector<PLAOBJActor *> _actors = std::vector<PLAOBJActor *>();

  virtual void SetUp()
  {
    //_rootActor = PLAOBJActor::CreateRect(kPLAVec3fNorm, kPLAColorWhite,
    //                                  kGRATransformNorm, PLARect(kPLAVec3fNone, kPLAVec2fNone));
    _rootActor = PLAOBJActor::CreateRect(kPLAVec3fNorm, kPLAColorWhite,
                                         kPLATransformNorm, kPLARectNorm);
    _rootActor->SetObjectName("_rootActor");

    static const int kNumberOfActors = 3;
    for (int i = 0; i < kNumberOfActors; i++)
    {
      PLAOBJActor *actor = PLAOBJActor::CreateRect(kPLAVec3fNorm, kPLAColorWhite,
                                                   kPLATransformNorm, kPLARectNorm);
      actor->SetObjectName("actor");
      _actors.push_back(actor);
    }
  }

  virtual void TearDown()
  {
    PLAObject::Delete(_rootActor);
    _rootActor = nullptr;
    for (PLAOBJActor *aActor : _actors)
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
  PLATMLMotionNode m0 = PLATMLMotionNode(PLATMLMotionType::Translation,
                                         PLAVec3f(0, 0, 0), PLAVec3f( 10, 0, 0), duration);
  m0.SetObjectName("m0");
  PLATMLMotionNode m1 = PLATMLMotionNode(PLATMLMotionType::Translation,
                                         PLAVec3f(10, 0, 0), PLAVec3f(0, 0, 0), duration);
  m1.SetObjectName("m1");
  /*
  PLATMLMotionNode motion = PLATMLMotionNode();
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
    PLAProperty p = _rootActor->GetMotionProperty(PLATMLMotionType::Translation);
    if (p.GetPropertyType() == PLAPropertyType::None) { continue; }
    PLAVec3f pt = p.GetVec3f();
    PLAFloat ptx = pt.x;
    GRA_PRINT("ptx: %f\n", i, ptx);
    GRA_PRINT("-----------------\n");
  }
}
