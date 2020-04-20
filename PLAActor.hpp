#ifndef PLAIN_PLAACTOR_HPP
#define PLAIN_PLAACTOR_HPP

#include <list>
#include "PLAActorType.hpp"
#include "PLAType.hpp"

class PLAActor
{
  PLAActorType _type;
  std::list<PLAActor *> _actors;
  PLAVec3 _pivot;
  PLAVec3 _origin;
  PLAVec3 _pos;
  PLAVec3 _size;

public :
  PLAActor(PLAActorType aType,
           const PLAVec3 &aPivot,
           const PLAVec3 &aPos,
           const PLAVec3 &aSize);
  virtual ~PLAActor();

  void AddActor(PLAActor *aActor);

  void Update();
  void Render();

  const PLAVec3 &GetPivot()  { return _pivot;  };
  const PLAVec3 &GetOrigin() { return _origin; };
  const PLAVec3 &GetPos()    { return _pos;    };
  const PLAVec3 &GetSize()   { return _size;   };

  size_t GetNumberOfActors()  { return _actors.size(); };

  virtual void SetPivot(const PLAVec3 &aPivot);
  virtual void SetSize(const PLAVec3 &aSize);

  void SetPos(const PLAVec3 &aPos) { _pos = aPos; };

protected :
  virtual void OnUpdate() = 0;
  virtual void OnRender() = 0;

private :
  void RefreshOrigin();
};

#endif // PLAIN_PLAACTOR_HPP
