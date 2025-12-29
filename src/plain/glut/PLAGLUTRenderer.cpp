#include <math.h>

#include "plain/glut/PLAGLUTRenderer.hpp"
#include "plain/glut/PLAGLUTTexture.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include "plain/core/object/PLAOBJResource.hpp"
#include "plain/core/object/PLAOBJVideoClip.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

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

void PLAGLUTRenderer::RefreshScreenSize(const PLAVec3f &aFrameSize,
                                        const PLAVec3f &aStageSize)
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

  //*/

  //-- Blend --/////////////////////////////////////////////////////////////////
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(0.0, 0.0, 0.0, 1.0);
}

void PLAGLUTRenderer::Clear() const
{
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void PLAGLUTRenderer::Flush() const
{
  glFlush();
}

void PLAGLUTRenderer::Render(const PLAOBJActor *aActor) const
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  this->Draw(aActor, kPLAColorNorm);
}

void PLAGLUTRenderer::GetRectVertices(GLfloat aVertices[12],
                                      const PLAVec3f &aPos,
                                      const PLAVec2f &aSize)
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
                                       const PLAVec2f &aPos,
                                       const PLAVec2f &aSize)
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

void PLAGLUTRenderer::GetMotionProperties(const PLATMLMotion *aNode,
                                          MotionProperties *aProperties) {
  if (aNode)
  {
    std::map<PLATMLMotionType, PLAProperty> properties =
      std::map<PLATMLMotionType, PLAProperty>();
    aNode->GetProperties(&properties);
    if (properties.contains(PLATMLMotionType::Translation))
    {
      aProperties->translation = properties.at(PLATMLMotionType::Translation).GetVec3f();
    }
    if (properties.contains(PLATMLMotionType::Rotation))
    {
      aProperties->rotation = properties.at(PLATMLMotionType::Rotation).GetVec3f();
    }
    if (properties.contains(PLATMLMotionType::Scale))
    {
      aProperties->scale = properties.at(PLATMLMotionType::Scale).GetVec3f();
    }
    if (properties.contains(PLATMLMotionType::Color))
    {
      aProperties->color = properties.at(PLATMLMotionType::Color).GetColor();
    }
  }
}

void PLAGLUTRenderer::Draw(const PLAOBJActor *aActor, const PLAColor &aColor) const
{
  //glClear(GL_COLOR_BUFFER_BIT);

  /*
  GRA_PRINT("Draw(aActor: %s, aColor: {r: %.2f, g: %.2f, b: %.2f, a: %.2f}\n",
            aActor->GetObjectName().c_str(),
            aColor.r, aColor.g, aColor.b, aColor.a);
  */

  this->ApplyRenderMode(aActor->GetRenderMode());

  if (!aActor->IsVisible()) { return; }

  glPushMatrix();

  const PLATransform &transform = aActor->GetTransform();
  glTranslatef(transform.translation.x, -transform.translation.y,
               transform.translation.z);
  glRotatef(transform.rotation.x, 1.0, 0.0, 0.0);
  glRotatef(transform.rotation.y, 0.0, 1.0, 0.0);
  glRotatef(transform.rotation.z, 0.0, 0.0, 1.0);
  glScalef(transform.scale.x, transform.scale.y, transform.scale.z);

  const PLAOBJLayer *layer = aActor->GetLayer();
  PLAColor color = aActor->GetColor();
  color *= aColor;

  auto motion = aActor->GetMotion();

  if (motion) {
    if (motion->GetObjectName() == "Telop")
    {
      GRA_TRACE("");
    }
  }
  MotionProperties motionProperties = MotionProperties();
  GetMotionProperties(motion, &motionProperties);
  PLAGLUTRenderer::GetMotionProperties(motion, &motionProperties);
  glTranslatef( motionProperties.translation.x,
               -motionProperties.translation.y,
                motionProperties.translation.z);
  color *= motionProperties.color;

  bool isMask = aActor->IsMask();

  if (isMask)
  {
    // Clear stencil buffer for this mask
    glClear(GL_STENCIL_BUFFER_BIT);

    // Setup stencil buffer for mask - write 1 where geometry is drawn
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    // Enable alpha test to respect texture alpha (discard fragments with alpha <= 0.5)
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5f);

    // Disable color writes - only write to stencil buffer
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  }

  switch (layer->GetLayerType())
  {
    case PLALayerType::Point :
      this->DrawPoint(static_cast<const PLALYRPoint *>(layer), color, motion);
      break;
    case PLALayerType::Line :
      this->DrawLine(static_cast<const PLALYRLine *>(layer), color, motion);
      break;
    case PLALayerType::Rect :
      this->DrawRect(static_cast<const PLALYRRect *>(layer), color, motion);
      break;
    case PLALayerType::Circle :
      this->DrawCircle(static_cast<const PLALYRCircle *>(layer), color, motion);
      break;
    case PLALayerType::Arc :
      this->DrawArc(static_cast<const PLALYRArc *>(layer), color, motion);
      break;
    case PLALayerType::Tile :
      this->DrawTile(static_cast<const PLALYRTile *>(layer), color, motion);
      break;
    case PLALayerType::Label :
      this->DrawLabel(static_cast<const PLALYRLabel *>(layer), color, motion);
      break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Unexpected PLARenderingDataType detected.");
      break;
  }

  if (isMask)
  {
    // Restore color writes
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    // Disable alpha test (was used for mask texture alpha)
    glDisable(GL_ALPHA_TEST);

    // Setup stencil test for children - only draw where stencil == 1
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
  }

  for (const PLAOBJActor *actor : *aActor->GetActors())
  {
    this->Draw(actor, color);
  }

  if (isMask)
  {
    // Disable stencil test after drawing children
    glDisable(GL_STENCIL_TEST);
  }

  glPopMatrix();

