//
// Created by Kentaro Kawai on 2022/02/27.
//

#include "PLATMLMotion.hpp"
#include "Agent/PLAAGTMotion.hpp"

PLATMLMotion *PLATMLMotion::Object(const PLAString &aName)
{
  auto object = PLAObject::Object(PLAObjectType::Motion, aName);
  return static_cast<PLATMLMotion *>(object);
}

PLATMLMotion *PLATMLMotion::Object(PLAId aId)
{
  auto object = PLAObject::Object(PLAObjectType::Motion, aId);
  return static_cast<PLATMLMotion *>(object);
}

PLATMLMotion *PLATMLMotion::Create()
{
  PLATMLMotion *thread = new PLATMLMotion();
  thread->Bind();
  return thread;
}

PLATMLMotion::PLATMLMotion():
  PLAOBJTimeline(PLAObjectType::Motion)
{

}

PLATMLMotion::PLATMLMotion(const PLAString &aName):
  PLAOBJTimeline(PLAObjectType::Motion, aName)
{

}

PLAAGTMotion PLATMLMotion::AssignAgent()
{
  return PLAAGTMotion(this);
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
