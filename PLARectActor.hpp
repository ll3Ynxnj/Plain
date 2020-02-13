#ifndef PLARECTACTOR_HPP
#define PLARECTACTOR_HPP

#include "PLAActor.hpp"
#include "Grain/GRARect.h"
#include "Grain/GRAColor.h"

class PLARectActor : public PLAActor
{
  GRARect _rect;
  GRAColor _color;

public :
  PLARectActor(const GRARect &aRect, const GRAColor &aColor);
  virtual ~PLARectActor();

  void SetRect(const GRARect &aRect);
  void SetPosition(const GRAPoint &aPosition);
  void SetSize(const GRASize &aSize);

protected :
  virtual void OnUpdate();
  virtual void OnRender();
};

#endif
