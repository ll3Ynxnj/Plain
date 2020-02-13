#ifndef PLAACTOR_HPP
#define PLAACTOR_HPP

#include <list>
#include "PLAActorType.hpp"

class PLAActor
{
  PLAActorType _type;
  std::list<PLAActor *> _actors;

public :
  PLAActor(PLAActorType aType);
  virtual ~PLAActor();

  void AddActor(PLAActor *aActor);

  void Update();
  void Render();

protected :
  virtual void OnUpdate() = 0;
  virtual void OnRender() = 0;
};

#endif
