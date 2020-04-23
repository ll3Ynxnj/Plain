#include <GLUT/glut.h>
#include <math.h>
#include "PLAGLUTRenderer.hpp"

PLAGLUTRenderer::PLAGLUTRenderer()
{

}

PLAGLUTRenderer::~PLAGLUTRenderer()
{

}

void PLAGLUTRenderer::RefreshScreenSize(const PLAVec3 &aFrameSize,
                                        const PLAVec3 &aStageSize)
{
  glViewport(0, 0, aFrameSize.x, aFrameSize.y);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-aStageSize.x * 0.5, aStageSize.x * 0.5,
          -aStageSize.y * 0.5, aStageSize.y * 0.5,
          -aStageSize.z * 0.5, aStageSize.z * 0.5);
}

void PLAGLUTRenderer::Init() const
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glClearColor(0.0, 0.0, 0.0, 1.0);
}

void PLAGLUTRenderer::Clear() const
{
  glClear(GL_COLOR_BUFFER_BIT);
}

void PLAGLUTRenderer::Flush() const
{
  glFlush();
}

void PLAGLUTRenderer::DrawDemo() const
{
  glBegin(GL_POLYGON);
  glColor3d(1.0, 0.0, 0.0);
  glVertex2d(-0.9, -0.9);
  glColor3d(1.0, 1.0, 0.0);
  glVertex2d(0.9, -0.9);
  glColor3d(0.0, 0.0, 1.0);
  glVertex2d(0.9, 0.9);
  glColor3d(0.0, 1.0, 1.0);
  glVertex2d(-0.9, 0.9);
  glEnd();
}

void PLAGLUTRenderer::DrawRect(const PLARDRect *aData) const
{
  GLfloat vertices[] =
  {
    aData->rect.pos.x,
    aData->rect.pos.y,
    0,
    aData->rect.pos.x + aData->rect.size.x,
    aData->rect.pos.y,
    0,
    aData->rect.pos.x,
    aData->rect.pos.y + aData->rect.size.y,
    0,
    aData->rect.pos.x + aData->rect.size.x,
    aData->rect.pos.y + aData->rect.size.y,
    0,
  };

  GLfloat colors[] =
  {
    aData->color.r, aData->color.g, aData->color.b, aData->color.a,
    aData->color.r, aData->color.g, aData->color.b, aData->color.a,
    aData->color.r, aData->color.g, aData->color.b, aData->color.a,
    aData->color.r, aData->color.g, aData->color.b, aData->color.a,
  };

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(4, GL_FLOAT, 0, colors);

  glTranslatef(30, 30, 0);

  glBegin(GL_TRIANGLE_STRIP);
  glArrayElement(0);
  glArrayElement(1);
  glArrayElement(2);
  glArrayElement(3);
  glEnd();
}

void PLAGLUTRenderer::DrawCircle(const PLARDCircle *aData) const
{
  glBegin(GL_TRIANGLE_FAN);
  glColor4d(aData->color.r, aData->color.g, aData->color.b, aData->color.a);
  PLAVec3 origin = aData->circle.origin;
  glVertex2d(origin.x, origin.y);
  int split = aData->split;

  double radius = aData->circle.radius;
  double radian = 0;
  double step = M_PI * 2 / split;
  for (int i = 0; i <= split; i++)
  {
    GLfloat px = origin.x + radius * cos(radian) ;
    GLfloat py = origin.y + radius * sin(radian) ;
    glVertex2d(px, py);
    radian += step;
  }
  glEnd();
}
