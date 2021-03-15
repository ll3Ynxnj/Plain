#include <math.h>
#include <unistd.h>

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

  this->InitTextures();

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

void PLAGLUTRenderer::InitTextures() const
{
#define kTexWidth 1024
#define kTexHeight 1024
#define kBufCurrentPath 512

  static const char kTexPath[] = "/Users/ll3ynxnj/Projects/anhr/sample.raw";
  char currentPath[kBufCurrentPath];
  memset(currentPath, '\0', kBufCurrentPath);
  getcwd(currentPath, kBufCurrentPath);
  fprintf(stdout,"Current path : %s\n", currentPath);

  GLubyte texture[kTexHeight][kTexWidth][4];
  FILE *fp;

  if ((fp = fopen(kTexPath, "rb")) != nullptr) {
    fread(texture, sizeof texture, 1, fp);
    fclose(fp);
  }
  else {
    perror(kTexPath);
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, kTexWidth, kTexHeight, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
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

  GLfloat texCoords[] = {
    0.0, 0.0,
    0.0625, 0.0,
    0.0, 0.0625,
    0.0625, 0.0625,
  };

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(4, GL_FLOAT, 0, fillColors);
  glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

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
