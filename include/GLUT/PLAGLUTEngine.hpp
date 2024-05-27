#ifndef PLAIN_ENGINE_PLAGLUT_MAIN_HPP
#define PLAIN_ENGINE_PLAGLUT_MAIN_HPP

class PLAGLUTEngine
{
  static void display(void);
  static void reshape(int w, int h);
  static void timer(int value);
  static void mouse(int button, int state, int x, int y);
  static void keyboard(unsigned char key, int x, int y);
  static void keyboardUp(unsigned char key, int x, int y);

public:
  static void glut(int argc, char *argv[], int width, int height,
                   void (*init)(void));
};

#endif //PLAIN_ENGINE_PLAGLUT_HPP
