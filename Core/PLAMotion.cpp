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

/*
PLAMotion::PLAMotion():
  PLANode()
{

}
*/

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
