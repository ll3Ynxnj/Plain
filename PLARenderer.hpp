#ifndef PLAIN_PLARENDERER_HPP
#define PLAIN_PLARENDERER_HPP

#include <vector>
#include "PLARDRect.hpp"
#include "PLARDCircle.hpp"
#include "PLARendererType.hpp"

class PLARenderer
{
  std::vector <const PLARenderingData *>_renderingDataSet;

public:
  static PLARenderer *Create(PLARendererType aType);

  PLARenderer();

  virtual ~PLARenderer();

  void PushRenderingData(const PLARenderingData *aData);
  void Render();

  virtual void Init() const = 0;
  virtual void Clear() const = 0;
  virtual void Flush() const = 0;
  virtual void DrawDemo() const = 0;
  virtual void DrawRect(const PLARDRect *aRect) const = 0;
  virtual void DrawCircle(const PLARDCircle *aCircle) const = 0;
  virtual void RefreshScreenSize(const PLAVec3 &aFrameSize,
                                 const PLAVec3 &aStageSize) = 0;
};

#endif // PLAIN_PLARENDERER_HPP
