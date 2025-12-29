// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLACOMPUTEMODE_HPP
#define PLAIN_ENGINE_PLACOMPUTEMODE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"

// Compute execution mode for DNN inference
enum class PLAComputeMode : PLAInt
{
  Default,   // OpenCV default (CPU)
  CPU,       // Explicit CPU
  CUDA,      // NVIDIA CUDA (for Jetson, etc.)
  OpenCL,    // OpenCL (Intel, AMD, etc.)
  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLACOMPUTEMODE_HPP
