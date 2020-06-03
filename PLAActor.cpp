#include "PLAActor.hpp"
#include "PLAApp.hpp"
#include "PLAError.hpp"
#include "PLAShape.hpp"
#include "PLARenderer.hpp"

PLAActor::PLAActor(const PLAVec3 &aPivot,
                   const PLAColor &aColor,
                   const PLATransform &aTransform,
                   const PLAShape &aShape) :
PLAObj(),
_pivot(aPivot),
_color(aColor),
_transform(aTransform),
_shape(nullptr)
{
  switch (aShape.GetShapeType())
  {
    case PLAShapeType::Point :
      _shape = new PLAShapePoint(static_cast<const PLAShapePoint &>(aShape));
      break;
    case PLAShapeType::Line :
      _shape = new PLAShapeLine(static_cast<const PLAShapeLine  &>(aShape));
      break;
    case PLAShapeType::Rect :
      _shape = new PLAShapeRect(static_cast<const PLAShapeRect &>(aShape));
      break;
    case PLAShapeType::Circle :
      _shape = new PLAShapeCircle(static_cast<const PLAShapeCircle &>(aShape));
      break;
    default :
      PLAError::Throw(PLAErrorType::Assert, "Detected unexpected PLAShapeType.");
      break;
  }
}

PLAActor::~PLAActor()
{

}

void PLAActor::AddActor(PLAActor *aActor)
{
  _actors.push_back(aActor);
}

void PLAActor::Update()
{
  this->OnUpdate();
  for (PLAActor *actor : _actors)
  {
    actor->Update();
  }
}

void PLAActor::Render(const PLARenderer *aRenderer)
{
  this->OnRender(aRenderer);
  for (PLAActor *actor : _actors)
  {
    actor->Render(aRenderer);
  }
}

void PLAActor::GetOrigin(PLAVec3 *aOrigin)
{
  PLAVec3 size(kPLAVec3None);
  this->GetSize(&size);
  aOrigin->x = size.x * _pivot.x;
  aOrigin->y = size.y * _pivot.y;
  aOrigin->z = size.z * _pivot.z;
}

void PLAActor::OnUpdate()
{

}

void PLAActor::OnRender(const PLARenderer *aRenderer)
{
  aRenderer->Render(&_color, &_transform, _shape);
}
