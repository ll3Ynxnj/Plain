// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/29.
//

#include "PLAAGTImageClip.hpp"
#include "Object/PLAOBJImageClip.hpp"

PLAAGTImageClip::PLAAGTImageClip(PLAOBJImageClip *aOwner):
  PLAAgent(aOwner)
{

}

PLAAGTImageClip::~PLAAGTImageClip() noexcept
{

}

const PLAOBJImageClip *PLAAGTImageClip::GetImageClip() const
{
  return static_cast<const PLAOBJImageClip *>(this->GetOwner());
}

PLAOBJImageClip *PLAAGTImageClip::RefImageClip() const
{
  return static_cast<PLAOBJImageClip *>(this->RefOwner());
}
