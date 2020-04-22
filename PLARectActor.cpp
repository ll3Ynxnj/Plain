#include "PLARectActor.hpp"
#include "PLAApp.hpp"

PLARectActor::PLARectActor(const PLARect &aRect,
                           const PLAColor &aColor,
                           const PLAVec3 &aPivot) :
  PLAActor(PLAActorType::Rect, aPivot),
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
  PLAApp::GetInstance()->PushRenderingData(&_renderingData);
}
