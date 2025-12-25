// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLAAGTFRAMEANALYZER_HPP
#define PLAIN_ENGINE_PLAAGTFRAMEANALYZER_HPP

#include "plain/core/agent/PLAAgent.hpp"
#include "plain/core/object/analysis/PLAFace.hpp"
#include "plain/core/PLAFunctionCode.hpp"
#include <functional>

class PLAOBJFrameAnalyzer;
class PLAOBJFrameSource;

class PLAAGTFrameAnalyzer final : public PLAAgent
{
public:
  explicit PLAAGTFrameAnalyzer(PLAOBJFrameAnalyzer *aOwner);
  virtual ~PLAAGTFrameAnalyzer() noexcept;

  void EnableFaceDetection(bool aEnable) const;
  bool IsFaceDetectionEnabled() const;

  void EnableFaceTracking(bool aEnable) const;
  bool IsFaceTrackingEnabled() const;

  void EnableSmileDetection(bool aEnable) const;
  bool IsSmileDetectionEnabled() const;

  void AttachToSource(PLAOBJFrameSource *aSource) const;

  void SetFunction(PLAFunctionCode::FrameAnalyzer aKey,
                   const std::function<void(PLAAGTFrameAnalyzer)> &aFunc) const;

  PLAFaceDetectionResult GetResult() const;

protected:
  const PLAOBJFrameAnalyzer *GetAnalyzer() const;
  PLAOBJFrameAnalyzer *RefAnalyzer() const;
};

#endif // PLAIN_ENGINE_PLAAGTFRAMEANALYZER_HPP
