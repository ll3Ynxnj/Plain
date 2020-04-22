#ifndef PLAIN_PLAACTOR_HPP
#define PLAIN_PLAACTOR_HPP

#include <list>
#include "PLAObj.hpp"
#include "PLAActorType.hpp"

class PLAActor : public PLAObj
{
  PLAActorType _type;
  std::list<PLAActor *> _actors;
  PLAVec3 _pivot;

public :
  PLAActor(PLAActorType aType,
           const PLAVec3 &aPivot);
  virtual ~PLAActor();

  void AddActor(PLAActor *aActor);

  void Update();
  void Render();

  const PLAVec3 &GetPivot() { return _pivot;  };
  void GetOrigin(PLAVec3 *aOrigin);
  virtual void GetSize(PLAVec3 *aSize) = 0;

  size_t GetNumberOfActors() { return _actors.size(); };

  void SetPivot(const PLAVec3 &aPivot) { _pivot = aPivot; };
  virtual void SetSize(const PLAVec3 &aSize) = 0;

protected :
  virtual void OnUpdate() = 0;
  virtual void OnRender() = 0;

private :
  void RefreshOrigin();
};

#endif // PLAIN_PLAACTOR_HPP
