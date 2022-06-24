//
// Created by Kentaro Kawai on 2021/09/06.
//

#include "PLATMLMotionNode.hpp"
#include "Object/PLAOBJApp.hpp"

//const PLATMLMotionNode PLATMLMotionNode::kNone = PLATMLMotionNode();

PLATMLMotionNode *PLATMLMotionNode::Create()
{
  PLATMLMotionNode *motion = new PLATMLMotionNode();
  motion->Bind();
  return motion;
}

PLATMLMotionNode *PLATMLMotionNode::CreateColor(const PLAColor &aBegin, const PLAColor &aEnd,
                                                PLATimeInterval aDuration)
{
  PLATMLMotionNode *motion =
    new PLATMLMotionNode(PLATMLMotionType::Color, aBegin, aEnd, aDuration);
  motion->Bind();
  return motion;
}

PLATMLMotionNode *PLATMLMotionNode::CreateTranslation(const PLAVec3 &aBegin,
                                                      const PLAVec3 &aEnd,
                                                      PLATimeInterval aDuration)
{
  PLATMLMotionNode *motion =
    new PLATMLMotionNode(PLATMLMotionType::Translation, aBegin, aEnd, aDuration);
  motion->Bind();
  return motion;
}

PLATMLMotionNode *PLATMLMotionNode::CreateRotation(const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                                                   PLATimeInterval aDuration)
{
  PLATMLMotionNode *motion =
    new PLATMLMotionNode(PLATMLMotionType::Rotation, aBegin, aEnd, aDuration);
  motion->Bind();
  return motion;
}

PLATMLMotionNode *PLATMLMotionNode::CreateScale(const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                                                PLATimeInterval aDuration)
{
  PLATMLMotionNode *motion =
    new PLATMLMotionNode(PLATMLMotionType::Scale, aBegin, aEnd, aDuration);
  motion->Bind();
  return motion;
}

const PLAProperty &PLATMLMotionNode::MakeProperty(const PLATMLMotionType aType)
{
  switch (aType)
  {
    case PLATMLMotionType::Color       : return PLAProperty::kColor;
    case PLATMLMotionType::Translation : return PLAProperty::kVec3;
    case PLATMLMotionType::Rotation    : return PLAProperty::kVec3;
    case PLATMLMotionType::Scale       : return PLAProperty::kVec3;
    default :
      PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Detect unexpected types.");
      return PLAProperty::kNone;
  }
}

const char *PLATMLMotionNode::GetNameOfType(PLATMLMotionType aType)
{
  static std::map<PLATMLMotionType, const char *> nameTable =
  {
    {PLATMLMotionType::Color,       "Color" },
    {PLATMLMotionType::Translation, "Translation" },
    {PLATMLMotionType::Rotation,    "Rotation" },
    {PLATMLMotionType::Scale,       "Scale" },
  };
  return nameTable.at(aType);
}

PLATMLMotionNode::PLATMLMotionNode():
  PLAOBJTimelineNode(PLAOBJTimelineNode::Type::Motion)
{

}

PLATMLMotionNode::PLATMLMotionNode(PLATMLMotionType aType, const PLAColor &aBegin,
                                   const PLAColor &aEnd, PLATimeInterval aDuration):
  PLAOBJTimelineNode(PLAOBJTimelineNode::Type::Motion, aDuration * PLAOBJApp::kRefreshRate),
  _type(aType),
  _begin(PLAProperty(aBegin)),
  _end(PLAProperty(aEnd)),
  _distance(PLAProperty(PLAColor(aEnd.r - aBegin.r, aEnd.g - aBegin.g,
                                 aEnd.b - aBegin.b, aEnd.a - aBegin.a)))//,
  //_duration(aDuration)
{

}

PLATMLMotionNode::PLATMLMotionNode(PLATMLMotionType aType, const PLAVec3 &aBegin,
                                   const PLAVec3 &aEnd, PLATimeInterval aDuration):
  PLAOBJTimelineNode(PLAOBJTimelineNode::Type::Motion, aDuration * PLAOBJApp::kRefreshRate),
  _type(aType),
  _begin(PLAProperty(aBegin)),
  _end(PLAProperty(aEnd)),
  _distance(PLAProperty(aEnd - aBegin))//,
  //_duration(aDuration)
{

}

PLATMLMotionNode::~PLATMLMotionNode()
{

}

void PLATMLMotionNode::GetProperty(std::map<PLATMLMotionType, PLAProperty> *aProperties) const
{
  if (_type == PLATMLMotionType::None) { return; }
  if (!aProperties->contains(_type))
  {
    (*aProperties)[_type] = PLATMLMotionNode::MakeProperty(_type);
  }
  GRA_PRINT("GetProgress() : %f\n", this->GetProgress());
  PLAProperty property = _begin;
  property += (_distance * this->GetProgress());
  if (_type == PLATMLMotionType::Translation)
  {
    PLAVec3 translation = property.GetVec3();
    GRA_PRINT("translation : %f, %f, %f\n",
              translation.x, translation.y, translation.z);
    GRA_PRINT("_distance.MulFloat(this->GetProgress().GetVec3().x) : %f\n",
              (_distance * this->GetProgress()).GetVec3().x);
  }
  (*aProperties)[_type] += property;
}
