// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/07/20.
//

#ifndef ANHR_PLAMOTIONHOLDER_HPP
#define ANHR_PLAMOTIONHOLDER_HPP


#include "PLATimelineHolder.hpp"

class PLATMLMotion;

class PLAMotionHolder: public PLATimelineHolder
{
public:
  const PLATMLMotion *GetMotion() const;
};


#endif //ANHR_PLAMOTIONHOLDER_HPP
