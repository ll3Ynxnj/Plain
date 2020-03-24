#include "PLACircleActor.hpp"
#include "PLARenderingManager.hpp"

PLACircleActor::PLACircleActor(const GRACircle &aCircle,
                               const GRAColor &aColor) :
PLAActor(PLAActorType::Circle),
_renderingData(aCircle, aColor, 24)
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
  PLARenderingManager::GetInstance()->PushRenderingData(&_renderingData);
}
