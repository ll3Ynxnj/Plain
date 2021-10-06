//
// Created by Kentaro Kawai on 2021/09/06.
//

#include "PLAMotion.hpp"
#include "PLAApp.hpp"
/*
static PLAMotion *PLAMotion::Create()
{
  return new PLAMotion();
}
*/

PLAMotion *PLAMotion::CreateColor(const PLAColor &aColor,
                                  PLATimeInterval aDuration)
{
  return new PLAMotion(PLAMotionType::Color, aColor, aDuration);
}

PLAMotion *PLAMotion::CreateTranslation(const PLAVec3 &aTranslation,
                                        PLATimeInterval aDuration)
{
  return new PLAMotion(PLAMotionType::Translation, aTranslation, aDuration);
}

PLAMotion *PLAMotion::CreateRotation(const PLAVec3 &aRotation,
                                     PLATimeInterval aDuration)
{
  return new PLAMotion(PLAMotionType::Rotation, aRotation, aDuration);
}

PLAMotion *CreateScale(const PLAVec3 &aScale,
                       PLATimeInterval aDuration)
{
  return new PLAMotion(PLAMotionType::Scale, aScale, aDuration);
}

const PLAProperty &PLAMotion::MakeProperty(const PLAMotionType aType)
{
  switch (aType)
  {
    case PLAMotionType::Translation : return kPLAPropertyVec3;
    case PLAMotionType::Rotation    : return kPLAPropertyVec3;
    case PLAMotionType::Scale       : return kPLAPropertyVec3;
    case PLAMotionType::Color       : return kPLAPropertyColor;
    //case PLAMotionType::None        : return kPLAPropertyNone;
    default : PLA_ERROR_ISSUE(PLAErrorType::Assert, "Detect unexpected types.");
  }
}

PLAMotion::PLAMotion():
  PLANode()
{

}

PLAMotion::PLAMotion(PLAMotionType aType, const PLAColor &aDistance,
                     PLATimeInterval aDuration):
  PLANode(aDuration * PLAApp::kRefreshRate),
  _type(aType),
  _distance(PLAProperty(aDistance)),
  _duration(aDuration)
{

}

PLAMotion::PLAMotion(PLAMotionType aType, const PLAVec3 &aDistance,
                     PLATimeInterval aDuration):
  PLANode(aDuration * PLAApp::kRefreshRate),
  _type(aType),
  _distance(PLAProperty(aDistance)),
  _duration(aDuration)
{

}

PLAMotion::~PLAMotion()
{

}

/*
const PLAProperty &PLAMotion::GetProperty()
{

}
 */

/*
void PLAMotion::Update()
{
  PLANode::Update();

}
 */

void PLAMotion::GetProperty(std::map<PLAMotionType, PLAProperty> *aProperties) const
{
  const PLANode *currentNode = this->GetCurrentNode();
  if (currentNode)
  {
    static_cast<const PLAMotion *>(currentNode)->GetProperty(aProperties);
  }
  for (const PLANode *branch : this->GetBranch())
  {
    static_cast<const PLAMotion *>(branch)->GetProperty(aProperties);
  }
  if (_type == PLAMotionType::None) { return; }
  if (!aProperties->contains(_type))
  {
    (*aProperties)[_type] = PLAMotion::MakeProperty(_type);
  }
  (*aProperties)[_type].Add(_distance);
}
