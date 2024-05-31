//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "plain/core/object/timeline/PLATimelineHolder.hpp"
#include "plain/core/object/timeline/PLAOBJTimeline.hpp"
#include "plain/core/app/PLAApp.hpp"
#include "plain/core/agent/PLAAGTTimeline.hpp"

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
