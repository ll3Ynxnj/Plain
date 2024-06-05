#include <opencv2/opencv.hpp>
#include <GL/glut.h>
#include <thread>
#include <atomic>

class PLAGLUTRenderer_camera {
  cv::VideoCapture cap;
  cv::Mat frame;
  std::thread cameraThread;
  std::atomic<bool> running {true};

  int videoWidth = 1920;
  int videoHeight = 1080;

public:
  GLuint textureID = INT_MAX;

  ~PLAGLUTRenderer_camera() {
    running = false;
    cameraThread.join();
  }

  bool init(void) {
    printf("// CALLED: PLAGLUTRenderer_camera::init() "
           "//////////////////////////////////////\n");

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    cap.open(0, cv::CAP_V4L2);
    if (!cap.isOpened()) {
      std::cerr << "Error: Couldn't open the camera." << std::endl;
      return false;
    }

    // Set the camera parameters
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap.set(cv::CAP_PROP_FRAME_WIDTH, videoWidth);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, videoHeight);
    cap.set(cv::CAP_PROP_FPS, 30);

    cameraThread = std::thread([this] {
      while (running) {
          cap >> frame;
      }
    });
    return true;
  }

  void draw(int aViewportWidth, int aViewportHeight) {
    printf("// CALLED: PLAGLUTRenderer_camera::draw() "
           "//////////////////////////////////////\n");

    if (!frame.empty()) {
        printf("textureID: %d\n", textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0,
                     GL_BGR, GL_UNSIGNED_BYTE, frame.data);
    }

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(aViewportWidth * 0.14, aViewportHeight * 0.14);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(aViewportWidth * 0.86, aViewportHeight * 0.14);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(aViewportWidth * 0.86, aViewportHeight * 0.86);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(aViewportWidth * 0.14, aViewportHeight * 0.86);
    glEnd();
  }

};
