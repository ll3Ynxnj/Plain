#ifndef PLAIN_PLAOBJCAMERASTREAM_HPP
#define PLAIN_PLAOBJCAMERASTREAM_HPP

#include "plain/core/object/PLAOBJStream.hpp"
#include <opencv2/opencv.hpp>

// PLAOBJCameraStream: Camera device stream implementation
// Captures frames from a camera device (e.g., /dev/video0)
// Updates provide new frames from the camera
class PLAOBJCameraStream : public PLAOBJStream
{
  cv::VideoCapture _capture;
  cv::Mat _lastFrame;
  int _cameraID;

public:
  static PLAOBJCameraStream *Create(const PLAString &aName, int aCameraID = 0);
  static PLAOBJCameraStream *Stream(const PLAString &aName);

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

  // Get last captured frame (BGR format, for analysis)
  cv::Mat GetLastFrame() const { return _lastFrame; }
};

#endif //PLAIN_PLAOBJCAMERASTREAM_HPP
