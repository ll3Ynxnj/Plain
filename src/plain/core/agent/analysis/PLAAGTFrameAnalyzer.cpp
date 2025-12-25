// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/core/agent/analysis/PLAAGTFrameAnalyzer.hpp"
#include "plain/core/object/analysis/PLAOBJFrameAnalyzer.hpp"

PLAAGTFrameAnalyzer::PLAAGTFrameAnalyzer(PLAOBJFrameAnalyzer *aOwner) :
  PLAAgent(aOwner)
{
}

PLAAGTFrameAnalyzer::~PLAAGTFrameAnalyzer() noexcept
{
}

void PLAAGTFrameAnalyzer::EnableFaceDetection(bool aEnable) const
{
  RefAnalyzer()->EnableFaceDetection(aEnable);
}

bool PLAAGTFrameAnalyzer::IsFaceDetectionEnabled() const
{
  return GetAnalyzer()->IsFaceDetectionEnabled();
}

void PLAAGTFrameAnalyzer::EnableFaceTracking(bool aEnable) const
{
  RefAnalyzer()->EnableFaceTracking(aEnable);
}

bool PLAAGTFrameAnalyzer::IsFaceTrackingEnabled() const
{
  return GetAnalyzer()->IsFaceTrackingEnabled();
}

void PLAAGTFrameAnalyzer::EnableSmileDetection(bool aEnable) const
{
  RefAnalyzer()->EnableSmileDetection(aEnable);
}

bool PLAAGTFrameAnalyzer::IsSmileDetectionEnabled() const
{
  return GetAnalyzer()->IsSmileDetectionEnabled();
}

void PLAAGTFrameAnalyzer::AttachToSource(PLAOBJFrameSource *aSource) const
{
  RefAnalyzer()->AttachToSource(aSource);
}

void PLAAGTFrameAnalyzer::SetFunction(
  PLAFunctionCode::FrameAnalyzer aKey,
  const std::function<void(const PLAFaceDetectionResult &)> &aFunc) const
{
  RefAnalyzer()->SetFunction(aKey, aFunc);
}

PLAFaceDetectionResult PLAAGTFrameAnalyzer::GetResult() const
{
  return GetAnalyzer()->GetResult();
}

const PLAOBJFrameAnalyzer *PLAAGTFrameAnalyzer::GetAnalyzer() const
{
  return static_cast<const PLAOBJFrameAnalyzer *>(GetOwner());
}

PLAOBJFrameAnalyzer *PLAAGTFrameAnalyzer::RefAnalyzer() const
{
  return static_cast<PLAOBJFrameAnalyzer *>(RefOwner());
}
