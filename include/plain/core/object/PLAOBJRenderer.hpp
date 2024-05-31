#ifndef PLAIN_ENGINE_PLAOBJRENDERER_HPP
#define PLAIN_ENGINE_PLAOBJRENDERER_HPP

#include <vector>
#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/actor/PLAOBJActor.hpp"
#include "plain/core/PLARendererType.hpp"

class PLAOBJRenderer : public PLAObject
{
protected:
  PLAOBJRenderer();

public:
  static PLAOBJRenderer *Create(PLARendererType aType);

  virtual ~PLAOBJRenderer();

  virtual void Init() const = 0;
  virtual void Clear() const = 0;
  virtual void Flush() const = 0;
  virtual void Render(const PLAOBJActor *aActor) const = 0;

  virtual void RefreshScreenSize(const PLAVec3f &aFrameSize,
                                 const PLAVec3f &aStageSize) = 0;
};

#endif // PLAIN_ENGINE_PLAOBJRENDERER_HPP