// CAUTION ( goto for tests) ///////////////////////////////////////////////////
  //goto DRAW_VIDEO;
  //{
////////////////////////////////////////////////////////////////////////////////

// CAUTION ( label for tests) //////////////////////////////////////////////////
  //}
  //DRAW_VIDEO:
////////////////////////////////////////////////////////////////////////////////

  // TEST: Initialize the camera ///////////////////////////////////////////////
  /*
  static PLAGLUTRenderer_camera *camera = nullptr;
  if (!camera) {
    camera = new PLAGLUTRenderer_camera();
    if (!camera->init()) {
      delete camera;
      camera = nullptr;
    }
  }
  */
  //////////////////////////////////////////////////////////////////////////////

  // TEST: Draw the camera image ///////////////////////////////////////////////
  /*
  glPushMatrix();
  camera->draw(640, 360);//viewportWidth, viewportHeight);
  glPopMatrix();
  */
  //////////////////////////////////////////////////////////////////////////////

}

void PLAGLUTRenderer::DrawPoint(const PLALYRPoint *aLayer, const PLAColor &aColor,
                                const PLATMLMotion *aMotion) const
{
  glDisable(GL_TEXTURE_2D);

  const PLAVec3f offset = aLayer->GetOffset();
  PLAColor color = aLayer->GetColor() * aColor;

  glPointSize(4.0f);
  glBegin(GL_POINTS);
  glColor4f(color.r, color.g, color.b, color.a);
  glVertex3f(offset.x, -offset.y, offset.z);
  glEnd();
}

void PLAGLUTRenderer::DrawLine(const PLALYRLine *aLayer, const PLAColor &aColor,
                               const PLATMLMotion *aMotion) const
{
  glDisable(GL_TEXTURE_2D);

  PLALine line = aLayer->GetLine();
  PLAColor color = aLayer->GetColor() * aColor;

  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glColor4f(color.r, color.g, color.b, color.a);
  glVertex3f(line.p0.x, -line.p0.y, 0);
  glVertex3f(line.p1.x, -line.p1.y, 0);
  glEnd();
}

