#include <GL/glut.h>
#include "plain/core/object/input/PLAIPTCamera.hpp"

class PLAGLUTRenderer_camera {

  PLAIPTCamera camera;
  GLuint textureID = INT_MAX;

 public:

  ~PLAGLUTRenderer_camera() {

  }

  bool init(void) {
    printf("// CALLED: PLAGLUTRenderer_camera::init() "
           "//////////////////////////////////////\n");

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    return camera.Init();
  }

  void draw(int aViewportWidth, int aViewportHeight) {
    printf("// CALLED: PLAGLUTRenderer_camera::draw() "
           "//////////////////////////////////////\n");

    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto frame = camera.GetFrame();
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
