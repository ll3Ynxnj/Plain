// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAOBJFRAMESOURCE_HPP
#define PLAIN_ENGINE_PLAOBJFRAMESOURCE_HPP

#include "plain/core/PLAFunctionCode.hpp"
#include "grain/object/GRAOBJFunctor.hpp"
#include <opencv2/opencv.hpp>
#include <functional>

// PLAOBJFrameSource: Abstract interface for frame providers
// Implementations: PLAOBJCameraStream, PLAOBJVideoFileStream (future)
class PLAOBJFrameSource
{
public:
  using Functor = GRAOBJFunctor<const cv::Mat &, PLAFunctionCode::FrameSource>;

  virtual ~PLAOBJFrameSource() = default;

  virtual cv::Mat GetCurrentFrame() const = 0;

  virtual void SetFunction(PLAFunctionCode::FrameSource aKey,
                           const std::function<void(const cv::Mat &)> &aFunc) = 0;

protected:
  virtual void RunFunction(PLAFunctionCode::FrameSource aKey,
                           const cv::Mat &aFrame) const = 0;
};

#endif // PLAIN_ENGINE_PLAOBJFRAMESOURCE_HPP