void PLAGLUTRenderer::DrawRect(const PLALYRRect *aLayer, const PLAColor &aColor,
                               const PLATMLMotion *aMotion) const
{
  // GRA_PRINT("DrawRect(\n"
  //           "  aLayer: %s\n"
  //           "    aLayer.origin: { x: %.2f, y: %.2f, z: %.2f }\n"
  //           "    aLayer.size: { x: %.2f, y: %.2f }\n"
  //           "    aLayer.color: { r: %.2f, g: %.2f, b: %.2f, a: %.2f }\n"
  //           "  aColor: { r: %.2f, g: %.2f, b: %.2f, a: %.2f })\n",
  //           aLayer->GetObjectName().c_str(),
  //           aLayer->GetOffset().x, aLayer->GetOffset().y, aLayer->GetOffset().z,
  //           aLayer->GetSize().x, aLayer->GetSize().y,
  //           aColor.r, aColor.g, aColor.b, aColor.a);

  const PLAOBJImageClip *imageClip = aLayer->GetImageClip();
  if (imageClip)
  {
    const PLAOBJImage *texImage = imageClip->GetImage();
    if (texImage) {
      glEnable(GL_TEXTURE_2D);

      if (imageClip->GetObjectType() == PLAObjectType::VideoClip) {
        // VideoClip: dedicated texture per Video, data updated each frame
        PLAOBJVideoClip *videoClip = const_cast<PLAOBJVideoClip*>(
          static_cast<const PLAOBJVideoClip*>(imageClip));
        videoClip->Update();
        PLAGLUTTexture::Manager::Instance()->BindAndUpdate(videoClip->GetVideo(), texImage);
      }
      else
      {
        // Static image: cached texture
        PLAGLUTTexture::Manager::Instance()->GetOrCreate(texImage);
      }
    }
  }
  else
  {
    glDisable(GL_TEXTURE_2D);
  }

  if (aMotion) {
    if (aMotion->GetObjectName() == "Telop")
    {
      GRA_TRACE("");
    }
  }

  const PLAVec3f offset = aLayer->GetOffset();

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
    texCoords[0] = imageClip->GetNormalizedPixelClip().pos.x;  // 0.0,
    texCoords[1] = imageClip->GetNormalizedPixelClip().pos.y;  // 0.0,
    texCoords[2] = imageClip->GetNormalizedPixelClip().pos.x +
                   imageClip->GetNormalizedPixelClip().size.x; // 0.0625,
    texCoords[3] = imageClip->GetNormalizedPixelClip().pos.y;  // 0.0,
    texCoords[4] = imageClip->GetNormalizedPixelClip().pos.x;  // 0.0,
    texCoords[5] = imageClip->GetNormalizedPixelClip().pos.y +
                   imageClip->GetNormalizedPixelClip().size.y; // 0.0625,
    texCoords[6] = imageClip->GetNormalizedPixelClip().pos.x +
                   imageClip->GetNormalizedPixelClip().size.x; // 0.0625
    texCoords[7] = imageClip->GetNormalizedPixelClip().pos.y +
                   imageClip->GetNormalizedPixelClip().size.y; // 0.0625,
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

  // Draw stroke if strokeColor has alpha > 0
  const PLAStroke &stroke = aLayer->GetStroke();
  PLAColor strokeColor = stroke.color;
  strokeColor *= aColor;
  if (strokeColor.a > 0) {
    glDisable(GL_TEXTURE_2D);
    PLAFloat w = stroke.width;
    PLAFloat left = offset.x;
    PLAFloat right = offset.x + aLayer->GetSize().x;
    PLAFloat top = -offset.y;
    PLAFloat bottom = -offset.y - aLayer->GetSize().y;
    PLAFloat z = offset.z;

    // Calculate stroke offset based on alignment
    PLAFloat outerOffset = 0;
    PLAFloat innerOffset = 0;
    switch (stroke.align) {
      case PLAStroke::Align::Outside:
        outerOffset = w;
        innerOffset = 0;
        break;
      case PLAStroke::Align::Center:
        outerOffset = w * 0.5f;
        innerOffset = w * 0.5f;
        break;
      case PLAStroke::Align::Inside:
        outerOffset = 0;
        innerOffset = w;
        break;
      default:
        outerOffset = w;
        innerOffset = 0;
        break;
    }

    glColor4f(strokeColor.r, strokeColor.g, strokeColor.b, strokeColor.a);

    // Top edge
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(left - outerOffset, top + outerOffset, z);
    glVertex3f(right + outerOffset, top + outerOffset, z);
    glVertex3f(left - outerOffset, top - innerOffset, z);
    glVertex3f(right + outerOffset, top - innerOffset, z);
    glEnd();

    // Bottom edge
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(left - outerOffset, bottom + innerOffset, z);
    glVertex3f(right + outerOffset, bottom + innerOffset, z);
    glVertex3f(left - outerOffset, bottom - outerOffset, z);
    glVertex3f(right + outerOffset, bottom - outerOffset, z);
    glEnd();

    // Left edge (between top and bottom inner edges)
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(left - outerOffset, top - innerOffset, z);
    glVertex3f(left + innerOffset, top - innerOffset, z);
    glVertex3f(left - outerOffset, bottom + innerOffset, z);
    glVertex3f(left + innerOffset, bottom + innerOffset, z);
    glEnd();

    // Right edge (between top and bottom inner edges)
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(right - innerOffset, top - innerOffset, z);
    glVertex3f(right + outerOffset, top - innerOffset, z);
    glVertex3f(right - innerOffset, bottom + innerOffset, z);
    glVertex3f(right + outerOffset, bottom + innerOffset, z);
    glEnd();
  }
}

