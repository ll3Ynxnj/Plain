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

PLATimelineHolder::PLATimelineHolder(PLAOBJTimeline *aThread):
  _thread(aThread)
{
  PLAApp::Instance()->AddTimelineThread(aThread);
}

PLATimelineHolder::~PLATimelineHolder() noexcept
{

}

void PLATimelineHolder::AddThread(PLAOBJTimeline *aThread)
{
  if (!_thread) {
    _thread = PLAOBJTimeline::Create(nullptr);
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
