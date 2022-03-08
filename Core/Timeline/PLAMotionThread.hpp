//
// Created by Kentaro Kawai on 2022/02/27.
//

#ifndef ANHR_PLAMOTIONTHREAD_HPP
#define ANHR_PLAMOTIONTHREAD_HPP

#include "PLATimelineThread.hpp"
#include "PLAMotionNode.hpp"

class PLAMotionThread: public PLATimelineThread
{
public:
  static PLAMotionThread *Create();

  PLAMotionThread();
  ~PLAMotionThread() override {}
  void GetProperty(std::map<PLAMotionType, PLAProperty> *aProperties) const;
};

#endif //ANHR_PLAMOTIONTHREAD_HPP
