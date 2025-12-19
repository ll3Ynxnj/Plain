#ifndef PLAIN_PLAOBJCAMERASTREAM_HPP
#define PLAIN_PLAOBJCAMERASTREAM_HPP

#include "plain/core/object/PLAOBJStream.hpp"
#include "plain/core/object/analysis/PLAFace.hpp"
#include <opencv2/opencv.hpp>

// PLAOBJCameraStream: Camera device stream implementation
// Captures frames from a camera device (e.g., /dev/video0)
// Updates provide new frames from the camera
class PLAOBJCameraStream : public PLAOBJStream
{
  cv::VideoCapture _capture;
  cv::Mat _lastFrame;  // Keep last frame for smile detection
  int _cameraID;
  PLAString _faceDetectorName = "";
  PLAString _faceTrackerName = "";
  PLAString _smileDetectorName = "";
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

  // Face detection and tracking (loose coupling via name references)
  void SetFaceDetectorName(const PLAString &aName) { _faceDetectorName = aName; }
  const PLAString &GetFaceDetectorName() const { return _faceDetectorName; }

  void SetFaceTrackerName(const PLAString &aName) { _faceTrackerName = aName; }
  const PLAString &GetFaceTrackerName() const { return _faceTrackerName; }

  void SetSmileDetectorName(const PLAString &aName) { _smileDetectorName = aName; }
  const PLAString &GetSmileDetectorName() const { return _smileDetectorName; }

  PLAFaceDetectionResult GetFaceDetectionResult() const;
};

#endif //PLAIN_PLAOBJCAMERASTREAM_HPP
