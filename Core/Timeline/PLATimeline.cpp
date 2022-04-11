//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "PLATimeline.hpp"
#include "PLATimelineThread.hpp"
#include "Core/Class/PLAApp.hpp"

// PLATimeline /////////////////////////////////////////////////////////////////

PLATimeline::PLATimeline()
{

}

PLATimeline::PLATimeline(PLATimelineThread *aThread):
  _thread(aThread)
{
  PLAApp::Instance()->AddTimelineThread(aThread);
}

PLATimeline::~PLATimeline() noexcept
{

}

void PLATimeline::AddThread(PLATimelineThread *aThread)
{
  if (!_thread) {
    _thread = PLATimelineThread::Create(nullptr);
    _thread->SetHolder(this);
    PLAApp::Instance()->AddTimelineThread(_thread);
  }
  _thread->AddThread(aThread);
}

void PLATimeline::OnFinishThread()
{
  //PLAApp::Instance()->RemoveTimelineThread(_thread);
  PLAObject::Destroy(_thread);
  _thread = nullptr;
}
