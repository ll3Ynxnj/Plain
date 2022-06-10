//
// Created by Kentaro Kawai on 2022/02/25.
//

#ifndef ANHR_PLATIMELINEHOLDER_HPP
#define ANHR_PLATIMELINEHOLDER_HPP

class PLATimelineNode;
class PLATimeline;

class PLATimelineHolder
{
  PLATimeline *_thread = nullptr;

public:
  PLATimelineHolder();
  PLATimelineHolder(PLATimeline *aThread);
  virtual ~PLATimelineHolder() noexcept;

  void AddThread(PLATimeline *aThread);

  const PLATimeline *GetNodeThread() const { return _thread; }

  /*virtual*/ void OnFinishThread();
};

#endif //ANHR_PLATIMELINEHOLDER_HPP
