#ifndef PLAIN_ENGINE_PLAOBJFACETRACKER_HPP
#define PLAIN_ENGINE_PLAOBJFACETRACKER_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/analysis/PLAFace.hpp"
#include <vector>

struct PLATrackedFace
{
  PLAFaceId id = kPLAFaceIdNone;
  PLARect boundingRect = kPLARectNone;
  PLAFloat confidence = 0.0f;
  PLAInt missedFrames = 0;

  PLATrackedFace() = default;
  PLATrackedFace(PLAFaceId aId, const PLARect &aRect, PLAFloat aConfidence)
    : id(aId), boundingRect(aRect), confidence(aConfidence), missedFrames(0) {}
};

class PLAOBJFaceTracker : public PLAObject
{
  std::vector<PLATrackedFace> _trackedFaces;
  PLAFaceId _nextId = 0;
  PLAFloat _iouThreshold = 0.3f;
  PLAInt _maxMissedFrames = 5;

public:
  static PLAOBJFaceTracker *Create();

  PLAOBJFaceTracker();
  ~PLAOBJFaceTracker();

  void Update(PLAFaceDetectionResult &aResult);

  void SetIoUThreshold(PLAFloat aThreshold);
  PLAFloat GetIoUThreshold() const { return _iouThreshold; }

  void SetMaxMissedFrames(PLAInt aFrames);
  PLAInt GetMaxMissedFrames() const { return _maxMissedFrames; }

  PLASize GetTrackedFaceCount() const { return _trackedFaces.size(); }

private:
  PLAFloat CalculateIoU(const PLARect &aRect1, const PLARect &aRect2);
};

#endif // PLAIN_ENGINE_PLAOBJFACETRACKER_HPP
