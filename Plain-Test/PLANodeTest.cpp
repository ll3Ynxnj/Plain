//
// Created by Kentaro Kawai on 2021/08/15.
//

#include "PLANode.hpp"

class PLANodeTest : public ::testing::Test
{
protected:
  //PLANode *_rootNode = nullptr;

  //std::vector<PLANode *>_nodes = std::vector<PLANode *>();

  virtual void SetUp()
  {
    /*
    _rootNode = PLANode::Create(1);
    _nodes.push_back(PLANode::Create(1));
    _nodes.push_back(PLANode::Create(2));
    _nodes.push_back(PLANode::Create(3));
    _nodes.push_back(PLANode::Create(4));
    */
  }

  virtual void TearDown()
  {
    /*
    PLAObject::Delete(_rootNode);
    for (PLANode *node : _nodes)
    {
      PLAObject::Delete(node);
    }
    */
  }
};
/*
TEST_F(PLANodeTest, Update_UpdateNodes_IncreaseProgress)
{
  uint i = 0;
  std::vector<PLANode *> nodes = {
    PLANode::Create(1),
    PLANode::Create(2),
    PLANode::Create(3),
    PLANode::Create(4),
  };

  for (PLANode *node : nodes) {
    GRA_PRINT("-- nodes[%d] --------\n", i);
    node->SetFunction(PLANode::FunctionCode::OnStart, [i](PLANode *node) {
      GRA_PRINT("    nodes[%d] %4d OnStart\n", i, node->GetSteps());
    });
    node->SetFunction(PLANode::FunctionCode::OnUpdate, [i](PLANode *node) {
      PLAFloat progress = node->GetProgress();
      GRA_PRINT("    nodes[%d] %4d OnUpdate : progress : %f\n",
                i, node->GetSteps(), progress);
    });
    node->SetFunction(PLANode::FunctionCode::OnStop, [i](PLANode *node) {
      GRA_PRINT("    nodes[%d] %4d OnStop\n", i, node->GetSteps());
    });
    PLAInt length = node->GetLength();
    for (int i = 0; i < length + 3; i++) {
      GRA_PRINT("-- FRAME: %d\n", i);
      node->Update();
      if (i == length - 1) {
        ASSERT_EQ(1, node->GetProgress());
      } else {
        ASSERT_NE(1, node->GetProgress());
      }
    }
    ++i;
    GRA_PRINT("\n");
  }

  //GRA_PRINT("--_nodes[0]\n");
  //TestUpdateNodes(_nodes[0]);
  //GRA_PRINT("--_nodes[1]\n");
  //TestUpdateNodes(_nodes[1]);
  //GRA_PRINT("--_nodes[2]\n");
  //TestUpdateNodes(_nodes[2]);
  //GRA_PRINT("--_nodes[3]\n");
  //TestUpdateNodes(_nodes[3]);
}
*/

TEST_F(PLANodeTest, Update_UpdateNodes_UpdatesPropagateToChildNodes)
{
  /*
   *
   *  |-- [0_2_0]
   *  |-- [0_1_0]
   *  |-- [0_0_0]--[0_0_1]
   *  |
   *  |      |-- [1_0_0]
   *  |      |
   * [0] -- [1] -- [2]
   *
   */

  static const int kNodeLength = 40;
  PLANode *node = PLANode::Create(kNodeLength, "node");

  PLANode *node0 = PLANode::Create(10, "node0");
  PLANode *node1 = PLANode::Create(10, "node1");
  PLANode *node2 = PLANode::Create(10, "node2");

  node->AddMain(node0);
  node->AddMain(node1);
  node->AddMain(node2);

  PLANode *node0_0_0 = PLANode::Create(3, "node0_0_0");
  PLANode *node0_1_0 = PLANode::Create(3, "node0_1_0");
  PLANode *node0_2_0 = PLANode::Create(3, "node0_2_0");

  node0->AddBranch(node0_0_0);
  node0->AddBranch(node0_1_0);
  node0->AddBranch(node0_2_0);

  PLANode *node1_0_0 = PLANode::Create(3, "node1_0_0");

  node1->AddBranch(node1_0_0);

  for (int i = 0; i < kNodeLength; i++) {
    GRA_PRINT("-- %2d : Update() --\n", i);
    node->Update();
  }
}
