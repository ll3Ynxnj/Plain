//
// Created by Kentaro Kawai on 2021/09/06.
//

#ifndef ANHR_PLAMOTION_HPP
#define ANHR_PLAMOTION_HPP

#include "PLANode.hpp"
#include "PLAMotionType.hpp"

class PLAMotion final: public PLANode
{
  PLAMotionType _type = PLAMotionType::None;
  PLAProperty _distance = PLAProperty();
  PLAFloat _duration = 0;

public:
  //static PLAMotion *Create();
  static PLAMotion *CreateColor(const PLAColor &aColor,
                                PLATimeInterval aDuration);
  static PLAMotion *CreateTranslation(const PLAVec3 &aTranslation,
                                      PLATimeInterval aDuration);
  static PLAMotion *CreateRotation(const PLAVec3 &aRotation,
                                   PLATimeInterval aDuration);
  static PLAMotion *CreateScale(const PLAVec3 &aScale,
                                PLATimeInterval aDuration);

  static const PLAProperty &MakeProperty(const PLAMotionType aType);

  PLAMotion();
  PLAMotion(PLAMotionType aType, const PLAColor &aDistance,
            PLATimeInterval aDuration);
  PLAMotion(PLAMotionType aType, const PLAVec3 &aDistance,
            PLATimeInterval aDuration);
  ~PLAMotion();

  //void Update() override;

  PLAMotionType GetMotionType() { return _type; }
  void GetProperty(std::map<PLAMotionType, PLAProperty> *aProperties) const;
};

#endif //ANHR_PLAMOTION_HPP
