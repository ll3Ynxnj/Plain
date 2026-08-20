//
// Created by Kentaro Kawai on 2022/02/27.
//

#ifndef PLAIN_PLATMLMOTION_HPP
#define PLAIN_PLATMLMOTION_HPP

#include "plain/core/object/timeline/PLAOBJTimeline.hpp"
#include "plain/core/object/timeline/PLATMLMotionNode.hpp"

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

#endif //PLAIN_PLATMLMOTION_HPP
