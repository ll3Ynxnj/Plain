#ifndef PLARENDERER_HPP
#define PLARENDERER_HPP

#include <vector>
#include "PLARDRect.hpp"
#include "PLARDCircle.hpp"

class PLARenderer
{
  std::vector <const PLARenderingData *>_renderingDataSet;

public:
  PLARenderer();

  virtual ~PLARenderer();

  void PushRenderingData(const PLARenderingData *aData);
  void Render();

  virtual void Clear() const = 0;
  virtual void Flush() const = 0;
  virtual void DrawDemo() const = 0;
  virtual void DrawRect(const PLARDRect *aRect) const = 0;
  virtual void DrawCircle(const PLARDCircle *aCircle) const = 0;
  virtual void RefreshScreenSize(const GRASize &aFrameSize,
                                 const GRASize &aStageSize) = 0;
};

#endif
