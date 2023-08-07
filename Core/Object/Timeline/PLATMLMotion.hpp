//
// Created by Kentaro Kawai on 2022/02/27.
//

#ifndef ANHR_PLATMLMOTION_HPP
#define ANHR_PLATMLMOTION_HPP

#include "PLAOBJTimeline.hpp"
#include "PLATMLMotionNode.hpp"

class PLAAGTMotion;

class PLATMLMotion: public PLAOBJTimeline
{
public:
  static PLATMLMotion *Object(const PLAString &aName);
  static PLATMLMotion *Object(PLAId aId);

  static PLATMLMotion *Create();

  PLATMLMotion();
  PLATMLMotion(const PLAString &aName);
  ~PLATMLMotion() override {}

  PLAAGTMotion AssignAgent();

  void GetProperties(std::map<PLATMLMotionType, PLAProperty> *aProperties) const;
};

#endif //ANHR_PLATMLMOTION_HPP
