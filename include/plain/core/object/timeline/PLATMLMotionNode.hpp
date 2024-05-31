//
// Created by Kentaro Kawai on 2021/09/06.
//

#ifndef ANHR_PLATMLMOTIONNODE_HPP
#define ANHR_PLATMLMOTIONNODE_HPP

#include "plain/core/object/timeline/PLAOBJTimelineNode.hpp"
#include "plain/core/object/timeline/PLATMLMotionType.hpp"
#include "plain/core/PLAEasing.hpp"

class PLAAGTMotionNode;

class PLATMLMotionNode final: public PLAOBJTimelineNode
{
  PLATMLMotionType _type = PLATMLMotionType::None;
  PLAProperty _begin = PLAProperty();
  PLAProperty _end = PLAProperty();
  PLAProperty _distance = PLAProperty();
  PLAEasing::Type _easingType = PLAEasing::Type::Linear;
  //PLAFloat _duration = 0;

public:
  static const PLATMLMotionNode kNone;

  static PLATMLMotionNode *Object(const PLAString &aName);
  static PLATMLMotionNode *Object(PLAId aId);
  static PLATMLMotionNode *Create();
  static PLATMLMotionNode *CreateColor(const PLAColor &aBegin,
                                       const PLAColor &aEnd,
                                       PLAEasing::Type aEasingType,
                                       PLATimeInterval aDuration);
  static PLATMLMotionNode *CreateTranslation(const PLAVec3f &aBegin,
                                             const PLAVec3f &aEnd,
                                             PLAEasing::Type aEasingType,
                                             PLATimeInterval aDuration);
  static PLATMLMotionNode *CreateRotation(const PLAVec3f &aBegin,
                                          const PLAVec3f &aEnd,
                                          PLAEasing::Type aEasingType,
                                          PLATimeInterval aDuration);
  static PLATMLMotionNode *CreateScale(const PLAVec3f &aBegin,
                                       const PLAVec3f &aEnd,
                                       PLAEasing::Type aEasingType,
                                       PLATimeInterval aDuration);

  static const PLAProperty &MakeProperty(const PLATMLMotionType aType);

  static const char *GetNameOfType(PLATMLMotionType aType);

  PLATMLMotionNode();
  PLATMLMotionNode(PLATMLMotionType aType,
                   const PLAColor &aBegin, const PLAColor &aEnd,
                   PLAEasing::Type aEasingType, PLATimeInterval aDuration);
  PLATMLMotionNode(PLATMLMotionType aType,
                   const PLAVec3f &aBegin, const PLAVec3f &aEnd,
                   PLAEasing::Type aEasingType, PLATimeInterval aDuration);

  ~PLATMLMotionNode() override;

  PLAAGTMotionNode AssignAgent();

  const char *GetNameOfType() { return GetNameOfType(_type); };

  PLATMLMotionType GetMotionType() { return _type; }
  void GetProperty(std::map<PLATMLMotionType, PLAProperty> *aProperties) const;
};

#endif //ANHR_PLATMLMOTIONNODE_HPP
