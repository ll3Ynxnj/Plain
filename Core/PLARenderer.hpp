#ifndef PLAIN_ENGINE_PLARENDERER_HPP
#define PLAIN_ENGINE_PLARENDERER_HPP

#include <vector>
#include "PLAObject.hpp"
#include "PLAActor.hpp"
#include "PLARendererType.hpp"

class PLARenderer : public PLAObject
{
protected:
  PLARenderer();

public:
  static PLARenderer *Create();

  virtual ~PLARenderer();

  virtual void Init() const = 0;
  virtual void Clear() const = 0;
  virtual void Flush() const = 0;
  virtual void Render(const PLAActor *aActor) const = 0;

  virtual void RefreshScreenSize(const PLAVec3 &aFrameSize,
                                 const PLAVec3 &aStageSize) = 0;
};

#endif // PLAIN_ENGINE_PLARENDERER_HPP
