//
// Created by Kentaro Kawai on 2021/09/06.
//

#ifndef ANHR_PLAMOTIONNODE_HPP
#define ANHR_PLAMOTIONNODE_HPP

#include "Timeline/PLATimelineNode.hpp"
#include "PLAMotionType.hpp"

class PLAMotionNode final: public PLATimelineNode
{
  PLAMotionType _type = PLAMotionType::None;
  PLAProperty _begin = PLAProperty();
  PLAProperty _end = PLAProperty();
  PLAProperty _distance = PLAProperty();
  //PLAFloat _duration = 0;

public:
  static const PLAMotionNode kNone;

  static PLAMotionNode *Create();
  static PLAMotionNode *CreateColor(const PLAColor &aBegin, const PLAColor &aEnd,
                                    PLATimeInterval aDuration);
  static PLAMotionNode *CreateTranslation(const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                                          PLATimeInterval aDuration);
  static PLAMotionNode *CreateRotation(const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                                       PLATimeInterval aDuration);
  static PLAMotionNode *CreateScale(const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                                    PLATimeInterval aDuration);

  static const PLAProperty &MakeProperty(const PLAMotionType aType);

  static const char *GetNameOfType(PLAMotionType aType);

  PLAMotionNode();
  PLAMotionNode(PLAMotionType aType, const PLAColor &aBegin, const PLAColor &aEnd,
                PLATimeInterval aDuration);
  PLAMotionNode(PLAMotionType aType, const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                PLATimeInterval aDuration);

  ~PLAMotionNode() override;

  const char *GetNameOfType() { return GetNameOfType(_type); };

  PLAMotionType GetMotionType() { return _type; }
  void GetProperty(std::map<PLAMotionType, PLAProperty> *aProperties) const;
};

#endif //ANHR_PLAMOTIONNODE_HPP
