#include <math.h>

#include "PLAGLUT.h"
#include "PLAGLUTRenderer.hpp"
#include "PLAError.hpp"
#include "PLAResource.hpp"

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
  glEnableClientState(GL_CURRENT_COLOR);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  //-- Texture --///////////////////////////////////////////////////////////////
  //*
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //*/

  //-- Blend --/////////////////////////////////////////////////////////////////
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
  this->Draw(aActor, kPLAColorNorm);
}

void PLAGLUTRenderer::Draw(const PLAActor *aActor, const PLAColor &aColor) const
{
  glPushMatrix();

  const PLATransform &transform = aActor->GetTransform();
  glTranslatef(transform.translation.x, -transform.translation.y,
               transform.translation.z);
  glRotatef(transform.rotation.x, 1.0, 0.0, 0.0);
  glRotatef(transform.rotation.y, 0.0, 1.0, 0.0);
  glRotatef(transform.rotation.z, 0.0, 0.0, 1.0);
  glScalef(transform.scale.x, transform.scale.y, transform.scale.z);

  const PLALayer *layer = aActor->GetLayer();
  PLAColor color = aActor->GetColor();
  color.Mul(aColor);
  switch (layer->GetLayerType())
  {
    case PLALayerType::Rect :
      this->DrawRect(static_cast<const PLALYRRect *>(layer), color);
      break;
    case PLALayerType::Circle :
      this->DrawCircle(static_cast<const PLALYRCircle *>(layer), color);
      break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Unexpected PLARenderingDataType detected.");
      break;
  }
  for (const PLAActor *actor : *aActor->GetActors())
  {
    this->Draw(actor, color);
  }

  glPopMatrix();
}

void PLAGLUTRenderer::DrawRect(const PLALYRRect *aLayer, const PLAColor &aColor) const
{
  const PLAImageClip *imageClip = aLayer->GetImageClip();
  if (imageClip)
  {
    const PLARSCImage *texImage = imageClip->GetImage();
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImage->GetWidth(),
                 texImage->GetHeight(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, texImage->GetData());
  }
  else
  {
    glDisable(GL_TEXTURE_2D);
  }

  const PLAVec3 offset = aLayer->GetOffset();
  GLfloat vertices[] = {
     offset.x,
    -offset.y,
     offset.z,
     offset.x + aLayer->GetSize().x,
    -offset.y,
     offset.z,
     offset.x,
    -offset.y - aLayer->GetSize().y,
     offset.z,
     offset.x + aLayer->GetSize().x,
    -offset.y - aLayer->GetSize().y,
     offset.z,
  };
  glVertexPointer(3, GL_FLOAT, 0, vertices);

  PLAColor fillColor = aLayer->GetFillColor();
  fillColor.Mul(aColor);
  GLfloat fillColors[] = {
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
  };
  glColorPointer(4, GL_FLOAT, 0, fillColors);

  GLfloat texCoords[8] = {
     0.0, 0.0,
     0.0, 0.0,
     0.0, 0.0,
     0.0, 0.0,
  };

  if (imageClip)
  {
    texCoords[0] = imageClip->GetNormalizedClip().pos.x;  // 0.0,
    texCoords[1] = imageClip->GetNormalizedClip().pos.y;  // 0.0,
    texCoords[2] = imageClip->GetNormalizedClip().pos.x +
                   imageClip->GetNormalizedClip().size.x; // 0.0625,
    texCoords[3] = imageClip->GetNormalizedClip().pos.y;  // 0.0,
    texCoords[4] = imageClip->GetNormalizedClip().pos.x;  // 0.0,
    texCoords[5] = imageClip->GetNormalizedClip().pos.y +
                   imageClip->GetNormalizedClip().size.y; // 0.0625,
    texCoords[6] = imageClip->GetNormalizedClip().pos.x +
                   imageClip->GetNormalizedClip().size.x; // 0.0625
    texCoords[7] = imageClip->GetNormalizedClip().pos.y +
                   imageClip->GetNormalizedClip().size.y; // 0.0625,
    /*/
   GLfloat texCoords[] = {
     0.0, 0.0,
     0.0625, 0.0,
     0.0, 0.0625,
     0.0625, 0.0625,
   };
    //*/
  }

  glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

  glBegin(GL_TRIANGLE_STRIP);
  glArrayElement(0);
  glArrayElement(1);
  glArrayElement(2);
  glArrayElement(3);
  glEnd();
}

void PLAGLUTRenderer::DrawCircle(const PLALYRCircle *aLayer, const PLAColor &aColor) const
{
  const PLAImageClip *imageClip = aLayer->GetImageClip();
  if (imageClip)
  {
    const PLARSCImage *texImage = imageClip->GetImage();
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImage->GetWidth(),
                 texImage->GetHeight(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, texImage->GetData());
  }
  else
  {
    glDisable(GL_TEXTURE_2D);
  }

  int split = 24;
  const unsigned numVertices = 1 + split + 1;
  GLfloat vertices[numVertices * 3];
  {
    const double radius = aLayer->GetRadius();
    const double step = M_PI * 2 / split;
    const PLAVec2 origin = PLAVec2( radius + aLayer->GetOffset().x,
                                   -radius - aLayer->GetOffset().y);

    double radian = 0;
    vertices[0] = origin.x;
    vertices[1] = origin.y;
    vertices[2] = 0;

    for (int i = 1; i < numVertices; i++)
    {
      unsigned baseIndex = i * 3;
      vertices[baseIndex + 0] = origin.x + radius * cos(radian);
      vertices[baseIndex + 1] = origin.y - radius * sin(radian);
      vertices[baseIndex + 2] = 0;

      int index = baseIndex;
      GRA_PRINT("vertices[%2d] : %.2f\n", index, vertices[index]);
      ++index;
      GRA_PRINT("vertices[%2d] : %.2f\n", index, vertices[index]);
      ++index;
      GRA_PRINT("vertices[%2d] : %.2f\n", index, vertices[index]);
      GRA_PRINT("--------------------\n");

      radian += step;
    }
  }

  GLfloat fillColors[numVertices * 4];
  PLAColor fillColor = aLayer->GetFillColor();
  fillColor.Mul(aColor);

  for (int i = 0; i < numVertices; i++)
  {
    unsigned baseIndex = i * 4;
    fillColors[baseIndex + 0] = fillColor.r;
    fillColors[baseIndex + 1] = fillColor.g;
    fillColors[baseIndex + 2] = fillColor.b;
    fillColors[baseIndex + 3] = fillColor.a;
  }

  GLfloat texCoords[numVertices * 2];
  {
    const double radius = 0.625 * 0.5;
    const PLAVec2 offset = PLAVec2(0.5, 0.5);
    const double step = M_PI * 2 / split;
    const PLAVec2 origin = PLAVec2( radius + offset.x,
                                   -radius - offset.y);

    double radian = 0;
    texCoords[0] = origin.x;
    texCoords[1] = origin.y;

    for (int i = 1; i < numVertices; i++)
    {
      unsigned baseIndex = i * 2;
      texCoords[baseIndex + 0] = origin.x + radius * cos(radian);
      texCoords[baseIndex + 1] = origin.y - radius * sin(radian);
      radian += step;
    }
  }

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(4, GL_FLOAT, 0, fillColors);
  glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i < numVertices; i++)
  {
    glArrayElement(i);
  }
  glEnd();
}
