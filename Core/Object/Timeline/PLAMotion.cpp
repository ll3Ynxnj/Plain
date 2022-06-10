//
// Created by Kentaro Kawai on 2022/02/27.
//

#include "PLAMotion.hpp"

PLAMotion *PLAMotion::Create()
{
  PLAMotion *thread = new PLAMotion();
  thread->Bind();
  return thread;
}

PLAMotion::PLAMotion():
  PLATimeline(nullptr)
{

}

void PLAMotion::GetProperties(std::map<PLAMotionType, PLAProperty> *aProperties) const
{
  //GRA_PRINT("GetProperties()\n");
  const PLATimelineNode *currentNode = this->GetCurrentNode();
  if (currentNode)
  {
    static_cast<const PLAMotionNode *>(currentNode)->GetProperty(aProperties);
  }
  for (const auto thread : this->GetThreads())
  {
    static_cast<const PLAMotion *>(thread.second)->GetProperties(aProperties);
  }
}
