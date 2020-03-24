#ifndef PLARECTACTOR_HPP
#define PLARECTACTOR_HPP

#include "PLAActor.hpp"
#include "PLARDRect.hpp"

class PLARectActor : public PLAActor
{
  PLARDRect _renderingData;

public :
  PLARectActor(const GRARect &aRect, const GRAColor &aColor);
  virtual ~PLARectActor();

  void SetSize(const GRASize &aSize);

protected :
  virtual void OnUpdate();
  virtual void OnRender();
};

#endif
