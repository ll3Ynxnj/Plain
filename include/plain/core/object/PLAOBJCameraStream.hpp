#ifndef PLAIN_PLAOBJCAMERASTREAM_HPP
#define PLAIN_PLAOBJCAMERASTREAM_HPP

#include "plain/core/object/PLAOBJStream.hpp"
#include "plain/core/object/PLAOBJFrameSource.hpp"
#include <opencv2/opencv.hpp>

// PLAOBJCameraStream: Camera device stream implementation
// Captures frames from a camera device (e.g., /dev/video0)
// Updates provide new frames from the camera
class PLAOBJCameraStream : public PLAOBJStream, public PLAOBJFrameSource
{
  cv::VideoCapture _capture;
  cv::Mat _lastFrame;
  int _cameraID;
  Functor _functor;

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

  // PLAOBJFrameSource implementation
  cv::Mat GetCurrentFrame() const override { return _lastFrame; }

  void SetFunction(PLAFunctionCode::FrameSource aKey,
                   const std::function<void(const cv::Mat &)> &aFunc) override
  { _functor.SetFunction(aKey, aFunc); }

protected:
  void RunFunction(PLAFunctionCode::FrameSource aKey,
                   const cv::Mat &aFrame) const override
  { _functor.RunFunction(aKey, aFrame); }
};

#endif //PLAIN_PLAOBJCAMERASTREAM_HPP
