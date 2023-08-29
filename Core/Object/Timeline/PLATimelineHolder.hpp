//
// Created by Kentaro Kawai on 2022/02/25.
//

#ifndef ANHR_PLATIMELINEHOLDER_HPP
#define ANHR_PLATIMELINEHOLDER_HPP

class PLAOBJTimelineNode;
class PLAOBJTimeline;
class PLAAGTTimeline;

class PLATimelineHolder
{
  PLAOBJTimeline *_timeline = nullptr;

public:
  PLATimelineHolder();
  PLATimelineHolder(PLAOBJTimeline *aTimeline);
  virtual ~PLATimelineHolder() noexcept;

  void AddTimelineThread(PLAOBJTimeline *aThread);
  void AddTimelineThread(const PLAAGTTimeline &aAgent);

  const PLAOBJTimeline *GetTimeline() const { return _timeline; }

  /*virtual*/ void OnFinishTimeline();
};

#endif //ANHR_PLATIMELINEHOLDER_HPP
