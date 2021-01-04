#include <vector>
#include "gtest/gtest.h"

#include "PLAActorTest.cpp"
#include "PLACollisionTest.cpp"
#include "PLAShapeTest.cpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
