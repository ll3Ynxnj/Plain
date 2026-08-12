#ifndef PLAIN_PLAOBJCAMERASTREAM_HPP
#define PLAIN_PLAOBJCAMERASTREAM_HPP

#include "plain/core/object/PLAOBJStream.hpp"
#include "plain/core/object/PLAOBJFrameSource.hpp"
#include <opencv2/opencv.hpp>
#include <thread>
#include <atomic>

class PLAAGTCameraStream;

// PLAOBJCameraStream: Camera device stream implementation
// Captures frames from a camera device (e.g., /dev/video0)
// or a network stream URL (e.g., rtsp://...)
//
// Threading: This class handles its own capture thread internally.
// - Open() starts the capture thread
// - Close() stops the capture thread
// - Update() fires OnFrameUpdate event when new frame is available
class PLAOBJCameraStream : public PLAOBJStream, public PLAOBJFrameSource
{
  cv::VideoCapture _capture;

  // Double buffering for analysis frame (BGR format)
  cv::Mat _analysisFrames[2];
  std::atomic<int> _analysisFrameIndex{0};

  int _cameraID;
  PLAString _cameraURL;
  Functor _functor;

  // Internal capture thread
  std::thread _captureThread;
  std::atomic<bool> _running{false};

public:
  static PLAOBJCameraStream *Create(const PLAString &aName, int aCameraID = 0);
  static PLAOBJCameraStream *Create(const PLAString &aName,
                                    const PLAString &aCameraURL);
  static PLAOBJCameraStream *Stream(const PLAString &aName);

  PLAOBJCameraStream(const PLAString &aName, int aCameraID = 0);
  PLAOBJCameraStream(const PLAString &aName, const PLAString &aCameraURL);
  ~PLAOBJCameraStream();

  PLAAGTCameraStream AssignAgent();

  // Open the camera device (starts capture thread)
  bool Open();

  // Close the camera device (stops capture thread)
  void Close();

  // Update: Fire OnFrameUpdate event when new frame is available
  void Update() override;

  // Check if camera is opened
  bool IsOpened() const { return _capture.isOpened(); }

  // Get camera ID
  int GetCameraID() const { return _cameraID; }

  // PLAOBJFrameSource implementation (lock-free, thread-safe via double buffering)
  cv::Mat GetCurrentFrame() const override {
    // Read from front buffer (no lock needed - atomic index)
    return _analysisFrames[_analysisFrameIndex].clone();
  }

  void SetFunction(PLAFunctionCode::FrameSource aKey,
                   const std::function<void(const cv::Mat &)> &aFunc) override
  { _functor.SetFunction(aKey, aFunc); }

protected:
  void RunFunction(PLAFunctionCode::FrameSource aKey,
                   const cv::Mat &aFrame) const override
  { _functor.RunFunction(aKey, aFrame); }

private:
  // Capture loop running in separate thread
  void CaptureLoop();

  // Capture single frame and update buffers (called by CaptureLoop)
  void CaptureFrame();
};

#endif //PLAIN_PLAOBJCAMERASTREAM_HPP
