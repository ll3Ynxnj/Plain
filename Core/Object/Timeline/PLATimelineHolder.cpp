//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "PLATimelineHolder.hpp"
#include "PLAOBJTimeline.hpp"
#include "Core/App/PLAApp.hpp"

// PLATimelineHolder ///////////////////////////////////////////////////////////

PLATimelineHolder::PLATimelineHolder()
{

}

PLATimelineHolder::PLATimelineHolder(PLAOBJTimeline *aTimeline):
  _timeline(aTimeline)
{
  PLAApp::Instance()->AddTimelineThread(aTimeline);
}

PLATimelineHolder::~PLATimelineHolder() noexcept
{

}

void PLATimelineHolder::AddThread(PLAOBJTimeline *aThread)
{
  if (!_timeline) {
    _timeline = PLAOBJTimeline::Create(nullptr);
    _timeline->SetHolder(this);
    PLAApp::Instance()->AddTimelineThread(_timeline);
  }
  _timeline->AddThread(aThread);
}

void PLATimelineHolder::OnFinishTimeline()
{
  //_timeline->Unbind();
  _timeline = nullptr;
}
