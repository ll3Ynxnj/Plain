#ifndef PLAIN_PLARENDERER_HPP
#define PLAIN_PLARENDERER_HPP

#include <vector>
#include "Plain.hpp"
#include "PLARendererType.hpp"

class PLATransform;
class PLAShape;
class PLAShapeRect;
class PLAShapeCircle;

class PLARenderer
{
public:
  static PLARenderer *Create(PLARendererType aType);

  PLARenderer();

  virtual ~PLARenderer();

  void Render(const PLAColor *aColor,
              const PLATransform *aTransform,
              const PLAShape *aShape) const;

  virtual void Init() const = 0;
  virtual void Clear() const = 0;
  virtual void Flush() const = 0;
  virtual void DrawDemo() const = 0;
  virtual void RefreshScreenSize(const PLAVec3 &aFrameSize,
                                 const PLAVec3 &aStageSize) = 0;

  virtual void DrawRect(const PLAColor *aColor,
                        const PLATransform *aTransform,
                        const PLAShapeRect *aRect) const = 0;
  virtual void DrawCircle(const PLAColor *aColor,
                          const PLATransform *aTransform,
                          const PLAShapeCircle *aCircle) const = 0;

};

#endif // PLAIN_PLARENDERER_HPP
