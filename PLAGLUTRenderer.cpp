#include "PLAGLUTRenderer.hpp"
#include <OpenGL/gl.h>
#include <math.h>
#include "PLAShape.hpp"

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

void PLAGLUTRenderer::DrawRect(const PLAColor *aColor,
                               const PLATransform *aTransform,
                               const PLAShapeRect *aShape) const
{
  GLfloat vertices[] =
  {
    0,
    0,
    0,
    aShape->GetSize().x,
    0,
    0,
    0,
    aShape->GetSize().y,
    0,
    aShape->GetSize().x,
    aShape->GetSize().y,
    0,
  };

  GLfloat colors[] =
  {
    aColor->r, aColor->g, aColor->b, aColor->a,
    aColor->r, aColor->g, aColor->b, aColor->a,
    aColor->r, aColor->g, aColor->b, aColor->a,
    aColor->r, aColor->g, aColor->b, aColor->a,
  };

  const PLAStyle *style = aShape->GetStyle();
  PLAColor fillColor = style->GetValue<PLAColor>(PLAStyleType::FillColor);

  GLfloat fillColors[] =
  {
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
  };

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(4, GL_FLOAT, 0, fillColors);

  glTranslatef(aTransform->translation.x, aTransform->translation.y, aTransform->translation.z);

  glBegin(GL_TRIANGLE_STRIP);
  glArrayElement(0);
  glArrayElement(1);
  glArrayElement(2);
  glArrayElement(3);
  glEnd();
}

void PLAGLUTRenderer::DrawCircle(const PLAColor *aColor,
                                 const PLATransform *aTransform,
                                 const PLAShapeCircle *aShape) const
{
  const PLAStyle *style = aShape->GetStyle();
  PLAColor fillColor = style->GetValue<PLAColor>(PLAStyleType::FillColor);

  glBegin(GL_TRIANGLE_FAN);
  glColor4d(fillColor.r, fillColor.g, fillColor.b, fillColor.a);
  PLAVec2 origin(kPLAVec2None);
  glVertex2d(origin.x, origin.y);
  int split = 24;

  double radius = aShape->GetRadius();
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
