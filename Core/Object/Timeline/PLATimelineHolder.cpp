//
// Created by Kentaro Kawai on 2022/02/25.
//

#include "PLATimelineHolder.hpp"
#include "PLAOBJTimeline.hpp"
#include "Object/PLAOBJApp.hpp"

// PLATimelineHolder ///////////////////////////////////////////////////////////

PLATimelineHolder::PLATimelineHolder()
{

}

PLATimelineHolder::PLATimelineHolder(PLAOBJTimeline *aThread):
  _thread(aThread)
{
  PLAOBJApp::Instance()->AddTimelineThread(aThread);
}

PLATimelineHolder::~PLATimelineHolder() noexcept
{

}

void PLATimelineHolder::AddThread(PLAOBJTimeline *aThread)
{
  if (!_thread) {
    _thread = PLAOBJTimeline::Create(nullptr);
    _thread->SetHolder(this);
    PLAOBJApp::Instance()->AddTimelineThread(_thread);
  }
  _thread->AddThread(aThread);
}

void PLATimelineHolder::OnFinishThread()
{
  //_thread->Unbind();
  _thread = nullptr;
}