void PLAGLUTRenderer::DrawCircle(const PLALYRCircle *aLayer, const PLAColor &aColor,
                                 const PLATMLMotion *aMotion) const
{
  // GRA_PRINT("DrawCircle(aLayer: %s,"
  //           " aColor: {r: %.2f, g: %.2f, b: %.2f, a: %.2f})\n",
  //           aLayer->GetObjectName().c_str(),
  //           aColor.r, aColor.g, aColor.b, aColor.a);
  const PLAOBJImageClip *imageClip = aLayer->GetImageClip();
  if (imageClip)
  {
    const PLAOBJImage *texImage = imageClip->GetImage();
    if (texImage)
    {
      glEnable(GL_TEXTURE_2D);

      if (imageClip->GetObjectType() == PLAObjectType::VideoClip)
      {
        // VideoClip: dedicated texture per Video, data updated each frame
        PLAOBJVideoClip *videoClip = const_cast<PLAOBJVideoClip *>(
          static_cast<const PLAOBJVideoClip *>(imageClip));
        videoClip->Update();
        PLAGLUTTexture::Manager::Instance()->BindAndUpdate(videoClip->GetVideo(), texImage);
      }
      else
      {
        // Static image: cached texture
        PLAGLUTTexture::Manager::Instance()->GetOrCreate(texImage);
      }
    }
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
    const PLAVec2f origin = PLAVec2f( radius + aLayer->GetOffset().x,
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
      // GRA_DEBUG("vertices[%2d] : %.2f\n", index, vertices[index]);
      ++index;
      // GRA_DEBUG("vertices[%2d] : %.2f\n", index, vertices[index]);
      ++index;
      // GRA_DEBUG("vertices[%2d] : %.2f\n", index, vertices[index]);
      // GRA_DEBUG("--------------------\n");

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
    const PLAVec2f offset = PLAVec2f(0.5, 0.5);
    const double step = M_PI * 2 / split;
    const PLAVec2f origin = PLAVec2f( radius + offset.x,
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

  // Draw stroke if strokeColor has alpha > 0
  const PLAStroke &stroke = aLayer->GetStroke();
  PLAColor strokeColor = stroke.color;
  strokeColor *= aColor;
  if (strokeColor.a > 0) {
    glDisable(GL_TEXTURE_2D);
    glColor4f(strokeColor.r, strokeColor.g, strokeColor.b, strokeColor.a);

    PLAFloat w = stroke.width;
    PLAFloat baseRadius = aLayer->GetRadius();

    // Calculate inner/outer radius based on alignment
    PLAFloat outerRadius, innerRadius;
    switch (stroke.align) {
      case PLAStroke::Align::Outside:
        outerRadius = baseRadius + w;
        innerRadius = baseRadius;
        break;
      case PLAStroke::Align::Center:
        outerRadius = baseRadius + w * 0.5f;
        innerRadius = baseRadius - w * 0.5f;
        break;
      case PLAStroke::Align::Inside:
        outerRadius = baseRadius;
        innerRadius = baseRadius - w;
        break;
      default:
        outerRadius = baseRadius + w;
        innerRadius = baseRadius;
        break;
    }

    PLAFloat cx = baseRadius + aLayer->GetOffset().x;
    PLAFloat cy = -baseRadius - aLayer->GetOffset().y;
    PLAFloat z = aLayer->GetOffset().z;
    double step = M_PI * 2 / split;

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= split; i++)
    {
      double radian = i * step;
      PLAFloat cosR = cos(radian);
      PLAFloat sinR = sin(radian);
      // Outer vertex
      glVertex3f(cx + outerRadius * cosR, cy - outerRadius * sinR, z);
      // Inner vertex
      glVertex3f(cx + innerRadius * cosR, cy - innerRadius * sinR, z);
    }
    glEnd();
  }
}

void PLAGLUTRenderer::DrawArc(const PLALYRArc *aLayer, const PLAColor &aColor,
                              const PLATMLMotion *aMotion) const
{
  const PLAOBJImageClip *imageClip = aLayer->GetImageClip();
  if (imageClip)
  {
    const PLAOBJImage *texImage = imageClip->GetImage();
    if (texImage)
    {
      glEnable(GL_TEXTURE_2D);

      if (imageClip->GetObjectType() == PLAObjectType::VideoClip)
      {
        // VideoClip: dedicated texture per Video, data updated each frame
        PLAOBJVideoClip *videoClip = const_cast<PLAOBJVideoClip *>(
          static_cast<const PLAOBJVideoClip *>(imageClip));
        videoClip->Update();
        PLAGLUTTexture::Manager::Instance()->BindAndUpdate(videoClip->GetVideo(), texImage);
      }
      else
      {
        // Static image: cached texture
        PLAGLUTTexture::Manager::Instance()->GetOrCreate(texImage);
      }
    }
  }
  else
  {
    glDisable(GL_TEXTURE_2D);
  }

  const double radius = aLayer->GetRadius();
  const double startAngle = aLayer->GetStartAngle();
  const double endAngle = aLayer->GetEndAngle();
  const double angleSpan = endAngle - startAngle;

  // Calculate number of segments based on arc span
  int split = static_cast<int>(std::abs(angleSpan) / (M_PI * 2) * 24);
  if (split < 3) split = 3;

  const unsigned numVertices = 1 + split + 1;
  GLfloat vertices[numVertices * 3];
  {
    const double step = angleSpan / split;
    const PLAVec2f origin = PLAVec2f(radius + aLayer->GetOffset().x,
                                     -radius - aLayer->GetOffset().y);

    double radian = startAngle;

    // Center vertex
    vertices[0] = origin.x;
    vertices[1] = origin.y;
    vertices[2] = 0;

    for (int i = 1; i < numVertices; i++)
    {
      unsigned baseIndex = i * 3;
      vertices[baseIndex + 0] = origin.x + radius * cos(radian);
      vertices[baseIndex + 1] = origin.y - radius * sin(radian);
      vertices[baseIndex + 2] = 0;
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
    const double texRadius = 0.625 * 0.5;
    const PLAVec2f offset = PLAVec2f(0.5, 0.5);
    const double step = angleSpan / split;
    const PLAVec2f origin = PLAVec2f(texRadius + offset.x,
                                     -texRadius - offset.y);

    double radian = startAngle;
    texCoords[0] = origin.x;
    texCoords[1] = origin.y;

    for (int i = 1; i < numVertices; i++)
    {
      unsigned baseIndex = i * 2;
      texCoords[baseIndex + 0] = origin.x + texRadius * cos(radian);
      texCoords[baseIndex + 1] = origin.y - texRadius * sin(radian);
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

  // Draw stroke if strokeColor has alpha > 0
  const PLAStroke &stroke = aLayer->GetStroke();
  PLAColor strokeColor = stroke.color;
  strokeColor *= aColor;
  if (strokeColor.a > 0) {
    glDisable(GL_TEXTURE_2D);
    glColor4f(strokeColor.r, strokeColor.g, strokeColor.b, strokeColor.a);

    PLAFloat w = stroke.width;
    PLAFloat baseRadius = radius;

    // Calculate outer/inner offset based on alignment
    PLAFloat outerOffset, innerOffset;
    switch (stroke.align) {
      case PLAStroke::Align::Outside:
        outerOffset = w;
        innerOffset = 0;
        break;
      case PLAStroke::Align::Center:
        outerOffset = w * 0.5f;
        innerOffset = w * 0.5f;
        break;
      case PLAStroke::Align::Inside:
        outerOffset = 0;
        innerOffset = w;
        break;
      default:
        outerOffset = w;
        innerOffset = 0;
        break;
    }

    PLAFloat cx = baseRadius + aLayer->GetOffset().x;
    PLAFloat cy = -baseRadius - aLayer->GetOffset().y;
    PLAFloat z = aLayer->GetOffset().z;

    PLAFloat outerRadius = baseRadius + outerOffset;
    PLAFloat innerRadius = baseRadius - innerOffset;
    if (innerRadius < 0) innerRadius = 0;

    double step = angleSpan / split;

    // Draw arc stroke (curved part only)
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= split; i++)
    {
      double radian = startAngle + i * step;
      PLAFloat cosR = cos(radian);
      PLAFloat sinR = sin(radian);
      // Outer vertex
      glVertex3f(cx + outerRadius * cosR, cy - outerRadius * sinR, z);
      // Inner vertex
      glVertex3f(cx + innerRadius * cosR, cy - innerRadius * sinR, z);
    }
    glEnd();

    // Draw the two radial edges (from center to arc)
    // First edge (start angle)
    {
      double radian = startAngle;
      PLAFloat cosR = cos(radian);
      PLAFloat sinR = sin(radian);
      // Perpendicular direction for edge stroke
      PLAFloat perpX = -sinR;
      PLAFloat perpY = -cosR;

      glBegin(GL_TRIANGLE_STRIP);
      // From center outward along the radial edge
      glVertex3f(cx + perpX * outerOffset, cy - perpY * outerOffset, z);
      glVertex3f(cx - perpX * innerOffset, cy + perpY * innerOffset, z);
      glVertex3f(cx + outerRadius * cosR + perpX * outerOffset,
                 cy - outerRadius * sinR - perpY * outerOffset, z);
      glVertex3f(cx + outerRadius * cosR - perpX * innerOffset,
                 cy - outerRadius * sinR + perpY * innerOffset, z);
      glEnd();
    }

    // Second edge (end angle)
    {
      double radian = endAngle;
      PLAFloat cosR = cos(radian);
      PLAFloat sinR = sin(radian);
      PLAFloat perpX = sinR;
      PLAFloat perpY = cosR;

      glBegin(GL_TRIANGLE_STRIP);
      glVertex3f(cx + perpX * outerOffset, cy - perpY * outerOffset, z);
      glVertex3f(cx - perpX * innerOffset, cy + perpY * innerOffset, z);
      glVertex3f(cx + outerRadius * cosR + perpX * outerOffset,
                 cy - outerRadius * sinR - perpY * outerOffset, z);
      glVertex3f(cx + outerRadius * cosR - perpX * innerOffset,
                 cy - outerRadius * sinR + perpY * innerOffset, z);
      glEnd();
    }
  }
}

// この関数では、タイルチップを一つづつ矩形で描画しているが、FBOを利用して先に全チップを一枚のテクスチャに描画したほうが効率的なはず。
// This function draws each tile chip with a rectangle, but it should be more efficient to draw all the chips on one texture in advance using FBO.

void PLAGLUTRenderer::DrawTile(const PLALYRTile *aLayer,
                               const PLAColor &aColor,
                               const PLATMLMotion *aMotion) const
{
  // GRA_PRINT("DrawTile(aLayer: %s,"
  //           " aColor: {r: %.2f, g: %.2f, b: %.2f, a: %.2f})\n",
  //           aLayer->GetObjectName().c_str(),
  //           aColor.r, aColor.g, aColor.b, aColor.a);

  //-- This method is an inefficient implementation.
  static bool kIsDebug = false;

  PLAOBJImageSize texSize = PLAOBJImageSize(1024);
  const PLAOBJImage *texImage = aLayer->GetImage();
  if (texImage) {
    texSize = texImage->GetSize();
    glEnable(GL_TEXTURE_2D);
    // Static image: cached texture
    PLAGLUTTexture::Manager::Instance()->GetOrCreate(texImage);
  } else {
    glDisable(GL_TEXTURE_2D);
  }

  GRAVec2<PLASize> tileSize = aLayer->GetTileSize();
  GRAVec2<PLASize> chipSize = aLayer->GetChipSize();

  PLAVec3f offset = aLayer->GetOffset();

  GLfloat pxTable[tileSize.x];
  for (PLAInt i = 0; i < tileSize.x; i++) {
    GLfloat px = offset.x + chipSize.x * i;
    pxTable[i] = px;
    if (kIsDebug) { GRA_PRINT("pxTable[%d]: %.2f\n", i, pxTable[i]); }
  }

  GLfloat pyTable[tileSize.y];
  for (PLAInt i = 0; i < tileSize.y; i++) {
    GLfloat py = offset.y + chipSize.x * i;
    pyTable[i] = py;
    if (kIsDebug) { GRA_PRINT("pyTable[%d]: %.2f\n", i, pyTable[i]); }
  }

  PLASize numberOfChipsX = texSize.x / chipSize.x;
  GLfloat cxTable[numberOfChipsX];
  for (PLAInt i = 0; i < numberOfChipsX; i++) {
    cxTable[i] = (i * chipSize.x) / GLfloat(texSize.x);
    if (kIsDebug) { GRA_PRINT("cxTable[%d]:%.2f\n", i, cxTable[i]); }
  };

  PLASize numberOfChipsY = texSize.y / chipSize.y;
  GLfloat cyTable[numberOfChipsY];
  for (PLAInt i = 0; i < numberOfChipsY; i++) {
    cyTable[i] = (i * chipSize.y) / GLfloat(texSize.y);
    if (kIsDebug) { GRA_PRINT("cyTable[%d]:%.2f\n", i, cyTable[i]); }
  };

  GLfloat cw = static_cast<GLfloat>(chipSize.x) / texSize.x;
  GLfloat ch = static_cast<GLfloat>(chipSize.y) / texSize.y;

  const PLATileDataAddress dataAddress = aLayer->GetDataAddress();
  for (PLAInt y = 0; y < tileSize.y; y++) {
    for (PLAInt x = 0; x < tileSize.x; x++)
    {
      PLATileDataAddress address(dataAddress.x + x, dataAddress.y + y);
      const PLATileChip chip = aLayer->GetChip(address);
      // 空チップは描画をスキップ
      // Skip drawing if the chip is empty.
      if (chip.code == kPLATileChipCodeNone) { continue; }

      const PLATMLMotion *motion = aLayer->GetMotion(address);
      MotionProperties motionProperties = MotionProperties();
      GetMotionProperties(motion, &motionProperties);
      static const PLAUInt kNumVertices = 12;
      GLfloat vertices[kNumVertices] = {
        0, 0, 0,
        static_cast<GLfloat>(chipSize.x), 0, 0,
        0, -static_cast<GLfloat>(chipSize.y), 0,
        static_cast<GLfloat>(chipSize.x), -static_cast<GLfloat>(chipSize.y), 0,
      };

      if (kIsDebug) {
        for (int i = 0; i < kNumVertices;) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsequenced"
          GRA_DEBUG("x: %d, y: %d,"
                    " vertices: [%d] x: %.2f, [%d] y: %.2f, [%d] z: %.2f\n",
                    x, y, i, vertices[i++], i, vertices[i++], i, vertices[i++]);
#pragma clang diagnostic pop
        }
      }

      PLAColor color = aColor * chip.color;

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
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsequenced"
          GRA_DEBUG("x: %d, y: %d, coords: [%d] x: %.2f, [%d] y: %.2f\n",
                    x, y, i, coords[i++], i, coords[i++]);
#pragma clang diagnostic pop
        }
      }

      glPushMatrix();

      glTranslatef(pxTable[x], -pyTable[y], 0);

      auto translation = motionProperties.translation;
      glTranslatef(translation.x, -translation.y, translation.z);

      auto rotation = motionProperties.rotation;
      glTranslatef(12, -12, 0);
      glRotatef(rotation.x, 1.0, 0.0, 0.0);
      glRotatef(rotation.y, 0.0, 1.0, 0.0);
      glRotatef(rotation.z, 0.0, 0.0, 1.0);
      glTranslatef(-12, 12, 0);

      glVertexPointer(3, GL_FLOAT, 0, vertices);
      glColorPointer(4, GL_FLOAT, 0, colors);
      glTexCoordPointer(2, GL_FLOAT, 0, coords);

      glBegin(GL_TRIANGLE_STRIP);
      glArrayElement(0);
      glArrayElement(1);
      glArrayElement(2);
      glArrayElement(3);
      glEnd();

      glPopMatrix();
    }
  }
}

void PLAGLUTRenderer::DrawLabel(const PLALYRLabel *aLayer,
                                const PLAColor &aColor,
                                const PLATMLMotion *aMotion) const
{
  PLALYRLabel *mutableLayer = const_cast<PLALYRLabel *>(aLayer);
  mutableLayer->Update();

  const PLAOBJImage *texImage = aLayer->GetTextureImage();
  if (!texImage) {
    return;
  }

  glEnable(GL_TEXTURE_2D);
  // TODO: Use PLAGLUTTexture::Manager for caching. Currently not cached because
  // PLALYRLabel recreates _textureImage when text changes, and there is no
  // mechanism to invalidate the cache when the old PLAOBJImage is deleted.
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
               texImage->GetSize().x, texImage->GetSize().y, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, texImage->GetResourceData());

  // Set texture filtering for smooth text rendering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  const PLAVec3f offset = aLayer->GetOffset();
  const PLAVec3f size = aLayer->GetSize();

  GLfloat vertices[] = {
    offset.x,
    -offset.y,
    offset.z,
    offset.x + size.x,
    -offset.y,
    offset.z,
    offset.x,
    -offset.y - size.y,
    offset.z,
    offset.x + size.x,
    -offset.y - size.y,
    offset.z,
  };

  PLAColor color = aColor;
  GLfloat colors[] = {
    color.r, color.g, color.b, color.a,
    color.r, color.g, color.b, color.a,
    color.r, color.g, color.b, color.a,
    color.r, color.g, color.b, color.a,
  };

  GLfloat texCoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
  };

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(4, GL_FLOAT, 0, colors);
  glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

  glBegin(GL_TRIANGLE_STRIP);
  glArrayElement(0);
  glArrayElement(1);
  glArrayElement(2);
  glArrayElement(3);
  glEnd();
}

void PLAGLUTRenderer::ApplyRenderMode(PLARenderMode aMode) const
{
  switch (aMode) {
    case PLARenderMode::None:
      return;
    case PLARenderMode::Nearest:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glDisable(GL_POINT_SMOOTH);
      glDisable(GL_LINE_SMOOTH);
      break;
    case PLARenderMode::Linear:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glEnable(GL_POINT_SMOOTH);
      glEnable(GL_LINE_SMOOTH);
      break;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Unexpected PLARenderMode detected.");
      break;
  }
}

#pragma clang diagnostic pop
