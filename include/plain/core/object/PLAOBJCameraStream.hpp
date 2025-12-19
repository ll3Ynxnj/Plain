#ifndef PLAIN_PLAOBJCAMERASTREAM_HPP
#define PLAIN_PLAOBJCAMERASTREAM_HPP

#include "plain/core/object/PLAOBJStream.hpp"
#include "plain/core/object/analysis/PLAFace.hpp"
#include <opencv2/opencv.hpp>

class PLAOBJFaceDetector;
class PLAOBJFaceTracker;

// PLAOBJCameraStream: Camera device stream implementation
// Captures frames from a camera device (e.g., /dev/video0)
// Updates provide new frames from the camera
class PLAOBJCameraStream : public PLAOBJStream
{
  cv::VideoCapture _capture;
  int _cameraID;
  PLAOBJFaceDetector *_faceDetector = nullptr;
  PLAOBJFaceTracker *_faceTracker = nullptr;
  PLAFaceDetectionResult _lastResult;

public:
  static PLAOBJCameraStream *Create(const PLAString &aName, int aCameraID = 0);

  PLAOBJCameraStream(const PLAString &aName, int aCameraID = 0);
  ~PLAOBJCameraStream();

  // Open the camera device
  bool Open();

  // Close the camera device
  void Close();

  // Update: Capture next frame from camera
  void Update() override;

  // Check if camera is opened
  bool IsOpened() const { return _capture.isOpened(); }

  // Get camera ID
  int GetCameraID() const { return _cameraID; }

  // Face detection and tracking
  void SetFaceDetector(PLAOBJFaceDetector *aDetector);
  PLAOBJFaceDetector *GetFaceDetector() const { return _faceDetector; }

  void SetFaceTracker(PLAOBJFaceTracker *aTracker);
  PLAOBJFaceTracker *GetFaceTracker() const { return _faceTracker; }

  PLAFaceDetectionResult GetFaceDetectionResult() const;
};

#endif //PLAIN_PLAOBJCAMERASTREAM_HPP
