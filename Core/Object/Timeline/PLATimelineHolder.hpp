//
// Created by Kentaro Kawai on 2022/02/25.
//

#ifndef ANHR_PLATIMELINEHOLDER_HPP
#define ANHR_PLATIMELINEHOLDER_HPP

class PLAOBJTimelineNode;
class PLAOBJTimeline;

class PLATimelineHolder
{
  PLAOBJTimeline *_thread = nullptr;

public:
  PLATimelineHolder();
  PLATimelineHolder(PLAOBJTimeline *aThread);
  virtual ~PLATimelineHolder() noexcept;

  void AddThread(PLAOBJTimeline *aThread);

  const PLAOBJTimeline *GetNodeThread() const { return _thread; }

  /*virtual*/ void OnFinishThread();
};

#endif //ANHR_PLATIMELINEHOLDER_HPP
