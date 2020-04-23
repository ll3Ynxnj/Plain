#ifndef PLAIN_PLAGLUTRENDERER_HPP
#define PLAIN_PLAGLUTRENDERER_HPP

#include "PLARenderer.hpp"
#include "PLARenderingData.hpp"

class PLAGLUTRenderer : public PLARenderer
{
public:
  PLAGLUTRenderer();
  ~PLAGLUTRenderer();

  virtual void Init() const;
  virtual void Clear() const;
  virtual void Flush() const;
  virtual void DrawDemo() const;
  virtual void DrawRect(const PLARDRect *aRect) const;
  virtual void DrawCircle(const PLARDCircle *aCircle) const;

  virtual void RefreshScreenSize(const PLAVec3 &aFrameSize,
                                 const PLAVec3 &aStageSize);
};

#endif // PLAIN_PLAGLUTRENDERER_HPP
