#include "PLARectActor.hpp"
#include "PLARenderingManager.hpp"

PLARectActor::PLARectActor(const GRARect &aRect, const GRAColor &aColor) :
  PLAActor(PLAActorType::Rect),
  _rect(aRect),
  _color(aColor)
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
  PLARenderingManager::GetInstance()->PushRenderingDataRect(_rect, _color);
}

void PLARectActor::SetRect(const GRARect &aRect)
{
  _rect = aRect;
}

void PLARectActor::SetPosition(const GRAPoint &aPosition)
{
  _rect.position = aPosition;
}

void PLARectActor::SetSize(const GRASize &aSize)
{
  _rect.size = aSize;
}
