//
// Created by Kentaro Kawai on 2022/02/27.
//

#ifndef ANHR_PLAMOTION_HPP
#define ANHR_PLAMOTION_HPP

#include "PLATimeline.hpp"
#include "PLAMotionNode.hpp"

class PLAMotion: public PLATimeline
{
public:
  static PLAMotion *Create();

  PLAMotion();
  ~PLAMotion() override {}
  void GetProperties(std::map<PLAMotionType, PLAProperty> *aProperties) const;
};

#endif //ANHR_PLAMOTION_HPP
