//
// Created by Kentaro Kawai on 2022/02/27.
//

#ifndef ANHR_PLAMOTIONTHREAD_HPP
#define ANHR_PLAMOTIONTHREAD_HPP

#include "PLANodeThread.hpp"
#include "PLAMotion.hpp"

class PLAMotionThread: public PLANodeThread
{
public:
  static PLAMotionThread *Create();

  PLAMotionThread();
  ~PLAMotionThread() override {}
  void GetProperty(std::map<PLAMotionType, PLAProperty> *aProperties) const;
};

#endif //ANHR_PLAMOTIONTHREAD_HPP
