// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/29.
//

#include "plain/core/agent/PLAAGTVideoClip.hpp"
#include "plain/core/object/PLAOBJVideoClip.hpp"

PLAAGTVideoClip::PLAAGTVideoClip(PLAOBJVideoClip *aOwner):
  PLAAgent(aOwner)
{

}

PLAAGTVideoClip::~PLAAGTVideoClip() noexcept
{

}

const PLAOBJVideoClip *PLAAGTVideoClip::GetVideoClip() const
{
  return static_cast<const PLAOBJVideoClip *>(this->GetOwner());
}

PLAOBJVideoClip *PLAAGTVideoClip::RefVideoClip() const
{
  return static_cast<PLAOBJVideoClip *>(this->RefOwner());
}
