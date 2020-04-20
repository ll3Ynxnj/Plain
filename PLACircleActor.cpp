#include "PLACircleActor.hpp"
#include "PLAApp.hpp"

PLACircleActor::PLACircleActor(const PLACircle &aCircle,
                               const PLAColor &aColor) :
PLAActor(PLAActorType::Circle, PLAVec3(0.5, 0.5, 0), aCircle.origin, PLAVec3(aCircle.radius * 2, aCircle.radius * 2, 0)),
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
