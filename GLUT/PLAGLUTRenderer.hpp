#ifndef PLAIN_ENGINE_PLAGLUTRENDERER_HPP
#define PLAIN_ENGINE_PLAGLUTRENDERER_HPP

#include "PLARenderer.hpp"

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
  void Draw(const PLAActor *aActor) const;
  void DrawRect(const PLALYRRect *aLayer) const;
  void DrawCircle(const PLALYRCircle *aLayer) const;
};

#endif // PLAIN_ENGINE_PLAGLUTRENDERER_HPP
