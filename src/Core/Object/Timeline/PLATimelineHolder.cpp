//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "Core/Object/Timeline/PLATimelineHolder.hpp"
#include "Core/Object/Timeline/PLAOBJTimeline.hpp"
#include "Core/App/PLAApp.hpp"
#include "Core/Agent/PLAAGTTimeline.hpp"

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

void PLATimelineHolder::AddTimelineThread(PLAOBJTimeline *aThread)
{
  if (!_timeline) {
    _timeline = PLAOBJTimeline::Create(nullptr);
    _timeline->SetHolder(this);
    PLAApp::Instance()->AddTimelineThread(_timeline);
  }
  _timeline->AddThread(aThread);
}

void PLATimelineHolder::AddTimelineThread(const PLAAGTTimeline &aAgent)
{
  auto thread = aAgent.RefTimeline();
  this->AddTimelineThread(thread);
}

void PLATimelineHolder::OnFinishTimeline()
{
  //_timeline->Unbind();
  _timeline = nullptr;
}
