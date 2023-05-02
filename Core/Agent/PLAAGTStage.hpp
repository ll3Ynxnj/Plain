//
// Created by Kentaro Kawai on 2022/04/28.
//

#ifndef ANHR_PLAAGTSTAGE_HPP
#define ANHR_PLAAGTSTAGE_HPP


#include "PLAAgent.hpp"
#include "PLAFunctionCode.hpp"
#include "Grain/Object/GRAOBJListener.hpp"

class PLAAGTActor;
class PLAOBJStage;

class PLAAGTStage final : public PLAAgent
{
public:

public:
  /// Agent is const method only.
  explicit PLAAGTStage(PLAOBJStage *aScene);
  virtual ~PLAAGTStage() noexcept;

  void Init() const;
  void AddActor(const PLAAGTActor &aAgent) const;
  void PrintActors() const;

  void AddListener(GRAOBJListener<PLAAGTStage, PLAFunctionCode::Stage> *aListener);
  void RemoveListener(GRAOBJListener<PLAAGTStage, PLAFunctionCode::Stage> *aListener);
  void SetFunction(PLAFunctionCode::Stage aKey,
                   const std::function<void(PLAAGTStage)> &aFunc);
  void RunFunction(PLAFunctionCode::Stage aKey);

  PLAVec3f GetSize() const;

protected:
  const PLAOBJStage *GetStage() const;
  PLAOBJStage *RefStage() const;
};


#endif //ANHR_PLAAGTSTAGE_HPP
