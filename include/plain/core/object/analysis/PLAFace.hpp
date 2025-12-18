#ifndef PLAIN_PLAFACE_HPP
#define PLAIN_PLAFACE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"
#include "plain/core/primitive/PLAPRMRect.hpp"
#include <vector>

using PLAFaceId = PLAId;
static const PLAFaceId kPLAFaceIdNone = kPLAIdUndefined;

struct PLAFace
{
  PLAFaceId id = kPLAFaceIdNone;
  PLARect boundingRect = kPLARectNone;
  PLAFloat confidence = 0.0f;

  PLAFace() = default;
  PLAFace(const PLARect &aRect, PLAFloat aConfidence)
    : boundingRect(aRect), confidence(aConfidence) {}
};
static const PLAFace kPLAFaceNone = PLAFace();

struct PLAFaceDetectionResult
{
  std::vector<PLAFace> faces;
  PLAUInt64 frameNumber = 0;
  bool isValid = false;

  PLAFaceDetectionResult() = default;

  PLASize GetFaceCount() const { return faces.size(); }
  bool HasFaces() const { return !faces.empty(); }
};
static const PLAFaceDetectionResult kPLAFaceDetectionResultNone = PLAFaceDetectionResult();

#endif // PLAIN_PLAFACE_HPP
