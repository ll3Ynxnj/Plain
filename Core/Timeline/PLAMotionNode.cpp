//
// Created by Kentaro Kawai on 2021/09/06.
//

#include "PLAMotionNode.hpp"
#include "PLAApp.hpp"

//const PLAMotionNode PLAMotionNode::kNone = PLAMotionNode();

PLAMotionNode *PLAMotionNode::Create()
{
  PLAMotionNode *motion = new PLAMotionNode();
  motion->Bind();
  return motion;
}

PLAMotionNode *PLAMotionNode::CreateColor(const PLAColor &aBegin, const PLAColor &aEnd,
                                          PLATimeInterval aDuration)
{
  PLAMotionNode *motion =
    new PLAMotionNode(PLAMotionType::Color, aBegin, aEnd, aDuration);
  motion->Bind();
  return motion;
}

PLAMotionNode *PLAMotionNode::CreateTranslation(const PLAVec3 &aBegin,
                                                const PLAVec3 &aEnd,
                                                PLATimeInterval aDuration)
{
  PLAMotionNode *motion =
    new PLAMotionNode(PLAMotionType::Translation, aBegin, aEnd, aDuration);
  motion->Bind();
  return motion;
}

PLAMotionNode *PLAMotionNode::CreateRotation(const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                                             PLATimeInterval aDuration)
{
  PLAMotionNode *motion =
    new PLAMotionNode(PLAMotionType::Rotation, aBegin, aEnd, aDuration);
  motion->Bind();
  return motion;
}

PLAMotionNode *PLAMotionNode::CreateScale(const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                                          PLATimeInterval aDuration)
{
  PLAMotionNode *motion =
    new PLAMotionNode(PLAMotionType::Scale, aBegin, aEnd, aDuration);
  motion->Bind();
  return motion;
}

const PLAProperty &PLAMotionNode::MakeProperty(const PLAMotionType aType)
{
  switch (aType)
  {
    case PLAMotionType::Color       : return PLAProperty::kColor;
    case PLAMotionType::Translation : return PLAProperty::kVec3;
    case PLAMotionType::Rotation    : return PLAProperty::kVec3;
    case PLAMotionType::Scale       : return PLAProperty::kVec3;
    default : PLA_ERROR_ISSUE(PLAErrorType::Assert, "Detect unexpected types.");
  }
}

const char *PLAMotionNode::GetNameOfType(PLAMotionType aType)
{
  static std::map<PLAMotionType, const char *> nameTable =
  {
    { PLAMotionType::Color, "Color" },
    { PLAMotionType::Translation, "Translation" },
    { PLAMotionType::Rotation, "Rotation" },
    { PLAMotionType::Scale, "Scale" },
  };
  return nameTable.at(aType);
}

PLAMotionNode::PLAMotionNode():
  PLATimelineNode(PLATimelineNode::Type::Motion)
{

}

PLAMotionNode::PLAMotionNode(PLAMotionType aType, const PLAColor &aBegin,
                             const PLAColor &aEnd, PLATimeInterval aDuration):
  PLATimelineNode(PLATimelineNode::Type::Motion, aDuration * PLAApp::kRefreshRate),
  _type(aType),
  _begin(PLAProperty(aBegin)),
  _end(PLAProperty(aEnd)),
  _distance(PLAProperty(PLAColor(aEnd.r - aBegin.r, aEnd.g - aBegin.g,
                                 aEnd.b - aBegin.b, aEnd.a - aBegin.a))),
  _duration(aDuration)
{

}

PLAMotionNode::PLAMotionNode(PLAMotionType aType, const PLAVec3 &aBegin,
                             const PLAVec3 &aEnd, PLATimeInterval aDuration):
  PLATimelineNode(PLATimelineNode::Type::Motion, aDuration * PLAApp::kRefreshRate),
  _type(aType),
  _begin(PLAProperty(aBegin)),
  _end(PLAProperty(aEnd)),
  _distance(PLAProperty(aEnd - aBegin)),
  _duration(aDuration)
{

}

PLAMotionNode::~PLAMotionNode()
{

}

void PLAMotionNode::GetProperty(std::map<PLAMotionType, PLAProperty> *aProperties) const
{
  if (_type == PLAMotionType::None) { return; }
  if (!aProperties->contains(_type))
  {
    (*aProperties)[_type] = PLAMotionNode::MakeProperty(_type);
  }
  GRA_PRINT("GetProgress() : %f\n", this->GetProgress());
  PLAProperty property = _begin;
  property += (_distance * this->GetProgress());
  if (_type == PLAMotionType::Translation)
  {
    PLAVec3 translation = property.GetVec3();
    GRA_PRINT("translation : %f, %f, %f\n",
              translation.x, translation.y, translation.z);
    GRA_PRINT("_distance.MulFloat(this->GetProgress().GetVec3().x) : %f\n",
              (_distance * this->GetProgress()).GetVec3().x);
  }
  (*aProperties)[_type] += property;
}
