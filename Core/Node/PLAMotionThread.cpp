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
  PLANodeThread(nullptr)
{

}

// GetPropertiesのほうが名称として適切なのでは？
void PLAMotionThread::GetProperty(std::map<PLAMotionType, PLAProperty> *aProperties) const
{
  //GRA_PRINT("GetProperty()\n");
  const PLANode *currentNode = this->GetCurrentNode();
  if (currentNode)
  {
    static_cast<const PLAMotion *>(currentNode)->GetProperty(aProperties);
  }
  for (const PLANodeThread *thread : this->GetThreads())
  {
    static_cast<const PLAMotionThread *>(thread)->GetProperty(aProperties);
  }
}
