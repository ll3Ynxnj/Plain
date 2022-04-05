#ifndef PLAIN_ENGINE_PLAGLUTRENDERER_HPP
#define PLAIN_ENGINE_PLAGLUTRENDERER_HPP

#include "PLAGLUT.h"
#include "Core/Class/PLARenderer.hpp"
#include "Layer/PLALYRRect.hpp"
#include "Layer/PLALYRCircle.hpp"
#include "Layer/PLALYRTile.hpp"

class PLAGLUTRenderer : public PLARenderer
{
public:
  static PLAGLUTRenderer *Create();

  PLAGLUTRenderer();
  ~PLAGLUTRenderer();

  virtual void Init() const;
  virtual void Clear() const;
  virtual void Flush() const;
  virtual void Render(const PLAActor *aActor) const;

  virtual void RefreshScreenSize(const PLAVec3 &aFrameSize,
                                 const PLAVec3 &aStageSize);
private :
  static void GetRectVertices(GLfloat aVertices[12],
                              const PLAVec3 &aPos, const PLAVec2 &aSize);
  static void GetRectColors(GLfloat aColors[16],
                            const PLAColor &aColor);
  static void GetRectTexCoords(GLfloat aCoords[8],
                               const PLAVec2 &aPos, const PLAVec2 &aSize);

  void Draw(const PLAActor *aActor, const PLAColor &aColor) const;
  void DrawRect(const PLALYRRect *aLayer, const PLAColor &aColor) const;
  void DrawCircle(const PLALYRCircle *aLayer, const PLAColor &aColor) const;
  void DrawTile(const PLALYRTile *aLayer, const PLAColor &aColor) const;
};

#endif // PLAIN_ENGINE_PLAGLUTRENDERER_HPP
