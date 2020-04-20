#ifndef PLAIN_PLARECTACTOR_HPP
#define PLAIN_PLARECTACTOR_HPP

#include "PLAActor.hpp"
#include "PLARDRect.hpp"

class PLARectActor : public PLAActor
{
  PLARDRect _renderingData;

public :
  PLARectActor(const PLARect &aRect,
               const PLAColor &aColor,
               const PLAVec3 &aPivot = PLAVec3(0));
  virtual ~PLARectActor();

  virtual void SetSize(const PLAVec3 &aSize);

protected :
  virtual void OnUpdate();
  virtual void OnRender();
};

#endif // PLAIN_PLARECTACTOR_HPP
