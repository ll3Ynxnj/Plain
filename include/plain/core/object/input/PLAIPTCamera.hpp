#ifndef PLAIN_PLAIPTCAMERA_HPP
#define PLAIN_PLAIPTCAMERA_HPP

#include <opencv2/opencv.hpp>
#include <thread>
#include <atomic>

class PLAIPTCamera
{
  cv::VideoCapture _cap;
  cv::Mat _frame;
  std::thread _cameraThread;
  std::atomic<bool> _running {true};

  int videoWidth = 1920;
  int videoHeight = 1080;

public:
  ~PLAIPTCamera();
  bool Init();
  const cv::Mat &GetFrame();
};

#endif //PLAIN_PLAIPTCAMERA_HPP
