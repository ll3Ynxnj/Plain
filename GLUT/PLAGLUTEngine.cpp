//
// Created by Kentaro Kawai on 2021/01/18.
//

#include "PLAGLUT.h"
#include "PLAGLUTEngine.hpp"
#include "PLAGLUTRenderer.hpp"

#include "PLAApp.hpp"
#include "PLAStage.hpp"

void PLAGLUTEngine::display(void)
{
  PLAApp::GetInstance()->Render();
}

void PLAGLUTEngine::reshape(int w, int h)
{
  PLAApp::GetInstance()->RefreshScreenSize(w, h);
}

void PLAGLUTEngine::timer(int value)
{
  PLAApp::GetInstance()->Update();
  PLAApp::GetInstance()->Render();
  //glutPostRedisplay();
  glutTimerFunc(17, timer, 0);
}

void PLAGLUTEngine::mouse(int button, int state, int x, int y)
{
  PLAInputCode inputCode = kPLAInputCodeUndefined;
  switch (button)
  {
    case GLUT_LEFT_BUTTON   :
      inputCode = static_cast<PLAInputCode>(PLAInputCodeForMouse::Left);
      break;
    case GLUT_MIDDLE_BUTTON :
      inputCode = static_cast<PLAInputCode>(PLAInputCodeForMouse::Middle);
      break;
    case GLUT_RIGHT_BUTTON  :
      inputCode = static_cast<PLAInputCode>(PLAInputCodeForMouse::Right);
      break;
    default : break;
  }

  PLAInputSignal inputSignal = false;
  switch (state)
  {
    case GLUT_UP   : inputSignal = 0; break;
    case GLUT_DOWN : inputSignal = 1; break;
    default : break;
  }

  /*
  PLAApp::GetInstance()->
  Input(PLAInputDeviceType::Mouse, inputCode, inputSignal, { float(x), float(y) });
  /*/
  PLAVec3 contentScaleFactor = PLAApp::GetInstance()->GetContentScaleFactor();
  PLAApp::GetInstance()->
    Input(PLAInputDeviceType::Touch, inputCode, inputSignal,
          { float(x / contentScaleFactor.x), float(y / contentScaleFactor.y) });
  //*/
}

void PLAGLUTEngine::keyboard(unsigned char key, int x, int y)
{
  PLAInputCode inputCode = PLAApp::GetInputCodeFromChar(key);
  PLAApp::GetInstance()->Input(PLAInputDeviceType::Key, inputCode, 1,
                               { float(x), float(y) });
}

void PLAGLUTEngine::keyboardUp(unsigned char key, int x, int y)
{
  PLAInputCode inputCode = PLAApp::GetInputCodeFromChar(key);
  PLAApp::GetInstance()->Input(PLAInputDeviceType::Key, inputCode, 0,
                               { float(x), float(y) });
}

void PLAGLUTEngine::glut(int argc, char *argv[], void (*init)(void)) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  glutCreateWindow(argv[0]);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutIgnoreKeyRepeat(1);

  init();
  timer(0);

  glutMainLoop();
}
