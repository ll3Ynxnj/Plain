//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "PLATimelineHolder.hpp"
#include "PLATimeline.hpp"
#include "Object/PLAApp.hpp"

// PLATimelineHolder ///////////////////////////////////////////////////////////

PLATimelineHolder::PLATimelineHolder()
{

}

PLATimelineHolder::PLATimelineHolder(PLATimeline *aThread):
  _thread(aThread)
{
  PLAApp::Instance()->AddTimelineThread(aThread);
}

PLATimelineHolder::~PLATimelineHolder() noexcept
{

}

void PLATimelineHolder::AddThread(PLATimeline *aThread)
{
  if (!_thread) {
    _thread = PLATimeline::Create(nullptr);
    _thread->SetHolder(this);
    PLAApp::Instance()->AddTimelineThread(_thread);
  }
  _thread->AddThread(aThread);
}

void PLATimelineHolder::OnFinishThread()
{
  //_thread->Unbind();
  _thread = nullptr;
}
