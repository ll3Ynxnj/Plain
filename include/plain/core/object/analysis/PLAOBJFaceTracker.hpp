#ifndef PLAIN_ENGINE_PLAOBJFACETRACKER_HPP
#define PLAIN_ENGINE_PLAOBJFACETRACKER_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/analysis/PLAFace.hpp"
#include "grain/object/GRAOBJBinder.hpp"
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

class PLAOBJFaceTracker : public PLAObject,
                          private GRAOBJBinder<PLAOBJFaceTracker>::Item
{
  using Binder = GRAOBJBinder<PLAOBJFaceTracker>;

  std::vector<PLATrackedFace> _trackedFaces;
  PLAFaceId _nextId = 0;
  PLAFloat _iouThreshold = 0.3f;
  PLAInt _maxMissedFrames = 5;

  PLAOBJFaceTracker(const PLAString &aName);

public:
  using PLAFaceTrackerItem = GRAOBJBinder<PLAOBJFaceTracker>::Item;
  using PLAFaceTrackerError = GRAOBJBinder<PLAOBJFaceTracker>::Error;

  static PLAOBJFaceTracker *Create(const PLAString &aName = "FaceTracker");
  static PLAOBJFaceTracker *Tracker(const PLAString &aName);

  void Bind() override;

protected:
  void Unbind() override;

public:
  ~PLAOBJFaceTracker();

  void Update(PLAFaceDetectionResult &aResult);

  void SetIoUThreshold(PLAFloat aThreshold);
  PLAFloat GetIoUThreshold() const { return _iouThreshold; }

  void SetMaxMissedFrames(PLAInt aFrames);
  PLAInt GetMaxMissedFrames() const { return _maxMissedFrames; }

  PLASize GetTrackedFaceCount() const { return _trackedFaces.size(); }

private:
  PLAFloat CalculateIoU(const PLARect &aRect1, const PLARect &aRect2);

//-- GRAOBJBinder::Item --/////////////////////////////////////////////////////////
private:
  const char *GetBinderItemTypeName() const override;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRAOBJBinder<PLAOBJFaceTracker>
  {
    static Manager _instance;

    Manager();

  public:
    static Manager *Instance() { return &_instance; };

    ~Manager();

    void Init();
  };
};

#endif // PLAIN_ENGINE_PLAOBJFACETRACKER_HPP
