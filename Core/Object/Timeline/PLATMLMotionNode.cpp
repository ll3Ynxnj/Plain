//
// Created by Kentaro Kawai on 2021/09/06.
//

#include "PLATMLMotionNode.hpp"
#include "Core/App/PLAApp.hpp"
#include "Agent/PLAAGTMotionNode.hpp"

PLATMLMotionNode *PLATMLMotionNode::Object(const PLAString &aName)
{
  auto object = PLAObject::Object(PLAObjectType::MotionNode, aName);
  return static_cast<PLATMLMotionNode *>(object);
}

PLATMLMotionNode *PLATMLMotionNode::Object(PLAId aId)
{
  auto object = PLAObject::Object(PLAObjectType::MotionNode, aId);
  return static_cast<PLATMLMotionNode *>(object);
}

PLATMLMotionNode *PLATMLMotionNode::Create()
{
  PLATMLMotionNode *motion = new PLATMLMotionNode();
  motion->Bind();
  return motion;
}

PLATMLMotionNode *PLATMLMotionNode::CreateColor(const PLAColor &aBegin,
                                                const PLAColor &aEnd,
                                                PLAEasing::Type aEasingType,
                                                PLATimeInterval aDuration)
{
  PLATMLMotionNode *motion =
    new PLATMLMotionNode(PLATMLMotionType::Color, aBegin, aEnd,
                         aEasingType, aDuration);
  motion->Bind();
  return motion;
}

PLATMLMotionNode *PLATMLMotionNode::CreateTranslation(const PLAVec3f &aBegin,
                                                      const PLAVec3f &aEnd,
                                                      PLAEasing::Type aEasingType,
                                                      PLATimeInterval aDuration)
{
  PLATMLMotionNode *motion =
    new PLATMLMotionNode(PLATMLMotionType::Translation, aBegin, aEnd,
                         aEasingType, aDuration);
  motion->Bind();
  return motion;
}

PLATMLMotionNode *PLATMLMotionNode::CreateRotation(const PLAVec3f &aBegin,
                                                   const PLAVec3f &aEnd,
                                                   PLAEasing::Type aEasingType,
                                                   PLATimeInterval aDuration)
{
  PLATMLMotionNode *motion =
    new PLATMLMotionNode(PLATMLMotionType::Rotation, aBegin, aEnd,
                         aEasingType, aDuration);
  motion->Bind();
  return motion;
}

PLATMLMotionNode *PLATMLMotionNode::CreateScale(const PLAVec3f &aBegin,
                                                const PLAVec3f &aEnd,
                                                PLAEasing::Type aEasingType,
                                                PLATimeInterval aDuration)
{
  PLATMLMotionNode *motion =
    new PLATMLMotionNode(PLATMLMotionType::Scale, aBegin, aEnd,
                         aEasingType, aDuration);
  motion->Bind();
  return motion;
}

const PLAProperty &PLATMLMotionNode::MakeProperty(const PLATMLMotionType aType)
{
  switch (aType)
  {
    case PLATMLMotionType::Color       : return PLAProperty::kColor;
    case PLATMLMotionType::Translation : return PLAProperty::kVec3f;
    case PLATMLMotionType::Rotation    : return PLAProperty::kVec3f;
    case PLATMLMotionType::Scale       : return PLAProperty::kVec3f;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "Detect unexpected types.");
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

PLATMLMotionNode::PLATMLMotionNode(PLATMLMotionType aType,
                                   const PLAColor &aBegin, const PLAColor &aEnd,
                                   PLAEasing::Type aEasingType,
                                   PLATimeInterval aDuration):
  PLAOBJTimelineNode(PLAOBJTimelineNode::Type::Motion,
                     aDuration * PLAApp::kRefreshRate),
  _type(aType),
  _begin(PLAProperty(aBegin)),
  _end(PLAProperty(aEnd)),
  _easingType(aEasingType),
  _distance(PLAProperty(PLAColor(aEnd.r - aBegin.r, aEnd.g - aBegin.g,
                                 aEnd.b - aBegin.b, aEnd.a - aBegin.a)))//,
  //_duration(aDuration)
{

}

PLATMLMotionNode::PLATMLMotionNode(PLATMLMotionType aType,
                                   const PLAVec3f &aBegin, const PLAVec3f &aEnd,
                                   PLAEasing::Type aEasingType,
                                   PLATimeInterval aDuration):
  PLAOBJTimelineNode(PLAOBJTimelineNode::Type::Motion,
                     aDuration * PLAApp::kRefreshRate),
  _type(aType),
  _begin(PLAProperty(aBegin)),
  _end(PLAProperty(aEnd)),
  _easingType(aEasingType),
  _distance(PLAProperty(aEnd - aBegin))//,
  //_duration(aDuration)
{

}

PLATMLMotionNode::~PLATMLMotionNode()
{

}

PLAAGTMotionNode PLATMLMotionNode::AssignAgent()
{
  return PLAAGTMotionNode(this);
}

void PLATMLMotionNode::GetProperty(std::map<PLATMLMotionType,
                                   PLAProperty> *aProperties) const
{
  if (_type == PLATMLMotionType::None) { return; }
  if (!aProperties->contains(_type))
  {
    (*aProperties)[_type] = PLATMLMotionNode::MakeProperty(_type);
  }
  GRA_PRINT("GetProgress() : %f\n", this->GetProgress());
  PLAProperty property = _begin;
  auto progress = this->GetProgress();
  auto easedProgress = GRALIBEasing::GetEasing(_easingType, progress);
  property += (_distance * easedProgress);

  switch (_type) {
    case PLATMLMotionType::Translation:
    case PLATMLMotionType::Rotation:
      (*aProperties)[_type] += property;
      break;
    case PLATMLMotionType::Scale:
    case PLATMLMotionType::Color:
      (*aProperties)[_type] *= property;
      break;
  }

  //-- for debug
  if (_type == PLATMLMotionType::Translation)
  {
    PLAVec3f translation = property.GetVec3f();
    GRA_PRINT("translation : %f, %f, %f\n",
              translation.x, translation.y, translation.z);
    GRA_PRINT("_distance.MulFloat(this->GetProgress().GetVec3f().x) : %f\n",
              (_distance * this->GetProgress()).GetVec3f().x);
  }

  if (_type == PLATMLMotionType::Color)
  {
    PLAColor color = property.GetColor();
    GRA_PRINT("color : %f, %f, %f, %f\n",
              color.r, color.g, color.b, color.a);
    GRA_PRINT("_distance.MulFloat(this->GetProgress().GetColor().a) : %f\n",
              (_distance * this->GetProgress()).GetColor().a);
    GRA_TRACE("");
  }
}
