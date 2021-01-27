//
// Created by Kawai Kentaro on 2020/11/13.
//

#include "../Core/PLAShape.hpp"

class PLAShapeTest : public ::testing::Test
{
protected:
  virtual void SetUp()
  {

  }

  virtual void TearDown()
  {

  }
};

TEST(PLASHPRectTest, IsCollideWithPoint)
{
  PLAPoint point = kPLAPointNone;
  PLASHPRect shape = PLASHPRect(kPLAVec3None, kPLAVec2None);
  EXPECT_EQ(false, shape.IsCollideWithPoint(point));
  shape.SetSize(PLAVec3Make(1, 1, 0), kPLAVec3None);
  EXPECT_EQ(true, shape.IsCollideWithPoint(point));
  point.x = 1;
  EXPECT_EQ(false, shape.IsCollideWithPoint(point));
  point.y = 1;
  EXPECT_EQ(false, shape.IsCollideWithPoint(point));
  shape.SetSize(PLAVec3Make(2, 2, 0), kPLAVec3None);
  EXPECT_EQ(true, shape.IsCollideWithPoint(point));
  shape.SetOffset(PLAVec3Make(1, 1, 0));
  EXPECT_EQ(true, shape.IsCollideWithPoint(point));
  shape.SetOffset(PLAVec3Make(-1, -1, 0));
  EXPECT_EQ(false, shape.IsCollideWithPoint(point));
}

TEST(PLASHPCircleTest, IsCollideWithPoint)
{
  {
    PLAPoint point = kPLAPointNone;
    PLASHPCircle shape = PLASHPCircle(kPLAVec3None, 0);
    EXPECT_EQ(false, shape.IsCollideWithPoint(point));
  }
  {
    PLAPoint point = kPLAPointNone;
    PLASHPCircle shape = PLASHPCircle(PLAVec3Make(1, 1, 0), 1);
    EXPECT_EQ(false, shape.IsCollideWithPoint(point));
  }
  {
    PLAPoint point = kPLAPointNone;
    PLASHPCircle shape = PLASHPCircle(PLAVec3Make(1, 1, 0), 2);
    EXPECT_EQ(true, shape.IsCollideWithPoint(point));
  }
}

