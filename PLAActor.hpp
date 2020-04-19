#ifndef PLAACTOR_HPP
#define PLAACTOR_HPP

#include <list>
#include "PLAActorType.hpp"

#include "Grain/GRAPoint.hpp"
#include "Grain/GRASize.hpp"

class PLAActor
{
  PLAActorType _type;
  std::list<PLAActor *> _actors;
  GRAPoint _pivot;
  GRAPoint _origin;
  GRAPoint _pos;
  GRASize _size;

public :
  PLAActor(PLAActorType aType,
           const GRAPoint &aPivot,
           const GRAPoint &aPos,
           const GRASize &aSize);
  virtual ~PLAActor();

  void AddActor(PLAActor *aActor);

  void Update();
  void Render();

  const GRAPoint &GetPivot()  { return _pivot;  };
  const GRAPoint &GetOrigin() { return _origin; };
  const GRAPoint &GetPos()    { return _pos;    };
  const GRAPoint &GetSize()   { return _size;   };

  size_t GetNumberOfActors()  { return _actors.size(); };

  virtual void SetPivot(const GRAPoint &aPivot);
  virtual void SetSize(const GRASize &aSize);

  void SetPos(const GRAPoint &aPos) { _pos = aPos; };

protected :
  virtual void OnUpdate() = 0;
  virtual void OnRender() = 0;

private :
  void RefreshOrigin();
};

#endif
