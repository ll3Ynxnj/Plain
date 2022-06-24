//
// Created by Kentaro Kawai on 2021/08/15.
//

#include "Object/Timeline/PLAOBJTimelineNode.hpp"

class PLANodeTest : public ::testing::Test
{
protected:
  //PLAOBJTimelineNode *_rootNode = nullptr;

  //std::vector<PLAOBJTimelineNode *>_subNodes = std::vector<PLAOBJTimelineNode *>();

  virtual void SetUp()
  {
    /*
    _rootNode = PLAOBJTimelineNode::Create(1);
    _subNodes.push_back(PLAOBJTimelineNode::Create(1));
    _subNodes.push_back(PLAOBJTimelineNode::Create(2));
    _subNodes.push_back(PLAOBJTimelineNode::Create(3));
    _subNodes.push_back(PLAOBJTimelineNode::Create(4));
    */
  }

  virtual void TearDown()
  {
    /*
    PLAObject::Delete(_rootNode);
    for (PLAOBJTimelineNode *node : _subNodes)
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
  std::vector<PLAOBJTimelineNode *> nodes = {
    PLAOBJTimelineNode::Create(1),
    PLAOBJTimelineNode::Create(2),
    PLAOBJTimelineNode::Create(3),
    PLAOBJTimelineNode::Create(4),
  };

  for (PLAOBJTimelineNode *node : nodes) {
    GRA_PRINT("-- nodes[%d] --------\n", i);
    node->SetFunction(PLAOBJTimelineNode::FunctionCode::OnStart, [i](PLAOBJTimelineNode *node) {
      GRA_PRINT("    nodes[%d] %4d OnStart\n", i, node->GetSteps());
    });
    node->SetFunction(PLAOBJTimelineNode::FunctionCode::OnUpdate, [i](PLAOBJTimelineNode *node) {
      PLAFloat progress = node->GetProgress();
      GRA_PRINT("    nodes[%d] %4d OnUpdate : progress : %f\n",
                i, node->GetSteps(), progress);
    });
    node->SetFunction(PLAOBJTimelineNode::FunctionCode::OnStop, [i](PLAOBJTimelineNode *node) {
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

  //GRA_PRINT("--_subNodes[0]\n");
  //TestUpdateNodes(_subNodes[0]);
  //GRA_PRINT("--_subNodes[1]\n");
  //TestUpdateNodes(_subNodes[1]);
  //GRA_PRINT("--_subNodes[2]\n");
  //TestUpdateNodes(_subNodes[2]);
  //GRA_PRINT("--_subNodes[3]\n");
  //TestUpdateNodes(_subNodes[3]);
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
  PLAOBJTimelineNode *node = PLAOBJTimelineNode::Create(kNodeLength, "node");

  PLAOBJTimelineNode *node0 = PLAOBJTimelineNode::Create(10, "node0");
  PLAOBJTimelineNode *node1 = PLAOBJTimelineNode::Create(10, "node1");
  PLAOBJTimelineNode *node2 = PLAOBJTimelineNode::Create(10, "node2");

  node->AddQueue(node0);
  node->AddQueue(node1);
  node->AddQueue(node2);

  PLAOBJTimelineNode *node0_0_0 = PLAOBJTimelineNode::Create(3, "node0_0_0");
  PLAOBJTimelineNode *node0_1_0 = PLAOBJTimelineNode::Create(3, "node0_1_0");
  PLAOBJTimelineNode *node0_2_0 = PLAOBJTimelineNode::Create(3, "node0_2_0");

  node0->AddSubNode(node0_0_0);
  node0->AddSubNode(node0_1_0);
  node0->AddSubNode(node0_2_0);

  PLAOBJTimelineNode *node1_0_0 = PLAOBJTimelineNode::Create(3, "node1_0_0");

  node1->AddSubNode(node1_0_0);

  for (int i = 0; i < kNodeLength; i++) {
    GRA_PRINT("-- %2d : Update() --\n", i);
    node->Update();
  }
}
