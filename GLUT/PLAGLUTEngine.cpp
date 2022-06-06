#include "PLAGLUT.h"
#include "PLAGLUTEngine.hpp"
#include "PLAGLUTRenderer.hpp"

#include "Core/Class/PLAApp.hpp"
#include "Core/Class/PLAStage.hpp"

void PLAGLUTEngine::display(void)
{
  PLAApp::Instance()->Render();
}

void PLAGLUTEngine::reshape(int w, int h)
{
  PLAApp::Instance()->RefreshScreenSize(w, h);
}

void PLAGLUTEngine::timer(int value)
{
  PLAApp::Instance()->Update();
  PLAApp::Instance()->Render();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
  //glutPostRedisplay();
  glutTimerFunc(17, timer, 0);
#pragma clang diagnostic pop
}

void PLAGLUTEngine::mouse(int button, int state, int x, int y)
{
  PLAInputSignalCode inputCode = kPLAInputSignalCodeUndefined;
  switch (button)
  {
    case GLUT_LEFT_BUTTON   :
      inputCode =
        static_cast<PLAInputSignalCode>(PLAInputSignalCodeForMouse::Left);
      break;
    case GLUT_MIDDLE_BUTTON :
      inputCode =
        static_cast<PLAInputSignalCode>(PLAInputSignalCodeForMouse::Middle);
      break;
    case GLUT_RIGHT_BUTTON  :
      inputCode =
        static_cast<PLAInputSignalCode>(PLAInputSignalCodeForMouse::Right);
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
  PLAApp::Instance()->
  Input(PLAInputDeviceType::Mouse, inputCode, inputSignal, { float(x), float(y) });
  /*/
  PLAVec3 contentScaleFactor = PLAApp::Instance()->GetContentScaleFactor();
  PLAApp::Instance()->
    Input(PLAInputDeviceType::Touch, inputCode, inputSignal,
          { float(x / contentScaleFactor.x), float(y / contentScaleFactor.y) });
  //*/
}

void PLAGLUTEngine::keyboard(unsigned char key, int x, int y)
{
  PLAInputSignalCode inputCode = PLAApp::GetInputSignalCodeFromChar(key);
  PLAApp::Instance()->Input(PLAInputDeviceType::Keyboard, inputCode, 1,
                               { float(x), float(y) });
}

void PLAGLUTEngine::keyboardUp(unsigned char key, int x, int y)
{
  PLAInputSignalCode inputCode = PLAApp::GetInputSignalCodeFromChar(key);
  PLAApp::Instance()->Input(PLAInputDeviceType::Keyboard, inputCode, 0,
                               { float(x), float(y) });
}

void PLAGLUTEngine::glut(int argc, char *argv[], int width, int height, void (*init)(void)) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(width, height);

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
#pragma clang diagnostic pop
}

