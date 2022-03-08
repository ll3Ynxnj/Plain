//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "PLATimeline.hpp"
#include "PLATimelineThread.hpp"
#include "PLAApp.hpp"

// PLATimelineHolder ///////////////////////////////////////////////////////////

PLATimeline::PLATimeline()
{

}

PLATimeline::PLATimeline(PLATimelineThread *aThread):
  _thread(aThread)
{
  PLAApp::Instance()->AddNodeThread(aThread);
}

PLATimeline::~PLATimeline() noexcept
{

}

void PLATimeline::AddThread(PLATimelineThread *aThread)
{
  if (!_thread) {
    _thread = PLATimelineThread::Create(nullptr);
    _thread->SetHolder(this);
    PLAApp::Instance()->AddNodeThread(_thread);
  }
  _thread->AddThread(aThread);
}

void PLATimeline::ClearNode()
{
  _thread->Clear();
}

void PLATimeline::NodeDidFinish()
{
  PLAObject::Destroy(_thread);
  _thread = nullptr;
}
