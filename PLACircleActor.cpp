#include "PLACircleActor.hpp"
#include "PLAApp.hpp"

PLACircleActor::PLACircleActor(const GRACircle &aCircle,
                               const GRAColor &aColor) :
PLAActor(PLAActorType::Circle, GRAPoint(0.5, 0.5, 0), aCircle.origin, GRASize(aCircle.radius * 2, aCircle.radius * 2, 0)),
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
  PLAApp::GetInstance()->PushRenderingData(&_renderingData);
}
