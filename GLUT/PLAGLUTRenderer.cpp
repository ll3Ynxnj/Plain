#include <math.h>

#include "PLAGLUT.h"
#include "PLAGLUTRenderer.hpp"
#include "PLAError.hpp"

PLAGLUTRenderer *PLAGLUTRenderer::Create()
{
  return new PLAGLUTRenderer();
}

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
  /*
  glOrtho(-aStageSize.x * 0.5, aStageSize.x * 0.5,
          -aStageSize.y * 0.5, aStageSize.y * 0.5,
          -aStageSize.z * 0.5, aStageSize.z * 0.5);
  */
  glOrtho(0, aStageSize.x, -aStageSize.y, 0, 0, aStageSize.z);
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

void PLAGLUTRenderer::Render(const PLAActor *aActor) const
{
  glMatrixMode(GL_MODELVIEW);
  this->Draw(aActor);
}

void PLAGLUTRenderer::Draw(const PLAActor *aActor) const
{
  glPushMatrix();

  const PLATransform &transform = aActor->GetTransform();
  glTranslatef(transform.translation.x, -transform.translation.y,
               transform.translation.z);
  glRotatef(transform.rotation.x, 1.0, 0.0, 0.0);
  glRotatef(transform.rotation.y, 0.0, 1.0, 0.0);
  glRotatef(transform.rotation.z, 0.0, 0.0, 1.0);
  glScalef(transform.scale.x, transform.scale.y, transform.scale.z);

  switch (aActor->GetShapeType())
  {
    case PLAShapeType::Rect :
      this->DrawRect(aActor);
      break;
    case PLAShapeType::Circle :
      this->DrawCircle(aActor);
      break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Unexpected PLARenderingDataType detected.");
      break;
  }
  for (const PLAActor *actor : *aActor->GetActors())
  {
    this->Draw(actor);
  }

  glPopMatrix();
}

void PLAGLUTRenderer::DrawRect(const PLAActor *aActor) const
{
  const PLAVec3 offset = aActor->GetShapeOffset();
  GLfloat vertices[] = {
     offset.x,
    -offset.y,
     offset.z,
     offset.x + aActor->GetSize().x,
    -offset.y,
     offset.z,
     offset.x,
    -offset.y - aActor->GetSize().y,
     offset.z,
     offset.x + aActor->GetSize().x,
    -offset.y - aActor->GetSize().y,
     offset.z,
  };

  const PLAColor &color = aActor->GetColor();
  const GLfloat colors[] = {
    color.r, color.g, color.b, color.a,
    color.r, color.g, color.b, color.a,
    color.r, color.g, color.b, color.a,
    color.r, color.g, color.b, color.a,
  };

  //aActor->Print();

  const PLAStyle *style = aActor->GetStyle();
  const PLAColor fillColor = style->GetColorValue(PLAStyleType::FillColor);

  GLfloat fillColors[] = {
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
  };

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(4, GL_FLOAT, 0, fillColors);

  glBegin(GL_TRIANGLE_STRIP);
  glArrayElement(0);
  glArrayElement(1);
  glArrayElement(2);
  glArrayElement(3);
  glEnd();
}

void PLAGLUTRenderer::DrawCircle(const PLAActor *aActor) const
{
  const PLAStyle *style = aActor->GetStyle();
  const PLAColor fillColor = style->GetColorValue(PLAStyleType::FillColor);

  glBegin(GL_TRIANGLE_FAN);
  glColor4d(fillColor.r, fillColor.g, fillColor.b, fillColor.a);
  int split = 24;
  const PLASHPCircle *shape = static_cast<const PLASHPCircle *>(aActor->GetShape());
  const double radius = shape->GetRadius();
  const double step = M_PI * 2 / split;
  const PLAVec2 offset = PLAVec2Make( radius + aActor->GetShapeOffset().x,
                                     -radius - aActor->GetShapeOffset().y);
  glVertex2d(offset.x, offset.y);
  double radian = 0;
  for (int i = 0; i <= split; i++)
  {
    GLfloat px = offset.x + radius * cos(radian) ;
    GLfloat py = offset.y - radius * sin(radian) ;
    glVertex2d(px, py);
    radian += step;
  }
  glEnd();
}
