//
// Created by Kentaro Kawai on 2021/09/06.
//

#include "PLAMotion.hpp"
#include "PLAApp.hpp"

//const PLAMotion PLAMotion::kNone = PLAMotion();

PLAMotion *PLAMotion::Create()
{
  PLAMotion *motion = new PLAMotion();
  motion->Bind();
  return motion;
}

PLAMotion *PLAMotion::CreateColor(const PLAColor &aBegin, const PLAColor &aEnd,
                                  PLATimeInterval aDuration)
{
  PLAMotion *motion =
    new PLAMotion(PLAMotionType::Color, aBegin, aEnd, aDuration);
  motion->Bind();
  return motion;
}

PLAMotion *PLAMotion::CreateTranslation(const PLAVec3 &aBegin,
                                        const PLAVec3 &aEnd,
                                        PLATimeInterval aDuration)
{
  PLAMotion *motion =
    new PLAMotion(PLAMotionType::Translation, aBegin, aEnd, aDuration);
  motion->Bind();
  return motion;
}

PLAMotion *PLAMotion::CreateRotation(const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                                     PLATimeInterval aDuration)
{
  PLAMotion *motion =
    new PLAMotion(PLAMotionType::Rotation, aBegin, aEnd, aDuration);
  motion->Bind();
  return motion;
}

PLAMotion *PLAMotion::CreateScale(const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                       PLATimeInterval aDuration)
{
  PLAMotion *motion =
    new PLAMotion(PLAMotionType::Scale, aBegin, aEnd, aDuration);
  motion->Bind();
  return motion;
}

const PLAProperty &PLAMotion::MakeProperty(const PLAMotionType aType)
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

const char *PLAMotion::GetNameOfType(PLAMotionType aType)
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

PLAMotion::PLAMotion():
  PLANode(PLANode::Type::Motion)
{

}

PLAMotion::PLAMotion(PLAMotionType aType, const PLAColor &aBegin,
                     const PLAColor &aEnd, PLATimeInterval aDuration):
  PLANode(PLANode::Type::Motion, aDuration * PLAApp::kRefreshRate),
  _type(aType),
  _begin(PLAProperty(aBegin)),
  _end(PLAProperty(aEnd)),
  _distance(PLAProperty(PLAColor(aEnd.r - aBegin.r, aEnd.g - aBegin.g,
                                 aEnd.b - aBegin.b, aEnd.a - aBegin.a))),
  _duration(aDuration)
{

}

PLAMotion::PLAMotion(PLAMotionType aType, const PLAVec3 &aBegin,
                     const PLAVec3 &aEnd, PLATimeInterval aDuration):
  PLANode(PLANode::Type::Motion, aDuration * PLAApp::kRefreshRate),
  _type(aType),
  _begin(PLAProperty(aBegin)),
  _end(PLAProperty(aEnd)),
  _distance(PLAProperty(aEnd - aBegin)),
  _duration(aDuration)
{

}

PLAMotion::~PLAMotion()
{

}

// GetPropertiesのほうが名称として適切なのでは？
void PLAMotion::GetProperty(std::map<PLAMotionType, PLAProperty> *aProperties) const
{
  //GRA_PRINT("GetProperty()\n");
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
