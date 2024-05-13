// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/12.
//

#ifndef ANHR_PLAAGTTIMELINE_HPP
#define ANHR_PLAAGTTIMELINE_HPP


#include <functional>
#include "PLAAgent.hpp"
#include "PLAFunctionCode.hpp"

class PLAOBJTimeline;
class PLAAGTTimelineNode;

class PLAAGTTimeline: public PLAAgent
{
public:
  friend class PLATimelineHolder;

  /// Agent is const method only.
  PLAAGTTimeline() = delete;
  explicit PLAAGTTimeline(PLAOBJTimeline *aOwner);
  virtual ~PLAAGTTimeline() noexcept;

  void AddNode(const PLAAGTTimelineNode &aAgent);

  void SetFunction(PLAFunctionCode::Timeline aKey,
                   const std::function<void(PLAAGTTimeline)> &aFunc) const;

protected:
  const PLAOBJTimeline *GetTimeline() const;
  PLAOBJTimeline *RefTimeline() const;
};


#endif //ANHR_PLAAGTTIMELINE_HPP
