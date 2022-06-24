//
// Created by Kentaro Kawai on 2022/02/27.
//

#include "PLATMLMotion.hpp"

PLATMLMotion *PLATMLMotion::Create()
{
  PLATMLMotion *thread = new PLATMLMotion();
  thread->Bind();
  return thread;
}

PLATMLMotion::PLATMLMotion():
  PLAOBJTimeline(nullptr)
{

}

void PLATMLMotion::GetProperties(std::map<PLATMLMotionType, PLAProperty> *aProperties) const
{
  //GRA_PRINT("GetProperties()\n");
  const PLAOBJTimelineNode *currentNode = this->GetCurrentNode();
  if (currentNode)
  {
    static_cast<const PLATMLMotionNode *>(currentNode)->GetProperty(aProperties);
  }
  for (const auto thread : this->GetThreads())
  {
    static_cast<const PLATMLMotion *>(thread.second)->GetProperties(aProperties);
  }
}
