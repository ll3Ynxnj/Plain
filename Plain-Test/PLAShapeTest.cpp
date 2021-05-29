//
// Created by Kawai Kentaro on 2020/11/13.
//

#include "Core/Layer/PLALayer.hpp"

class PLALayerTest : public ::testing::Test
{
protected:
  virtual void SetUp()
  {

  }

  virtual void TearDown()
  {

  }
};

TEST(PLALYRRectTest, IsCollideWithPoint)
{
  PLAPoint point = kPLAPointNone;
  PLALYRRect layer = PLALYRRect(kPLAVec3None, kPLAVec2None);
  EXPECT_EQ(false, layer.IsCollideWithPoint(point));
  layer.SetSize(PLAVec3Make(1, 1, 0), kPLAVec3None);
  EXPECT_EQ(true, layer.IsCollideWithPoint(point));
  point.x = 1;
  EXPECT_EQ(false, layer.IsCollideWithPoint(point));
  point.y = 1;
  EXPECT_EQ(false, layer.IsCollideWithPoint(point));
  layer.SetSize(PLAVec3Make(2, 2, 0), kPLAVec3None);
  EXPECT_EQ(true, layer.IsCollideWithPoint(point));
  layer.SetOffset(PLAVec3Make(1, 1, 0));
  EXPECT_EQ(true, layer.IsCollideWithPoint(point));
  layer.SetOffset(PLAVec3Make(-1, -1, 0));
  EXPECT_EQ(false, layer.IsCollideWithPoint(point));
}

TEST(PLALYRCircleTest, IsCollideWithPoint)
{
  {
    PLAPoint point = kPLAPointNone;
    PLALYRCircle layer = PLALYRCircle(kPLAVec3None, 0);
    EXPECT_EQ(false, layer.IsCollideWithPoint(point));
  }
  {
    PLAPoint point = kPLAPointNone;
    PLALYRCircle layer = PLALYRCircle(PLAVec3Make(1, 1, 0), 1);
    EXPECT_EQ(false, layer.IsCollideWithPoint(point));
  }
  {
    PLAPoint point = kPLAPointNone;
    PLALYRCircle layer = PLALYRCircle(PLAVec3Make(1, 1, 0), 2);
    EXPECT_EQ(true, layer.IsCollideWithPoint(point));
  }
}

