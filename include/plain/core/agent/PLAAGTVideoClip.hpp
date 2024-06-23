// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/29.
//

#ifndef PLAIN_PLAAGTVIDEOCLIP_HPP
#define PLAIN_PLAAGTVIDEOCLIP_HPP


#include "plain/core/agent/PLAAgent.hpp"

class PLAOBJVideoClip;

class PLAAGTVideoClip: public PLAAgent
{
public:
  /// Agent is const method only.
  PLAAGTVideoClip() = delete;
  explicit PLAAGTVideoClip(PLAOBJVideoClip *aOwner);
  virtual ~PLAAGTVideoClip() noexcept;

//protected:
  const PLAOBJVideoClip *GetVideoClip() const;
  PLAOBJVideoClip *RefVideoClip() const;
};


#endif //PLAIN_PLAAGTVIDEOCLIP_HPP
