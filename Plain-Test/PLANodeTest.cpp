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
    _nodes.push_back(PLANode::Create(1));
    _nodes.push_back(PLANode::Create(2));
    _nodes.push_back(PLANode::Create(3));
    _nodes.push_back(PLANode::Create(4));
  }

  virtual void TearDown()
  {
    PLAObject::Delete(_rootNode);
    for (PLANode *node : _nodes)
    {
      PLAObject::Delete(node);
    }
  }
};

TEST_F(PLANodeTest, Test)
{
  GRA_PRINT("%s\n", _rootNode->GetObjectName().c_str());
}

void TestUpdateNodes(PLANode *aNode) {
  PLAInt length = aNode->GetLength();
  for (int i = 0; i < length + 3; i++) {
    GRA_PRINT("-- FRAME: %d\n", i);
    aNode->Update();
    if (i == length - 1) {
      ASSERT_EQ(1, aNode->GetProgress());
    } else {
      ASSERT_NE(1, aNode->GetProgress());
    }
  }
}

TEST_F(PLANodeTest, Update_UpdateNodes_IncreaseProgress)
{
  uint i = 0;
  for (PLANode *node : _nodes) {
    GRA_PRINT("-- _nodes[%d] --------\n", i);
    node->SetFunction(PLANode::FunctionCode::OnStart, [i](PLANode *node) {
      GRA_PRINT("    _nodes[%d] %4d OnStart\n", i, node->GetSteps());
    });
    node->SetFunction(PLANode::FunctionCode::OnUpdate, [i](PLANode *node) {
      PLAFloat progress = node->GetProgress();
      GRA_PRINT("    _nodes[%d] %4d OnUpdate : progress : %f\n",
                i, node->GetSteps(), progress);
    });
    node->SetFunction(PLANode::FunctionCode::OnStop, [i](PLANode *node) {
      GRA_PRINT("    _nodes[%d] %4d OnStop\n", i, node->GetSteps());
    });
    TestUpdateNodes(node);
    ++i;
    GRA_PRINT("\n");
  }
  /*
  GRA_PRINT("--_nodes[0]\n");
  TestUpdateNodes(_nodes[0]);
  GRA_PRINT("--_nodes[1]\n");
  TestUpdateNodes(_nodes[1]);
  GRA_PRINT("--_nodes[2]\n");
  TestUpdateNodes(_nodes[2]);
  GRA_PRINT("--_nodes[3]\n");
  TestUpdateNodes(_nodes[3]);
  */
}
