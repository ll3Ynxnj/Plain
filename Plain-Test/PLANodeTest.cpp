//
// Created by Kentaro Kawai on 2021/08/15.
//

#include "Object/Timeline/PLATimelineNode.hpp"

class PLANodeTest : public ::testing::Test
{
protected:
  //PLATimelineNode *_rootNode = nullptr;

  //std::vector<PLATimelineNode *>_subNodes = std::vector<PLATimelineNode *>();

  virtual void SetUp()
  {
    /*
    _rootNode = PLATimelineNode::Create(1);
    _subNodes.push_back(PLATimelineNode::Create(1));
    _subNodes.push_back(PLATimelineNode::Create(2));
    _subNodes.push_back(PLATimelineNode::Create(3));
    _subNodes.push_back(PLATimelineNode::Create(4));
    */
  }

  virtual void TearDown()
  {
    /*
    PLAObject::Delete(_rootNode);
    for (PLATimelineNode *node : _subNodes)
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
  std::vector<PLATimelineNode *> nodes = {
    PLATimelineNode::Create(1),
    PLATimelineNode::Create(2),
    PLATimelineNode::Create(3),
    PLATimelineNode::Create(4),
  };

  for (PLATimelineNode *node : nodes) {
    GRA_PRINT("-- nodes[%d] --------\n", i);
    node->SetFunction(PLATimelineNode::FunctionCode::OnStart, [i](PLATimelineNode *node) {
      GRA_PRINT("    nodes[%d] %4d OnStart\n", i, node->GetSteps());
    });
    node->SetFunction(PLATimelineNode::FunctionCode::OnUpdate, [i](PLATimelineNode *node) {
      PLAFloat progress = node->GetProgress();
      GRA_PRINT("    nodes[%d] %4d OnUpdate : progress : %f\n",
                i, node->GetSteps(), progress);
    });
    node->SetFunction(PLATimelineNode::FunctionCode::OnStop, [i](PLATimelineNode *node) {
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
  PLATimelineNode *node = PLATimelineNode::Create(kNodeLength, "node");

  PLATimelineNode *node0 = PLATimelineNode::Create(10, "node0");
  PLATimelineNode *node1 = PLATimelineNode::Create(10, "node1");
  PLATimelineNode *node2 = PLATimelineNode::Create(10, "node2");

  node->AddQueue(node0);
  node->AddQueue(node1);
  node->AddQueue(node2);

  PLATimelineNode *node0_0_0 = PLATimelineNode::Create(3, "node0_0_0");
  PLATimelineNode *node0_1_0 = PLATimelineNode::Create(3, "node0_1_0");
  PLATimelineNode *node0_2_0 = PLATimelineNode::Create(3, "node0_2_0");

  node0->AddSubNode(node0_0_0);
  node0->AddSubNode(node0_1_0);
  node0->AddSubNode(node0_2_0);

  PLATimelineNode *node1_0_0 = PLATimelineNode::Create(3, "node1_0_0");

  node1->AddSubNode(node1_0_0);

  for (int i = 0; i < kNodeLength; i++) {
    GRA_PRINT("-- %2d : Update() --\n", i);
    node->Update();
  }
}
