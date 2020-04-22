#include "PLACircleActor.hpp"
#include "PLAApp.hpp"

PLACircleActor::PLACircleActor(const PLACircle &aCircle,
                               const PLAColor &aColor) :
PLAActor(PLAActorType::Circle,
         PLAVec3(0.5, 0.5, 0)),
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

void PLACircleActor::GetSize(PLAVec3 *aSize)
{
  float radius = _renderingData.circle.radius;
  aSize->x = radius;
  aSize->y = radius;
}

void PLACircleActor::SetSize(const PLAVec3 &aSize)
{
  float radius(aSize.x);
  if (radius < aSize.y) { radius = aSize.y; }
  _renderingData.circle.radius = radius;
}
