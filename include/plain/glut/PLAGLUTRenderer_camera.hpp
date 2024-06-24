#include <opencv2/opencv.hpp>
#include <GL/glut.h>
#include <thread>
#include <atomic>

class PLAGLUTRenderer_camera {
  class Camera {
    cv::VideoCapture _cap;
    cv::Mat _frame;
    std::thread _cameraThread;
    std::atomic<bool> _running {true};

    int videoWidth = 1920;
    int videoHeight = 1080;

  public:
    ~Camera() {
      _running = false;
      _cameraThread.join();
    }

    bool init() {
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

    const cv::Mat &getFrame() {
      return _frame;
    }
  };

  Camera camera;
  GLuint textureID = INT_MAX;

 public:

  ~PLAGLUTRenderer_camera() {

  }

  bool init(void) {
    printf("// CALLED: PLAGLUTRenderer_camera::init() "
           "//////////////////////////////////////\n");

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    return camera.init();
  }

  void draw(int aViewportWidth, int aViewportHeight) {
    printf("// CALLED: PLAGLUTRenderer_camera::draw() "
           "//////////////////////////////////////\n");

    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto frame = camera.getFrame();
    if (!frame.empty()) {
        printf("   textureID: %d, frame.cols: %d, frame.rows: %d\n"
               "   aViewportWidth: %d, aViewportHeight: %d\n",
            textureID, frame.cols, frame.rows, aViewportWidth, aViewportHeight);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0,
                     GL_BGR, GL_UNSIGNED_BYTE, frame.data);
    }

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(aViewportWidth * 0.14, -aViewportHeight * 0.14);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(aViewportWidth * 0.86, -aViewportHeight * 0.14);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(aViewportWidth * 0.86, -aViewportHeight * 0.86);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(aViewportWidth * 0.14, -aViewportHeight * 0.86);
    glEnd();

    glDisable(GL_TEXTURE_2D);
  }

};
