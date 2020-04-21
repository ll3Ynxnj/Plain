#include "PLARectActor.hpp"
#include "PLAApp.hpp"

PLARectActor::PLARectActor(const PLARect &aRect,
                           const PLAColor &aColor,
                           const PLAVec3 &aPivot) :
  PLAActor(PLAActorType::Rect, aPivot, aRect.pos, aRect.size),
  _renderingData(PLARDRect(aRect, aColor))
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

void PLARectActor::SetSize(const PLAVec3 &aSize)
{
  PLAActor::SetSize(aSize);
  _renderingData.rect.size = aSize;
}
