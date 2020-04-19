#include "PLARectActor.hpp"
#include "PLAApp.hpp"

PLARectActor::PLARectActor(const GRARect &aRect,
                           const GRAColor &aColor,
                           const GRAPoint &aPivot) :
  PLAActor(PLAActorType::Rect, aPivot, aRect.pos, aRect.size),
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
  _renderingData.rect.pos.x = this->GetPos().x - this->GetOrigin().x;
  _renderingData.rect.pos.y = this->GetPos().y - this->GetOrigin().y;
  _renderingData.rect.pos.z = this->GetPos().z - this->GetOrigin().z;
  PLAApp::GetInstance()->PushRenderingData(&_renderingData);
}

void PLARectActor::SetSize(const GRASize &aSize)
{
  PLAActor::SetSize(aSize);
  _renderingData.rect.size = aSize;
}
