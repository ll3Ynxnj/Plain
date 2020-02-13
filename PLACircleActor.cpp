#include "PLACircleActor.hpp"
#include "PLARenderingManager.hpp"
#include "PLARDCircle.hpp"

PLACircleActor::PLACircleActor(const GRACircle &aCircle,
                               const GRAColor &aColor) :
  PLAActor(PLAActorType::Circle),
  _circle(aCircle),
  _color(aColor)
{

}

PLACircleActor::~PLACircleActor()
{

}

void PLACircleActor::OnUpdate()
{

}

void PLACircleActor::OnRender()
{
  PLARenderingManager::GetInstance()->PushRenderingDataCircle(_circle, _color, 24);
}
