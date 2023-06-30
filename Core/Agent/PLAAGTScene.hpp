//
// Created by Kentaro Kawai on 2022/04/16.
//

#ifndef ANHR_PLAAGTSCENE_HPP
#define ANHR_PLAAGTSCENE_HPP


#include "PLAAgent.hpp"
#include "PLAFunctionCode.hpp"
#include "Grain/Object/GRAOBJListener.hpp"

class PLAAGTPhase;
class PLAOBJScene;

class PLAAGTScene final : public PLAAgent
{
public:
  /// Agent is const method only.
  explicit PLAAGTScene(PLAOBJScene *aOwner);
  virtual ~PLAAGTScene() noexcept;

  void Init() const;
  void PushPhase(const PLAAGTPhase &aAgent) const;
  void PopPhase() const;

  void AddListener(GRAOBJListener<PLAAGTScene, PLAFunctionCode::Scene> *aListener) const;
  void RemoveListener(GRAOBJListener<PLAAGTScene, PLAFunctionCode::Scene> *aListener) const;
  void SetFunction(PLAFunctionCode::Scene aKey,
                   const std::function<void(PLAAGTScene)> &aFunc) const;

  void PrintPhases() const;

//protected:
  const PLAOBJScene *GetScene() const;
  PLAOBJScene *RefScene() const;
};


#endif //ANHR_PLAAGTSCENE_HPP
