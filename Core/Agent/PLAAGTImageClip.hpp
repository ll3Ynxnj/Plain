// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/29.
//

#ifndef ANHR_PLAAGTIMAGECLIP_HPP
#define ANHR_PLAAGTIMAGECLIP_HPP


#include "PLAAgent.hpp"

class PLAOBJImageClip;

class PLAAGTImageClip: public PLAAgent
{
public:
  /// Agent is const method only.
  PLAAGTImageClip() = delete;
  explicit PLAAGTImageClip(PLAOBJImageClip *aOwner);
  virtual ~PLAAGTImageClip() noexcept;

//protected:
  const PLAOBJImageClip *GetImageClip() const;
  PLAOBJImageClip *RefImageClip() const;
};


#endif //ANHR_PLAAGTIMAGECLIP_HPP
