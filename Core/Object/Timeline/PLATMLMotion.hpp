//
// Created by Kentaro Kawai on 2022/02/27.
//

#ifndef ANHR_PLATMLMOTION_HPP
#define ANHR_PLATMLMOTION_HPP

#include "PLAOBJTimeline.hpp"
#include "PLATMLMotionNode.hpp"

class PLATMLMotion: public PLAOBJTimeline
{
public:
  static PLATMLMotion *Create();

  PLATMLMotion();
  ~PLATMLMotion() override {}
  void GetProperties(std::map<PLATMLMotionType, PLAProperty> *aProperties) const;
};

#endif //ANHR_PLATMLMOTION_HPP
