#include "plain/core/object/input/PLAIPTCamera.hpp"

PLAIPTCamera::PLAIPTCamera():
  PLAInput(PLAInputDeviceType::Camera, 0, 0),
  _running(true)
{

}

PLAIPTCamera::~PLAIPTCamera() {
  _running = false;
  _cameraThread.join();
}

bool PLAIPTCamera::Init() {
  _cap.open(0, cv::CAP_V4L2);
  if (!_cap.isOpened()) {
    std::cerr << "Error: Couldn't open the camera." << std::endl;
    return false;
  }

  // Set the camera parameters
  _cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
  _cap.set(cv::CAP_PROP_FRAME_WIDTH, videoWidth);
  _cap.set(cv::CAP_PROP_FRAME_HEIGHT, videoHeight);
  _cap.set(cv::CAP_PROP_FPS, 30);

  _cameraThread = std::thread([this] {
    while (_running) {
      _cap >> _frame;
    }
  });

  return true;
}

const cv::Mat &PLAIPTCamera::GetFrame() {
  return _frame;
}
