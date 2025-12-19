#include "plain/core/object/analysis/PLAOBJFaceTracker.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include <algorithm>
#include <limits>

PLAOBJFaceTracker *PLAOBJFaceTracker::Create(const PLAString &aName)
{
  PLAOBJFaceTracker *tracker = new PLAOBJFaceTracker(aName);
  tracker->Bind();
  return tracker;
}

PLAOBJFaceTracker *PLAOBJFaceTracker::Tracker(const PLAString &aName)
{
  GRAOBJBinder<PLAOBJFaceTracker>::Error error(GRAOBJBinder<PLAOBJFaceTracker>::Error::None);
  return static_cast<PLAOBJFaceTracker *>(Manager::Instance()->RefItemWithName(aName, &error));
}

void PLAOBJFaceTracker::Bind()
{
  this->PLAObject::Bind();

  GRAOBJBinder<PLAOBJFaceTracker>::Error error(GRAOBJBinder<PLAOBJFaceTracker>::Error::None);
  PLAOBJFaceTracker::Manager::Instance()->Bind(this, &error);
  if (error != GRAOBJBinder<PLAOBJFaceTracker>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJFaceTracker binding. ERROR : %02d", error); }
}

void PLAOBJFaceTracker::Unbind()
{
  GRAOBJBinder<PLAOBJFaceTracker>::Error error(GRAOBJBinder<PLAOBJFaceTracker>::Error::None);
  PLAOBJFaceTracker::Manager::Instance()->Unbind(this, &error);
  if (error != GRAOBJBinder<PLAOBJFaceTracker>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJFaceTracker unbinding. ERROR : %02d", error); }

  this->PLAObject::Unbind();
}

PLAOBJFaceTracker::PLAOBJFaceTracker(const PLAString &aName)
  : PLAObject(PLAObjectType::FaceTracker, aName),
    GRAOBJBinder<PLAOBJFaceTracker>::Item(aName, Manager::Instance())
{
}

PLAOBJFaceTracker::~PLAOBJFaceTracker()
{
}

void PLAOBJFaceTracker::Update(PLAFaceDetectionResult &aResult)
{
  if (!aResult.isValid)
  {
    return;
  }

  std::vector<bool> detectionMatched(aResult.faces.size(), false);
  std::vector<bool> trackedMatched(_trackedFaces.size(), false);

  // Match detections to tracked faces using IoU
  for (size_t i = 0; i < aResult.faces.size(); ++i)
  {
    PLAFloat bestIoU = 0.0f;
    size_t bestIdx = std::numeric_limits<size_t>::max();

    for (size_t j = 0; j < _trackedFaces.size(); ++j)
    {
      if (trackedMatched[j])
      {
        continue;
      }

      PLAFloat iou = CalculateIoU(aResult.faces[i].boundingRect,
                                   _trackedFaces[j].boundingRect);
      if (iou > bestIoU && iou >= _iouThreshold)
      {
        bestIoU = iou;
        bestIdx = j;
      }
    }

    if (bestIdx != std::numeric_limits<size_t>::max())
    {
      // Match found - update tracked face and assign ID to detection
      aResult.faces[i].id = _trackedFaces[bestIdx].id;
      _trackedFaces[bestIdx].boundingRect = aResult.faces[i].boundingRect;
      _trackedFaces[bestIdx].confidence = aResult.faces[i].confidence;
      _trackedFaces[bestIdx].missedFrames = 0;
      detectionMatched[i] = true;
      trackedMatched[bestIdx] = true;
    }
  }

  // Increment missed frames for unmatched tracked faces
  for (size_t j = 0; j < _trackedFaces.size(); ++j)
  {
    if (!trackedMatched[j])
    {
      _trackedFaces[j].missedFrames++;
    }
  }

  // Remove tracked faces that have been missing too long
  _trackedFaces.erase(
    std::remove_if(_trackedFaces.begin(), _trackedFaces.end(),
      [this](const PLATrackedFace &face) {
        return face.missedFrames > _maxMissedFrames;
      }),
    _trackedFaces.end());

  // Create new tracked faces for unmatched detections
  for (size_t i = 0; i < aResult.faces.size(); ++i)
  {
    if (!detectionMatched[i])
    {
      PLAFaceId newId = _nextId++;
      aResult.faces[i].id = newId;
      _trackedFaces.emplace_back(newId,
                                  aResult.faces[i].boundingRect,
                                  aResult.faces[i].confidence);
    }
  }
}

void PLAOBJFaceTracker::SetIoUThreshold(PLAFloat aThreshold)
{
  _iouThreshold = (aThreshold > 0.0f && aThreshold <= 1.0f) ? aThreshold : 0.3f;
}

void PLAOBJFaceTracker::SetMaxMissedFrames(PLAInt aFrames)
{
  _maxMissedFrames = (aFrames > 0) ? aFrames : 5;
}

PLAFloat PLAOBJFaceTracker::CalculateIoU(const PLARect &aRect1, const PLARect &aRect2)
{
  // Calculate intersection
  PLAFloat x1 = std::max(aRect1.pos.x, aRect2.pos.x);
  PLAFloat y1 = std::max(aRect1.pos.y, aRect2.pos.y);
  PLAFloat x2 = std::min(aRect1.pos.x + aRect1.size.x, aRect2.pos.x + aRect2.size.x);
  PLAFloat y2 = std::min(aRect1.pos.y + aRect1.size.y, aRect2.pos.y + aRect2.size.y);

  PLAFloat intersectionWidth = std::max(0.0f, x2 - x1);
  PLAFloat intersectionHeight = std::max(0.0f, y2 - y1);
  PLAFloat intersectionArea = intersectionWidth * intersectionHeight;

  // Calculate union
  PLAFloat area1 = aRect1.size.x * aRect1.size.y;
  PLAFloat area2 = aRect2.size.x * aRect2.size.y;
  PLAFloat unionArea = area1 + area2 - intersectionArea;

  if (unionArea <= 0.0f)
  {
    return 0.0f;
  }

  return intersectionArea / unionArea;
}

// GRAOBJBinder::Item //////////////////////////////////////////////////////////

const char *PLAOBJFaceTracker::GetBinderItemTypeName() const
{
  static const char *kName = "PLAOBJFaceTracker";
  return kName;
}

// PLAOBJFaceTracker::Manager //////////////////////////////////////////////////

PLAOBJFaceTracker::Manager PLAOBJFaceTracker::Manager::_instance =
  PLAOBJFaceTracker::Manager();

PLAOBJFaceTracker::Manager::Manager() : GRAOBJBinder<PLAOBJFaceTracker>()
{
}

PLAOBJFaceTracker::Manager::~Manager()
{
}

void PLAOBJFaceTracker::Manager::Init()
{
  GRAOBJBinder<PLAOBJFaceTracker>::Init();
}
