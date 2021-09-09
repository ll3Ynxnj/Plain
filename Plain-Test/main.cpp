#include <vector>
#include "gtest/gtest.h"

#include "PLAActorTest.cpp"
#include "PLACollisionTest.cpp"
#include "PLALayerTest.cpp"
#include "PLANodeTest.cpp"
#include "PLAPropertyTest.cpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
