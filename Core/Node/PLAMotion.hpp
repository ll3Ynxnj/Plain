//
// Created by Kentaro Kawai on 2021/09/06.
//

#ifndef ANHR_PLAMOTION_HPP
#define ANHR_PLAMOTION_HPP

#include "Core/Node/PLANode.hpp"
#include "PLAMotionType.hpp"

class PLAMotion final: public PLANode
{
  PLAMotionType _type = PLAMotionType::None;
  PLAProperty _begin = PLAProperty();
  PLAProperty _end = PLAProperty();
  PLAProperty _distance = PLAProperty();
  PLAFloat _duration = 0;

public:
  static const PLAMotion kNone;

  static PLAMotion *Create();
  static PLAMotion *CreateColor(const PLAColor &aBegin, const PLAColor &aEnd,
                                PLATimeInterval aDuration);
  static PLAMotion *CreateTranslation(const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                                      PLATimeInterval aDuration);
  static PLAMotion *CreateRotation(const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                                   PLATimeInterval aDuration);
  static PLAMotion *CreateScale(const PLAVec3 &aBegin, const PLAVec3 &aEnd,
                                PLATimeInterval aDuration);

  static const PLAProperty &MakeProperty(const PLAMotionType aType);

  static const char *GetNameOfType(PLAMotionType aType);

  PLAMotion();
  PLAMotion(PLAMotionType aType, const PLAColor &aBegin, const PLAColor &aEnd,
            PLATimeInterval aDuration);
  PLAMotion(PLAMotionType aType, const PLAVec3 &aBegin, const PLAVec3 &aEnd,
            PLATimeInterval aDuration);

  ~PLAMotion() override;

  const char *GetNameOfType() { return GetNameOfType(_type); };

  PLAMotionType GetMotionType() { return _type; }
  void GetProperty(std::map<PLAMotionType, PLAProperty> *aProperties) const;
};

#endif //ANHR_PLAMOTION_HPP
