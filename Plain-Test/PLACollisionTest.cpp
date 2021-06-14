class PLACollisionTest : public ::testing::Test
{
protected:
  virtual void SetUp()
  {

  }

  virtual void TearDown()
  {

  }
};

TEST(PLACollisionTest, IsCollideWithPointAndPoint)
{
  PLAPoint p0(kPLAPointNone);
  PLAPoint p1(kPLAPointNone);
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndPoint(p0, p1));
  p0.x = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndPoint(p0, p1));
  p1.x = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndPoint(p0, p1));
  p1 = p0;
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndPoint(p0, p1));
}

TEST(PLACollisionTest, IsCollideWithPointAndRect)
{
  PLAPoint point(kPLAPointNone);
  PLARect rect(kPLARectNone);
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndRect(point, rect));
  rect.size.x = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndRect(point, rect));
  rect.size.y = 1;
  EXPECT_EQ(true, PLACollision::IsCollideWithPointAndRect(point, rect));
  point.x = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndRect(point, rect));
  point.y = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndRect(point, rect));
  rect.size.x = 2;
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndRect(point, rect));
  rect.size.y = 2;
  EXPECT_EQ(true, PLACollision::IsCollideWithPointAndRect(point, rect));
}

TEST(PLACollisionTest, IsCollideWithPointAndCircle)
{
  PLAPoint point(kPLAPointNone);
  PLACircle circle(kPLACircleNone);
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndCircle(point, circle));
  point.x = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndCircle(point, circle));
  point.y = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndCircle(point, circle));
  circle.radius = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndCircle(point, circle));
  point.x = 0.5;
  EXPECT_EQ(false, PLACollision::IsCollideWithPointAndCircle(point, circle));
  point.y = 0.5;
  EXPECT_EQ(true, PLACollision::IsCollideWithPointAndCircle(point, circle));
}

TEST(PLACollisionTest, IsCollideWithRectAndRect)
{
  PLARect rect0(kPLARectNone);
  PLARect rect1(kPLARectNone);
  EXPECT_EQ(false, PLACollision::IsCollideWithRectAndRect(rect0, rect1));
  rect0.size.x = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithRectAndRect(rect0, rect1));
  rect0.size.y = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithRectAndRect(rect0, rect1));
  rect1.size.x = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithRectAndRect(rect0, rect1));
  rect1.size.y = 1;
  EXPECT_EQ(true, PLACollision::IsCollideWithRectAndRect(rect0, rect1));
  rect1.pos.x = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithRectAndRect(rect0, rect1));
  rect1.pos.y = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithRectAndRect(rect0, rect1));
  rect0.size.x = 2;
  EXPECT_EQ(false, PLACollision::IsCollideWithRectAndRect(rect0, rect1));
  rect0.size.y = 2;
  EXPECT_EQ(true, PLACollision::IsCollideWithRectAndRect(rect0, rect1));
}

TEST(PLACollisionTest, IsCollideWithRectAndCircle)
{
  PLARect rect(kPLARectNone);
  PLACircle circle(kPLACircleNone);
  EXPECT_EQ(false, PLACollision::IsCollideWithRectAndCircle(rect, circle));
  circle.radius = 1;
  EXPECT_EQ(true, PLACollision::IsCollideWithRectAndCircle(rect, circle));
  circle.origin.x = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithRectAndCircle(rect, circle));
  circle.origin.y = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithRectAndCircle(rect, circle));
  rect.size.x = 1;
  EXPECT_EQ(false, PLACollision::IsCollideWithRectAndCircle(rect, circle));
  rect.size.y = 1;
  EXPECT_EQ(true, PLACollision::IsCollideWithRectAndCircle(rect, circle));
}

TEST(PLACollisionTest, IsCollideWithCircleAndCircle)
{
  PLACircle circle0(kPLACircleNone);
  PLACircle circle1(kPLACircleNone);
  EXPECT_EQ(false, PLACollision::IsCollideWithCircleAndCircle(circle0, circle1));
  circle0.radius = 1;
  EXPECT_EQ(true, PLACollision::IsCollideWithCircleAndCircle(circle0, circle1));
  circle1.radius = 1;
  EXPECT_EQ(true, PLACollision::IsCollideWithCircleAndCircle(circle0, circle1));
  circle1.origin.x = 1;
  EXPECT_EQ(true, PLACollision::IsCollideWithCircleAndCircle(circle0, circle1));
  circle1.origin.x = 2;
  EXPECT_EQ(false, PLACollision::IsCollideWithCircleAndCircle(circle0, circle1));
}
