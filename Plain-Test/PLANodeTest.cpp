//
// Created by Kentaro Kawai on 2021/08/15.
//

#include "PLANode.hpp"

class PLANodeTest : public ::testing::Test
{
protected:
  PLANode *_rootNode = nullptr;

  std::vector<PLANode *>_nodes = std::vector<PLANode *>();

  virtual void SetUp()
  {
    _rootNode = PLANode::Create(1);
    _nodes.push_back(PLANode::Create(   20));
    _nodes.push_back(PLANode::Create(  300));
    _nodes.push_back(PLANode::Create( 4000));
    _nodes.push_back(PLANode::Create(10000));
  }

  virtual void TearDown()
  {
    PLAObject::Delete(_rootNode);
    PLAObject::Delete(_nodes[0]);
    PLAObject::Delete(_nodes[1]);
    PLAObject::Delete(_nodes[2]);
    PLAObject::Delete(_nodes[3]);
  }

};

TEST_F(PLANodeTest, Test)
{
  GRA_PRINT("%s\n", _rootNode->GetObjectName().c_str());
}

void TestUpdateNodes(PLANode *aNode) {
  PLAInt length = aNode->GetLength();
  for (int i = 0; i < length; i++) {
    aNode->Update();
    PLAFloat progress = aNode->GetProgress();
    GRA_PRINT("%d : progress : %f\n", i, progress);
    if (i == length - 1) {
      ASSERT_EQ(1, progress);
    } else {
      ASSERT_NE(1, progress);
    }
  }
}

TEST_F(PLANodeTest, Update_UpdateNodes_IncreaseProgress)
{
  GRA_PRINT("--_nodes[0]\n");
  TestUpdateNodes(_nodes[0]);
  GRA_PRINT("--_nodes[1]\n");
  TestUpdateNodes(_nodes[1]);
  GRA_PRINT("--_nodes[2]\n");
  TestUpdateNodes(_nodes[2]);
  GRA_PRINT("--_nodes[3]\n");
  TestUpdateNodes(_nodes[3]);
}
