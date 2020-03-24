#include "PLARectActor.hpp"
#include "PLARenderingManager.hpp"

PLARectActor::PLARectActor(const GRARect &aRect, const GRAColor &aColor) :
  PLAActor(PLAActorType::Rect),
  _renderingData(aRect, aColor)
{

}

PLARectActor::~PLARectActor()
{

}

void PLARectActor::OnUpdate()
{

}

void PLARectActor::OnRender()
{
  PLARenderingManager::GetInstance()->PushRenderingData(&_renderingData);
}

void PLARectActor::SetSize(const GRASize &aSize)
{
  _renderingData.rect.size = aSize;
}
