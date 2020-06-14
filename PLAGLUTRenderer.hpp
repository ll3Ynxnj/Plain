#ifndef PLAIN_PLAGLUTRENDERER_HPP
#define PLAIN_PLAGLUTRENDERER_HPP

#include "PLARenderer.hpp"

class PLAGLUTRenderer : public PLARenderer
{
public:
  PLAGLUTRenderer();
  ~PLAGLUTRenderer();

  virtual void Init() const;
  virtual void Clear() const;
  virtual void Flush() const;
  virtual void DrawDemo() const;

  virtual void RefreshScreenSize(const PLAVec3 &aFrameSize,
                                 const PLAVec3 &aStageSize);

  virtual void DrawRect(const PLAColor *aColor,
                        const PLATransform *aTransform,
                        const PLAShapeRect* aRect) const;
  virtual void DrawCircle(const PLAColor *aColor,
                          const PLATransform *aTransform,
                          const PLAShapeCircle *aCircle) const;
};

#endif // PLAIN_PLAGLUTRENDERER_HPP
