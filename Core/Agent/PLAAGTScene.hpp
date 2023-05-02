//
// Created by Kentaro Kawai on 2022/04/16.
//

#ifndef ANHR_PLAAGTSCENE_HPP
#define ANHR_PLAAGTSCENE_HPP


#include "PLAAgent.hpp"

class PLAOBJScene;

class PLAAGTScene final : public PLAAgent
{
public:
  /// Agent is const method only.
  explicit PLAAGTScene(PLAOBJScene *aScene);
  virtual ~PLAAGTScene() noexcept;

protected:
  const PLAOBJScene *GetStage() const;
  PLAOBJScene *RefStage() const;
};


#endif //ANHR_PLAAGTSCENE_HPP
