#ifndef PLACIRCLEACTOR_HPP
#define PLACIRCLEACTOR_HPP

#include "PLAActor.hpp"
#include "Grain/GRACircle.h"
#include "Grain/GRAColor.h"

class PLACircleActor : public PLAActor
{
  GRACircle _circle;
  GRAColor _color;

public :
  PLACircleActor(const GRACircle &aCircle, const GRAColor &aColor);
  ~PLACircleActor();

protected :
  virtual void OnUpdate();
  virtual void OnRender();
};

#endif
