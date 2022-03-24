//
// Created by Kentaro Kawai on 2022/02/25.
//

#ifndef ANHR_PLATIMELINE_HPP
#define ANHR_PLATIMELINE_HPP

class PLATimelineNode;
class PLATimelineThread;

class PLATimeline
{
  PLATimelineThread *_thread = nullptr;

public:
  PLATimeline();
  PLATimeline(PLATimelineThread *aThread);
  virtual ~PLATimeline();

  void AddThread(PLATimelineThread *aThread);

  const PLATimelineThread *GetNodeThread() const { return _thread; }

  /*virtual*/ void NodeDidFinish();
};

#endif //ANHR_PLATIMELINE_HPP
