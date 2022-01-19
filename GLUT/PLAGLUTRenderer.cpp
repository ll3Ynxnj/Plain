#include <math.h>

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

void PLAGLUTRenderer::GetRectVertices(GLfloat aVertices[12],
                                      const PLAVec3 &aPos,
                                      const PLAVec2 &aSize)
{
  aVertices[ 0] =  aPos.x;
  aVertices[ 1] = -aPos.y;
  aVertices[ 2] =  aPos.z;
  aVertices[ 3] =  aPos.x + aSize.x;
  aVertices[ 4] = -aPos.y;
  aVertices[ 5] =  aPos.z;
  aVertices[ 6] =  aPos.x;
  aVertices[ 7] = -aPos.y - aSize.y;
  aVertices[ 8] =  aPos.z;
  aVertices[10] =  aPos.x + aSize.x;
  aVertices[11] = -aPos.y - aSize.y;
  aVertices[12] =  aPos.z;
}

void PLAGLUTRenderer::GetRectColors(GLfloat aColors[16],
                                    const PLAColor &aColor)
{
  aColors[0] = aColors[4] = aColors[ 8] = aColors[12] = aColor.r;
  aColors[1] = aColors[5] = aColors[ 9] = aColors[13] = aColor.g;
  aColors[2] = aColors[6] = aColors[10] = aColors[14] = aColor.b;
  aColors[3] = aColors[7] = aColors[11] = aColors[15] = aColor.a;
}

void PLAGLUTRenderer::GetRectTexCoords(GLfloat aCoords[8],
                                       const PLAVec2 &aPos,
                                       const PLAVec2 &aSize)
{
  aCoords[0] = aPos.x;
  aCoords[1] = aPos.y;
  aCoords[2] = aPos.x + aSize.x;
  aCoords[3] = aPos.y;
  aCoords[4] = aPos.x;
  aCoords[5] = aPos.y + aSize.y;
  aCoords[6] = aPos.x + aSize.x;
  aCoords[7] = aPos.y + aSize.y;
}

