#ifndef PLACIRCLEACTOR_HPP
#define PLACIRCLEACTOR_HPP

#include "PLAActor.hpp"
#include "PLARDCircle.hpp"

class PLACircleActor : public PLAActor
{
  PLARDCircle _renderingData;

public :
  PLACircleActor(const GRACircle &aCircle, const GRAColor &aColor);
  ~PLACircleActor();

protected :
  virtual void OnUpdate();
  virtual void OnRender();
};

#endif
