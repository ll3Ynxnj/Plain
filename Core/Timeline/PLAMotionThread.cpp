//
// Created by Kentaro Kawai on 2022/02/27.
//

#include "PLAMotionThread.hpp"

PLAMotionThread *PLAMotionThread::Create()
{
  PLAMotionThread *thread = new PLAMotionThread();
  thread->Bind();
  return thread;
}

PLAMotionThread::PLAMotionThread():
  PLATimelineThread(nullptr)
{

}

// GetPropertiesのほうが名称として適切なのでは？
void PLAMotionThread::GetProperty(std::map<PLAMotionType, PLAProperty> *aProperties) const
{
  //GRA_PRINT("GetProperty()\n");
  const PLATimelineNode *currentNode = this->GetCurrentNode();
  if (currentNode)
  {
    static_cast<const PLAMotionNode *>(currentNode)->GetProperty(aProperties);
  }
  for (const auto thread : this->GetThreads())
  {
    static_cast<const PLAMotionThread *>(thread.second)->GetProperty(aProperties);
  }
}