void PLAGLUTRenderer::Draw(const PLAActor *aActor, const PLAColor &aColor) const
{
  /*
  GRA_PRINT("Draw(aActor: %s, aColor: {r: %.2f, g: %.2f, b: %.2f, a: %.2f}\n",
            aActor->GetObjectName().c_str(),
            aColor.r, aColor.g, aColor.b, aColor.a);
  */
  if (aActor->GetObjectName() == "ResponderActor") {
    //GRA_TRACE("");
  }
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
  color *= aColor;
  switch (layer->GetLayerType())
  {
    case PLALayerType::Rect :
      this->DrawRect(static_cast<const PLALYRRect *>(layer), color);
      break;
    case PLALayerType::Circle :
      this->DrawCircle(static_cast<const PLALYRCircle *>(layer), color);
      break;
    case PLALayerType::Tile :
      this->DrawTile(static_cast<const PLALYRTile *>(layer), color);
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
  /*
  GRA_PRINT("DrawRect(aLayer: %s,"
            "aColor: {r: %.2f, g: %.2f, b: %.2f, a: %.2f})\n",
            aLayer->GetObjectName().c_str(),
            aColor.r, aColor.g, aColor.b, aColor.a);
            */
  const PLAImageClip *imageClip = aLayer->GetImageClip();
  if (imageClip)
  {
    const PLAImage *texImage = imageClip->GetImage();
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImage->GetSize().x,
                 texImage->GetSize().y, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, texImage->GetResourceData());
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

  PLAColor fillColor = aLayer->GetFillColor();
  fillColor *= aColor;
  GLfloat fillColors[] = {
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
    fillColor.r, fillColor.g, fillColor.b, fillColor.a,
  };

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

void PLAGLUTRenderer::DrawCircle(const PLALYRCircle *aLayer, const PLAColor &aColor) const
{
  GRA_PRINT("DrawCircle(aLayer: %s,"
            " aColor: {r: %.2f, g: %.2f, b: %.2f, a: %.2f})\n",
            aLayer->GetObjectName().c_str(),
            aColor.r, aColor.g, aColor.b, aColor.a);
  const PLAImageClip *imageClip = aLayer->GetImageClip();
  if (imageClip)
  {
    const PLAImage *texImage = imageClip->GetImage();
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImage->GetSize().x,
                 texImage->GetSize().y, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, texImage->GetResourceData());
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
  glVertexPointer(3, GL_FLOAT, 0, vertices);

  GLfloat fillColors[numVertices * 4];
  PLAColor fillColor = aLayer->GetFillColor();
  fillColor *= aColor;

  for (int i = 0; i < numVertices; i++)
  {
    unsigned baseIndex = i * 4;
    fillColors[baseIndex + 0] = fillColor.r;
    fillColors[baseIndex + 1] = fillColor.g;
    fillColors[baseIndex + 2] = fillColor.b;
    fillColors[baseIndex + 3] = fillColor.a;
  }
  glColorPointer(4, GL_FLOAT, 0, fillColors);

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
  glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i < numVertices; i++)
  {
    glArrayElement(i);
  }
  glEnd();
}

void PLAGLUTRenderer::DrawTile(const PLALYRTile *aLayer,
                               const PLAColor &aColor) const
{
  /*
  GRA_PRINT("DrawTile(aLayer: %s,"
            " aColor: {r: %.2f, g: %.2f, b: %.2f, a: %.2f})\n",
            aLayer->GetObjectName().c_str(),
            aColor.r, aColor.g, aColor.b, aColor.a);
            */

  //-- This method is an inefficient implementation.
  static bool kIsDebug = false;//false;

  const PLAImage *texImage = aLayer->GetImage();
  if (texImage && !kIsDebug) {
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImage->GetSize().x,
                 texImage->GetSize().y, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, texImage->GetResourceData());
  } else {
    glDisable(GL_TEXTURE_2D);
  }

  GRAVec2<PLASize> tileSize = aLayer->GetTileSize();
  GRAVec2<PLASize> chipSize = aLayer->GetChipSize();

  GLfloat pxTable[tileSize.x];
  for (PLAInt i = 0; i < tileSize.x; i++) {
    GLfloat px = chipSize.x * i;
    pxTable[i] = px;
    if (kIsDebug) { GRA_PRINT("pxTable[%d]: %.2f\n", i, pxTable[i]); }
  }

  GLfloat pyTable[tileSize.y];
  for (PLAInt i = 0; i < tileSize.y; i++) {
    GLfloat py = chipSize.x * i;
    pyTable[i] = py;
    if (kIsDebug) { GRA_PRINT("pyTable[%d]: %.2f\n", i, pyTable[i]); }
  }

  PLASize numberOfChipsX = 1024 / chipSize.x;
  GLfloat cxTable[numberOfChipsX];
  for (PLAInt i = 0; i < numberOfChipsX; i++) {
    cxTable[i] = (i * chipSize.x) / 1024.0;
    if (kIsDebug) { GRA_PRINT("cxTable[%d]:%.2f\n", i, cxTable[i]); }
  };

  PLASize numberOfChipsY = 1024 / chipSize.y;
  GLfloat cyTable[numberOfChipsY];
  for (PLAInt i = 0; i < numberOfChipsY; i++) {
    cyTable[i] = (i * chipSize.y) / 1024.0;
    if (kIsDebug) { GRA_PRINT("cyTable[%d]:%.2f\n", i, cyTable[i]); }
  };

  GLfloat cw = static_cast<GLfloat>(chipSize.x) / 1024;
  GLfloat ch = static_cast<GLfloat>(chipSize.y) / 1024;

  const PLAVec2s dataAddress = aLayer->GetDataAddress();
  for (PLAInt y = 0; y < tileSize.y; y++) {
    for (PLAInt x = 0; x < tileSize.x; x++) {
      PLAVec2s address(dataAddress.x + x, dataAddress.y + y);
      const PLATileChip &chip = aLayer->GetChip(address);
      if (chip.code == kPLATileChipCodeNone) { continue; }

      const PLAMotion *motion = aLayer->GetMotion(address);
      PLAVec3 translation = kPLAVec3None;
      PLAVec3 rotation = kPLAVec3None;
      PLAVec3 scale = kPLAVec3Norm;
      //if (motion)
      //{
        std::map<PLAMotionType, PLAProperty> properties =
          std::map<PLAMotionType, PLAProperty>();
        motion->GetProperty(&properties);
        if (properties.contains(PLAMotionType::Translation))
        { translation = properties.at(PLAMotionType::Translation).GetVec3(); }
        if (properties.contains(PLAMotionType::Rotation))
        { rotation = properties.at(PLAMotionType::Rotation).GetVec3(); }
        if (properties.contains(PLAMotionType::Scale))
        { scale = properties.at(PLAMotionType::Scale).GetVec3(); }
      //}

      const PLAVec3 offset = PLAVec3(pxTable[x], pyTable[y], 0) + translation;
      static const PLAUInt kNumVertices = 12;
      GLfloat vertices[kNumVertices] = {
        offset.x,
        -offset.y,
        offset.z,
        offset.x + chipSize.x,
        -offset.y,
        offset.z,
        offset.x,
        -offset.y - chipSize.y,
        offset.z,
        offset.x + chipSize.x,
        -offset.y - chipSize.y,
        offset.z,
      };

      if (kIsDebug) {
        for (int i = 0; i < kNumVertices;) {
          GRA_PRINT("x: %d, y: %d,"
                    " vertices: [%d] x: %.2f, [%d] y: %.2f, [%d] z: %.2f\n",
                    x, y, i, vertices[i++], i, vertices[i++], i, vertices[i++]);
        }
      }

      PLAColor color = chip.color;
      if (kIsDebug)
      {
        static const PLAColor kDebugColors[] = {
          kPLAColorRed, kPLAColorGreen, kPLAColorBlue,
          kPLAColorCyan, kPLAColorMagenta, kPLAColorYellow,
        };
        const PLAUInt debugColorIndex = (y + x) % 6;
        color = kDebugColors[debugColorIndex];
        GRA_PRINT("x: %d, y: %d, colors: index: %d,"
                  " r: %.2f, g: %.2f, b: %.2f, a: %.2f,\n",
                  x, y, debugColorIndex, color.r, color.g, color.b, color.a);
      }

      static const PLAUInt kNumColors = 16;
      GLfloat colors[kNumColors] = {
        color.r, color.g, color.b, color.a,
        color.r, color.g, color.b, color.a,
        color.r, color.g, color.b, color.a,
        color.r, color.g, color.b, color.a,
      };

      static const PLAUInt kNumCoords = 8;
      GLfloat cx = cw * (chip.code % numberOfChipsX);
      GLfloat cy = ch * (chip.code / numberOfChipsY);
      GLfloat coords[kNumCoords] = {
        cx,      cy,
        cx + cw, cy,
        cx,      cy + ch,
        cx + cw, cy + ch,
      };

      if (kIsDebug) {
        for (int i = 0; i < kNumCoords;) {
          GRA_PRINT("x: %d, y: %d, coords: [%d] x: %.2f, [%d] y: %.2f\n",
                    x, y, i, coords[i++], i, coords[i++]);
        }
      }

      glVertexPointer(3, GL_FLOAT, 0, vertices);
      glColorPointer(4, GL_FLOAT, 0, colors);
      glTexCoordPointer(2, GL_FLOAT, 0, coords);

      glBegin(GL_TRIANGLE_STRIP);
      glArrayElement(0);
      glArrayElement(1);
      glArrayElement(2);
      glArrayElement(3);
      glEnd();
    }
  }
}
