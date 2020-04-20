#ifndef PLAIN_PLACIRCLEACTOR_HPP
#define PLAIN_PLACIRCLEACTOR_HPP

#include "PLAActor.hpp"
#include "PLARDCircle.hpp"

class PLACircleActor : public PLAActor
{
  PLARDCircle _renderingData;

public :
  PLACircleActor(const PLACircle &aCircle, const PLAColor &aColor);
  ~PLACircleActor();

protected :
  virtual void OnUpdate();
  virtual void OnRender();
};

#endif // PLAIN_PLACIRCLEACTOR_HPP
