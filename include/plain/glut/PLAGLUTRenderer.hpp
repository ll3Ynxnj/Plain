#ifndef PLAIN_ENGINE_PLAGLUTRENDERER_HPP
#define PLAIN_ENGINE_PLAGLUTRENDERER_HPP

#include "PLAGLUT.h"
#include "plain/core/object/PLAOBJRenderer.hpp"
#include "plain/core/object/layer/PLALYRRect.hpp"
#include "plain/core/object/layer/PLALYRCircle.hpp"
#include "plain/core/object/layer/PLALYRTile.hpp"
#include "plain/glut/PLAGLUTRenderer_camera.hpp"

class PLAGLUTRenderer : public PLAOBJRenderer
{
  struct MotionProperties {
    PLAVec3f translation = kPLAVec3fNone;
    PLAVec3f rotation = kPLAVec3fNone;
    PLAVec3f scale = kPLAVec3fNone;
    PLAColor color = kPLAColorNorm;
  };
public:
  static PLAGLUTRenderer *Create();

  PLAGLUTRenderer();
  ~PLAGLUTRenderer();

  virtual void Init() const;
  virtual void Clear() const;
  virtual void Flush() const;
  virtual void Render(const PLAOBJActor *aActor) const;

  virtual void RefreshScreenSize(const PLAVec3f &aFrameSize,
                                 const PLAVec3f &aStageSize);
private :
  static void GetRectVertices(GLfloat aVertices[12],
                              const PLAVec3f &aPos, const PLAVec2f &aSize);
  static void GetRectColors(GLfloat aColors[16],
                            const PLAColor &aColor);
  static void GetRectTexCoords(GLfloat aCoords[8],
                               const PLAVec2f &aPos, const PLAVec2f &aSize);
  static void GetMotionProperties(const PLATMLMotion *aNode,
                                  MotionProperties *aMotionProperties);
  void Draw(const PLAOBJActor *aActor, const PLAColor &aColor) const;
  void DrawRect(const PLALYRRect *aLayer, const PLAColor &aColor,
                const PLATMLMotion *aMotion) const;
  void DrawCircle(const PLALYRCircle *aLayer, const PLAColor &aColor,
                  const PLATMLMotion *aMotion) const;
  void DrawTile(const PLALYRTile *aLayer, const PLAColor &aColor,
                const PLATMLMotion *aMotion) const;
};

#endif // PLAIN_ENGINE_PLAGLUTRENDERER_HPP
