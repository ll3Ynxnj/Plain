// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/29.
//

#ifndef PLAIN_PLAAGTIMAGECLIP_HPP
#define PLAIN_PLAAGTIMAGECLIP_HPP


#include "plain/core/agent/PLAAgent.hpp"

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


#endif //PLAIN_PLAAGTIMAGECLIP_HPP
